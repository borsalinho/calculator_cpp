#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_PARSER_CALCPARSER_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_PARSER_CALCPARSER_H_

#include "../common/calcCommon.h"
#include "../calculate/calcCalculate.h"

namespace s21 {

struct func_t {
  std::string str;
  int p;
  int v;
};

using size_t = long unsigned int;

class CalcCalculation;

class CalcParser {

 public:
  CalcParser() = default;
  ~CalcParser() = default;

  void Parser(std::string& str);

  void GetStacks(std::stack<double>& stack_number, std::stack<t_operator>&  stack_operator);
 private:
  
  t_operator IdentOperator(char c);
  t_operator IdentFunc(std::string str, size_t& i);

  bool MyIsDigit(char c);
  bool IsDigitDotExp(char c);
  bool IsTrigoChar(char c);
  bool IsOperator(char c);
  void AssignValuePriory(int p, int v, t_operator& t);

 private:

  std::stack<double>* stack_number_p_;
  std::stack<t_operator>* stack_operator_p_;

  const func_t functions_[9] = {
    {"acos", 10, 14}, {"asin", 10, 15}, {"atan", 10, 16},
    {"cos", 10, 10},  {"sqrt", 10, 11}, {"sin", 10, 12},
    {"tan", 10, 13},  {"log", 10, 18} , {"ln", 10, 17}
  };

};
};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_PARSER_CALCPARSER_H_
