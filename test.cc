#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "./model/calcModel.h"

TEST(calc, simple_1) {
  double x = 4 + 3 * 1 - 4 / 2 + 100;
  s21::CalcModel model("4+3*1-4/2+100");
  EXPECT_TRUE(model.GetValidPtr().GetError() == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, simple_2) {
  double x = 4 - 4 * 4 * 3 - 12 * 4 + 3 - 10 - 3 * 4;
  s21::CalcModel model("4-4*4*3-12*4+3-10-3*4");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, simple_3) {
  double x = 4 * 24 * 333;
  s21::CalcModel model("4*24*333");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, simple_4) {
  double x = 10 - 2 - 3 - 4;
  s21::CalcModel model("10-2-3-4");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, simple_5) {
  double x = 1e3;
  s21::CalcModel model("1e3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, simple_6) {
  double x = 1e-3;
  s21::CalcModel model("1e-3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, simple_7) {
  double x = 1e-3;
  s21::CalcModel model("1e+3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e+7);
}

TEST(calc, skobki_1) {
  double x = (2 - 3) * 2;
  s21::CalcModel model("(2-3)*2");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, skobki_2) {
  double x = (double)1 * (2 - 3) / 2;
  s21::CalcModel model("1*(2-3)/2");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, skobki_3) {
  double x = (double)1 * (2 - 3) / (2 + 2) + (2 + 9);
  s21::CalcModel model("1*(2-3)/(2+2)+(2+9)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, skobki_4) {
  double x = (double)1 * (2 - 3) / (2 + 2) + (2 + 9) + pow(3, 3);
  s21::CalcModel model("1*(2-3)/(2+2)+(2+9)+3^3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, skobki_5) {
  double x = (double)1 * (2 - 3) / (2 + 2) + (2 + 9) + pow(3, 2 + 3);
  s21::CalcModel model("1*(2-3)/(2+2)+(2+9)+3^(2+3)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, skobki_6) {
  double x = (double)1 * (2 - 3) / (2 + 2) + (2 + 9) + pow(3, 2 + 3 * (2 + 3));
  s21::CalcModel model("1*(2-3)/(2+2)+(2+9)+3^(2+3*(2+3))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), x, 1e-7);
}

TEST(calc, dvoinue_skobki_1) {
  s21::CalcModel model("((1+2/2*(2+3)/2)+1)+9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), 13.5, 1e-7);
}

TEST(calc, dvoinue_skobki_2) {
  s21::CalcModel model("(1+(1+2/2*(2+3)/2))+9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), 13.5, 1e-7);
}

TEST(calc, dvoinue_skobki_3) {
  s21::CalcModel model("1+(2*((1+8*2)*1+2^(2+2)))/2");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(),
              1 + (2 * ((1 + 8 * 2) * 1 + pow(2, (2 + 2)))) / 2, 1e-7);
}

TEST(calc, troinue_skobki_1) {
  s21::CalcModel model("(((1+2)*2)*2)/3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), 4, 1e-7);
}

TEST(calc, troinue_skobki_2) {
  s21::CalcModel model("(2^(1+2%(1+2)))/3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(pow(2, (1 + fmod(2, (1 + 2))))) / 3,
              1e-7);
}

TEST(calc, troinue_skobki_3) {
  s21::CalcModel model("(((1+3)/2)^(1+2%(1+2)))/3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(),
              (double)(pow((1 + 3) / 2, (1 + fmod(2, (1 + 2))))) / 3, 1e-7);
}

TEST(calc, trogono_errmetric_1) {
  s21::CalcModel model("cos(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), cos(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_2) {
  s21::CalcModel model("sin(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), sin(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_3) {
  s21::CalcModel model("tan(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), tan(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_4) {
  s21::CalcModel model("acos(1)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), acos(1), 1e-7);
}

TEST(calc, trogono_errmetric_5) {
  s21::CalcModel model("asin(1)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)asin(1), 1e-7);
}

TEST(calc, trogono_errmetric_5_1) {
  s21::CalcModel model("asin(1)*asin(1)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)asin(1) * asin(1), 1e-7);
}

TEST(calc, trogono_errmetric_6) {
  s21::CalcModel model("atan(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), atan(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_7) {
  s21::CalcModel model("sqrt(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), sqrt(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_8) {
  s21::CalcModel model("ln(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), log(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_9) {
  s21::CalcModel model("log(pi)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), log10(M_PI), 1e-7);
}

TEST(calc, trogono_errmetric_10) {
  s21::CalcModel model("2^2^3");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), pow(2, pow(2, 3)), 1e-7);
}

//===== тесты с первого калька ========

TEST(calc, old_tests_1) {
  s21::CalcModel model("(1+2)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(1 + 2), 1e-7);
}

TEST(calc, old_tests_2) {
  s21::CalcModel model("(-1)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(-1), 1e-7);
}

TEST(calc, old_tests_3) {
  s21::CalcModel model("(1)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(1), 1e-7);
}

TEST(calc, old_tests_4) {
  s21::CalcModel model("-(cos(pi))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), -(cos(M_PI)), 1e-7);
}

TEST(calc, old_tests_5) {
  s21::CalcModel model("cos((pi))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), cos(M_PI), 1e-7);
}

TEST(calc, old_tests_6) {
  s21::CalcModel model("cos(-(pi))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), cos(-(M_PI)), 1e-7);
}

TEST(calc, old_tests_7) {
  s21::CalcModel model("cos(cos(-(pi)))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), cos(cos(-(M_PI))), 1e-7);
}

TEST(calc, old_tests_8) {
  s21::CalcModel model("1+2^(5*cos(3.14))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)1 + pow(2, (5 * cos(3.14))), 1e-7);
}

TEST(calc, old_tests_9) {
  s21::CalcModel model("2^(2+cos(2))-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)pow(2, 2 + cos(2)) - 9, 1e-7);
}

TEST(calc, old_tests_10) {
  s21::CalcModel model("2*(2+cos(2))-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)2 * (2 + cos(2)) - 9, 1e-7);
}

TEST(calc, old_tests_11) {
  s21::CalcModel model("2*(cos(2)+2)-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)2 * (cos(2) + 2) - 9, 1e-7);
}

TEST(calc, old_tests_12) {
  s21::CalcModel model("2*(cos(2))-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)2 * (cos(2)) - 9, 1e-7);
}

TEST(calc, old_tests_13) {
  s21::CalcModel model("2*(cos(2))-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)2 * (cos(2)) - 9, 1e-7);
}

TEST(calc, old_tests_14) {
  s21::CalcModel model("2*cos(2)-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)2 * cos(2) - 9, 1e-7);
}

TEST(calc, old_tests_15) {
  s21::CalcModel model("2*((2))-9");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)2 * ((2)) - 9, 1e-7);
}

TEST(calc, old_tests_16) {
  s21::CalcModel model("5*cos(3.14)-2");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)5 * cos(3.14) - 2, 1e-7);
}

TEST(calc, old_tests_17) {
  s21::CalcModel model("((cos(3.14)-2)*9)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)((cos(3.14) - 2) * 9), 1e-7);
}

TEST(calc, old_tests_18) {
  s21::CalcModel model("2^(-(cos(9)+pi))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)pow(2, (-(cos(9) + M_PI))), 1e-7);
}

TEST(calc, old_tests_19) {
  s21::CalcModel model("((90))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)((90)), 1e-7);
}

TEST(calc, old_tests_20) {
  s21::CalcModel model("((-90))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)((-90)), 1e-7);
}

TEST(calc, old_tests_21) {
  s21::CalcModel model("(-(90))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(-(90)), 1e-7);
}

TEST(calc, old_tests_22) {
  s21::CalcModel model("(+(90))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(+(90)), 1e-7);
}

TEST(calc, wtf_test) {
  s21::CalcModel model("-sqrt(0^log(5-0))+ln(55/(2+0))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(3.3141860046725256), 1e-7);
}

TEST(calc, wtf_test_1) {
  s21::CalcModel model("atan(1)+asin(1)+acos(1)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  == "no_err");
  EXPECT_NEAR(model.GetCalcPtr().GetResult(), (double)(atan(1)+asin(1)+acos(1)), 1e-7);
}

//=========Validator================

TEST(calc, validator_1) {
  s21::CalcModel model("(+90))");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_2) {
  std::string qwe =
      "012345678901234567890123456789012345678901234567890123456789012345678901"
      "234567890123456789012345678901234567890123456789012345678901234567890123"
      "456789012345678901234567890123456789012345678901234567890123456789012345"
      "6789012345678901234567890123456789012345";
  s21::CalcModel model(qwe);
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_3) {
  s21::CalcModel model("cos()");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_4) {
  s21::CalcModel model("1+$");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_5) {
  s21::CalcModel model("1+pu");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_6) {
  s21::CalcModel model("1+3^");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_7) {
  s21::CalcModel model("1+cos()");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_8) {
  s21::CalcModel model("1+cos(");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_9) {
  s21::CalcModel model("1+cos(2.2.25)");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_10) {
  s21::CalcModel model("1+1e");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_11) {
  s21::CalcModel model("1+1e1e1");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_12) {
  s21::CalcModel model("1+1e1.1");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_13) {
  s21::CalcModel model("1+ing");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

TEST(calc, validator_14) {
  s21::CalcModel model("1+igf");
  EXPECT_TRUE(model.GetValidPtr().GetError()  != "no_err");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
