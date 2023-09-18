#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_VALIDATOR_CALCVAlIDATOR_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_VALIDATOR_CALCVAlIDATOR_H_

#include "../common/calcCommon.h"

namespace s21 {

class CalcValidator {
 public:
  CalcValidator() = default;

  std::string& GetError();
  std::string& Validation(std::string& str);

  void SetErrDefault();
  void UpMaxSize();

 private:

  bool CheckSymvols(std::string str);
  bool CheckOperAndNum(const std::string& str);
  bool CheckLenght(const std::string& str);
  bool CheckNumber(const std::string& str);
  bool IsNextCharValid(char i);
  bool IsPrefCharDigit(char i);
  bool IsPrefCharValid(char i);
  bool IsNextOperValue(char i);
  bool IsPrevOperValue(char i);

  void DelSpace(std::string& str);

  int CheckBracer(const std::string& str);
  int CheckBracerCount(const std::string& str);
  int CheckDotAndExp(const std::string& str);

 private:
  size_t max_size_ = 255;

  std::string err_ = "no_err";

  const std::string tokens_[32] = {
    "inf", "pi",  "sqrt", "atan", "asin", "acos", "ln", "log",
    "tan", "cos", "sin",  "^",    "(",    ")",    "%",  "/",
    "*",   "-",   "+",    ".",    "x",    "e",    "0",  "1",
    "2",   "3",   "4",    "5",    "6",    "7",    "8",  "9"
  };
};
};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_VALIDATOR_CALCVAlIDATOR_H_
