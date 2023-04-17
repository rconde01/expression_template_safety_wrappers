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
// 1| o  o  o  o  x  o  o  o
// 2| o  o  o  o  x  o  o  o
// 3| o  o  o  o  x  o  o  o
// 4| o  o  o  o  x  o  o  o
// 5| x  x  x  x  x  x  x  x
// 6| o  o  o  o  x  o  o  o
// 7| o  o  o  o  x  o  o  o
// 8| o  o  o  o  x  o  o  o
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

#ifdef TEST_1_2
   m1 + mat_func();
#endif

#ifdef TEST_1_3
   auto lvme = m1 + m2;
   m1 + lvme;
#endif

#ifdef TEST_1_4
   m1 + (m2 + m3);
#endif

#ifdef TEST_1_5
   auto lvme = m1 + mat_func();
   m1 + lvme;
#endif

#ifdef TEST_1_6
   m1 + (m1 + mat_func());
#endif

#ifdef TEST_1_7
   auto lvme = m1 + (m2 + m3);
   m1 + lvme;
#endif

#ifdef TEST_1_8
   m1 + (m1 + (m2 + m3));
#endif

#ifdef TEST_2_1
   mat_func() + m2;
#endif

#ifdef TEST_2_2
   mat_func() + mat_func();
#endif

#ifdef TEST_2_3
   auto lvme = m1 + m2;
   mat_func() + lvme;
#endif

#ifdef TEST_2_4
   mat_func() + (m2 + m3);
#endif

#ifdef TEST_2_5
   auto lvme = m1 + mat_func();
   mat_func() + lvme;
#endif

#ifdef TEST_2_6
   mat_func() + (m1 + mat_func());
#endif

#ifdef TEST_2_7
   auto lvme = m1 + (m2 + m3);
   mat_func() + lvme;
#endif

#ifdef TEST_2_8
   mat_func() + (m1 + (m2 + m3));
#endif

#ifdef TEST_3_1
   auto lvme2 = m1 + m2;
   lvme2 + m2;
#endif

#ifdef TEST_3_2
   auto lvme2 = m1 + m2;
   lvme2 + mat_func();
#endif

#ifdef TEST_3_3
   auto lvme = m1 + m2;
   auto lvme2 = m1 + m2;
   lvme2 + lvme;
#endif

#ifdef TEST_3_4
   auto lvme2 = m1 + m2;
   lvme2 + (m2 + m3);
#endif

#ifdef TEST_3_5
   auto lvme = m1 + mat_func();
   auto lvme2 = m1 + m2;
   lvme2 + lvme;
#endif

#ifdef TEST_3_6
   auto lvme2 = m1 + m2;
   lvme2 + (m1 + mat_func());
#endif

#ifdef TEST_3_7
   auto lvme2 = m1 + m2;
   auto lvme = m1 + (m2 + m3);
   lvme2 + lvme;
#endif

#ifdef TEST_3_8
   auto lvme2 = m1 + m2;
   lvme2 + (m1 + (m2 + m3));
#endif

#ifdef TEST_4_1
   (m2 + m3) + m2;
#endif

#ifdef TEST_4_2
   (m2 + m3) + mat_func();
#endif

#ifdef TEST_4_3
   auto lvme = m1 + m2;
   (m2 + m3) + lvme;
#endif

#ifdef TEST_4_4
   (m2 + m3) + (m2 + m3);
#endif

#ifdef TEST_4_5
   auto lvme = m1 + mat_func();
   (m2 + m3) + lvme;
#endif

#ifdef TEST_4_6
   (m2 + m3) + (m1 + mat_func());
#endif

#ifdef TEST_4_7
   auto lvme = m1 + (m2 + m3);
   (m2 + m3) + lvme;
#endif

#ifdef TEST_4_8
   (m2 + m3) + (m1 + (m2 + m3));
#endif

   return 0;
}