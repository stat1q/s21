#include <gtest/gtest.h>

#include "model.h"

TEST(model, test_1) {
  s21::Model calculus("-sin(77)");
  s21::Model calc(calculus);
  double x = 1.0;
  double ans = -sin(77);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
  calculus.clearStack();
}

TEST(model, test_2) {
  s21::Model calculus("9.99999+9.999999*9.999");
  double x = 1.0;
  double ans = 9.99999 + 9.999999 * 9.999;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_3) {
  s21::Model calculus("((1)-2-((-3)-(4)))-5-(-6)");
  double x = 1.0;
  double ans = ((1) - 2 - ((-3) - (4))) - 5 - (-6);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_4) {
  s21::Model calculus("+5-(+4)-x+((+x)-x-(-x))");
  double x = 12345.0;
  double ans = +5 - (+4) - x + ((+x) - x - (-x));
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_5) {
  s21::Model calculus("-x-(-x)");
  double x = -123456.0;
  double ans = -x - (-x);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_6) {
  s21::Model calculus("-5mod3");
  double x = 1.0;
  double ans = fmod(-5, 3);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_7) {
  s21::Model calculus("2^3^4");
  double x = 1.0;
  double ans = 4096;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_8) {
  s21::Model calculus("1.0/2.0*(2.0-1.0)");
  double x = 1.0;
  double ans = 1.0 / 2.0 * (2.0 - 1.0);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_9) {
  s21::Model calculus("(1+2)*((3-4)+1+(5-6+7))");
  double x = 1.0;
  double ans = (1 + 2) * ((3 - 4) + 1 + (5 - 6 + 7));
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_10) {
  s21::Model calculus("1.1+2.0+(3*4.0)+(5+6.78)");
  double x = 1.0;
  double ans = 1.1 + 2.0 + (3 * 4.0) + (5 + 6.78);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_11) {
  s21::Model calculus("8^(1/(-x))");
  double x = -3.0;
  double ans = 2.0;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_12) {
  s21::Model calculus("asin(-x+1.5)+acos(-x)-atan(x+1)");
  double x = 1.0;
  double ans = asin(-x + 1.5) + acos(-x) - atan(x + 1);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_13) {
  s21::Model calculus("log(x)+ln(-2.0+4.0)");
  double x = 100.0;
  double ans = log10(x) + log(-2.0 + 4.0);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_14) {
  s21::Model calculus("cos(x)^2+sin(x)^2");
  double x = M_PI / 2.0;
  double ans = 1.0;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_15) {
  s21::Model calculus("-1*sin(cos(tan(-x^2)^3)^4)");
  double x = M_PI / 2.0;
  double ans = -1 * sin(pow(cos(pow(tan(pow(-x, 2)), 3)), 4));
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_16) {
  s21::Model calculus("+x");
  double x = M_PI;
  double ans = +x;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_17) {
  s21::Model calculus("-x");
  double x = M_PI;
  double ans = -x;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_18) {
  s21::Model calculus("xmod(x+1.0)");
  double x = M_PI;
  double ans = fmod(x, x + 1.0);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_19) {
  s21::Model calculus("1.2345678+2.3456789-3");
  double x = M_PI;
  double ans = 1.2345678 + 2.3456789 - 3;
  double result = calculus.expressionCalc(x);
  ASSERT_NEAR(ans, result, 1e-7);
}

TEST(model, test_20) {
  s21::Model calculus("(-1 + (-1 - (1 + 1)) - (-1 + 1) - (-1 + (-1)))");
  double x = M_PI;
  double ans = (-1 + (-1 - (1 + 1)) - (-1 + 1) - (-1 + (-1)));
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_21) {
  s21::Model calculus("sqrt(x)+sin(-3)");
  double x = 10.7;
  double ans = sqrt(x) + sin(-3);
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_22) {
  s21::Model calculus("x+2e-2");
  double x = 10.7;
  double ans = 10.72;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(model, test_23) {
  s21::Model calculus("x+2e+2");
  double x = 10.7;
  double ans = 210.7;
  double result = calculus.expressionCalc(x);
  ASSERT_DOUBLE_EQ(ans, result);
}

TEST(throw_test, test_1) {
  double x = 10.7;
  EXPECT_ANY_THROW(s21::Model("son(10)"));
  s21::Model calculus("4*");
  EXPECT_ANY_THROW(calculus.expressionCalc(x));
}

TEST(throw_test, test_2) {
  double x = 10.7;
  s21::Model calculus("*4");
  EXPECT_ANY_THROW(calculus.expressionCalc(x));
}

TEST(throw_test, test_3) {
  double x = 10.7;
  s21::Model calculus("");
  EXPECT_ANY_THROW(calculus.expressionCalc(x));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}