#include "expression_template_safety_wrapper.hpp"

// clang-format off

// 1. l-value reference to a Matrix
// 2. r-value reference to a Matrix
// 3. l-value reference to a MatrixExpression only referencing l-value Matrices
// 4. r-value reference to a MatrixExpression only referencing l-value Matrices
// 5. l-value reference to a MatrixExpression referencing at least 1 r-value Matrix
// 6. r-value reference to a MatrixExpression referencing at least 1 r-value Matrix
// 7. l-value reference to a MatrixExpression referencing at least 1 r-value MatrixExpression
// 8. r-value reference to a MatrixExpression referencing at least 1 r-value MatrixExpression

//    1  2  3  4  5  6  7  8 -> LHS
// --------------------------------
// 1| o  o  o  o  x  o  x  o
// 2| o  o  o  o  x  o  x  o
// 3| o  o  o  o  x  o  x  o
// 4| o  o  o  o  x  o  x  o
// 5| x  x  x  x  x  x  x  x
// 6| o  o  o  o  x  o  x  o
// 7| x  x  x  x  x  x  x  x
// 8| o  o  o  o  x  o  x  o
// |
// RHS

// clang-format on

Matrix mat_func() {
   return Matrix{};
}

auto main() -> int {
   Matrix m1, m2, m3;

#ifdef TEST_1_1
   m1 + m2;
#endif

#ifdef TEST_5_1
   auto lvme = m1 + mat_func();
   lvme + m2;
#endif

   return 0;
}