#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCULATE_CALCCALCULATE_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCULATE_CALCCALCULATE_H_

#include "../common/calcCommon.h"

namespace s21 {



class CalcParser;

class CalcCalculation {

 public:
  CalcCalculation() = default;
  CalcCalculation(std::string str);

  double Calculation();
  double& GetResult();
  void GetStacks(std::stack<double>& stack_number, std::stack<t_operator>&  stack_operator);
  void SetAnsDefault();
  std::stack<double>& GetStackNumber();
  std::stack<t_operator>& GetStackOper();

 private:

  t_operator TopPopOper();
  double LocalArifm(double& uppr_num, double& lowr_num, int& oprtr);
  double LocalTrignm(double& num, int& oprtr);
  double& TopPopNum();
  bool IsTrigonometric(int& oprtr);
  void Minusization();
  void LocalCalc(double& uppr_num, int& oprtr);

 private:

  double answer_ = 0;

  std::stack<double>* stack_number_c_;
  std::stack<t_operator>* stack_operator_c_;

};
};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCULATE_CALCCALCULATE_H_
