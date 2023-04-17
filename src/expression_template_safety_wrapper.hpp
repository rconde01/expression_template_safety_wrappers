#include <Eigen/Dense>
#include <type_traits>

template <template <typename...> class Template, typename T>
struct is_instantiation_of : std::false_type {};

template <template <typename...> class Template, typename... Args>
struct is_instantiation_of<Template, Template<Args...>> : std::true_type {};

template <typename ReferencesAnRValue, typename UnderlyingType>
class MatrixExpression;

template <typename Derived>
class MatrixBase {
   public:
    template <typename Other>
    auto operator+(Other&& other) const& {
        using UnderlyingType =
            decltype(static_cast<Derived const*>(this)->underlying() +
                     std::forward<Other>(other).underlying());

        constexpr bool is_lhs_an_expression =
            is_instantiation_of<MatrixExpression, std::decay_t<Derived>>::value;

        if constexpr (is_lhs_an_expression) {
            constexpr bool does_lhs_reference_rvalue =
                std::decay_t<Derived>::IsReferencingAnRValue;

            static_assert(!does_lhs_reference_rvalue,
                          "The LHS references an r-value past its lifetime.");
        }

        constexpr bool is_rhs_an_expression =
            is_instantiation_of<MatrixExpression, std::decay_t<Other>>::value;
        constexpr bool is_rhs_an_rvalue =
            std::is_rvalue_reference<Other&&>::value;

        if constexpr (is_rhs_an_expression) {
            constexpr bool is_rhs_an_lvalue =
                std::is_lvalue_reference<Other&&>::value;

            if constexpr (is_rhs_an_lvalue) {
                static_assert(
                    !std::decay_t<Other>::IsReferencingAnRValue,
                    "The RHS references an r-value past its lifetime.");
            }
        } else if constexpr (is_rhs_an_rvalue) {
            return MatrixExpression<std::true_type, UnderlyingType>(
                static_cast<Derived const*>(this)->underlying() +
                std::forward<Other>(other).underlying());
        } else {
            return MatrixExpression<std::false_type, UnderlyingType>(
                static_cast<Derived const*>(this)->underlying() +
                std::forward<Other>(other).underlying());
        }
    }

    template <typename Other>
    auto operator+(Other&& other) const&& {
        using UnderlyingType =
            decltype(std::move(*static_cast<Derived const*>(this))
                         .underlying() +
                     std::forward<Other>(other).underlying());

        constexpr bool is_rhs_an_expression =
            is_instantiation_of<MatrixExpression, std::decay_t<Other>>::value;

        if constexpr (is_rhs_an_expression) {
            constexpr bool is_rhs_an_lvalue =
                std::is_lvalue_reference<Other&&>::value;

            if constexpr (is_rhs_an_lvalue) {
                static_assert(
                    !std::decay_t<Other>::IsReferencingAnRValue,
                    "The RHS references a r-value past its lifetime.");
            }

            if constexpr (std::decay_t<Other>::IsReferencingAnRValue) {
                return MatrixExpression<std::true_type, UnderlyingType>{
                    std::move(*static_cast<Derived const*>(this)).underlying() +
                    std::forward<Other>(other).underlying()};
            }
        }

        constexpr bool is_lhs_an_expression =
            is_instantiation_of<MatrixExpression, std::decay_t<Derived>>::value;

        if constexpr (is_lhs_an_expression) {
            constexpr bool lhs_references_rvalue =
                std::decay_t<Derived>::IsReferencingAnRValue;

            if constexpr (lhs_references_rvalue) {
                return MatrixExpression<std::true_type, UnderlyingType>{
                    std::move(*static_cast<Derived const*>(this)).underlying() +
                    std::forward<Other>(other).underlying()};
            }
        } else {
            constexpr bool is_lhs_an_rvalue =
                std::is_rvalue_reference<Derived&&>::value;

            if constexpr (is_lhs_an_rvalue) {
                return MatrixExpression<std::true_type, UnderlyingType>{
                    std::move(*static_cast<Derived const*>(this)).underlying() +
                    std::forward<Other>(other).underlying()};
            } else {
                return MatrixExpression<std::false_type, UnderlyingType>{
                    std::move(*static_cast<Derived const*>(this)).underlying() +
                    std::forward<Other>(other).underlying()};
            }
        }
    }
};

class Matrix : public MatrixBase<Matrix> {
   public:
    auto underlying() const -> Eigen::MatrixXd const& { return m_underlying; }

   private:
    Eigen::MatrixXd m_underlying;
};

template <typename ReferencesAnRValue, typename UnderlyingType>
class MatrixExpression
    : public MatrixBase<MatrixExpression<ReferencesAnRValue, UnderlyingType>> {
   public:
    static constexpr bool IsReferencingAnRValue = ReferencesAnRValue::value;

    MatrixExpression(UnderlyingType underlying) : m_underlying(underlying) {}

    auto underlying() const -> UnderlyingType const& { return m_underlying; }

   private:
    UnderlyingType m_underlying;
};