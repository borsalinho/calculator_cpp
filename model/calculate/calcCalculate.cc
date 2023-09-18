#include "calcCalculate.h"

namespace s21 {

double CalcCalculation::Calculation() {
  std::stack<double> buffer_number_{};
  std::stack<t_operator> buffer_operator_{};
  int out = 800;
  t_operator zero{};

  zero.priority = -1;
  zero.value = out;
  buffer_operator_.push(zero);

  while (stack_operator_c_->top().value != out ||
         buffer_operator_.top().value != out) {
    if (stack_operator_c_->top().value == 90) {
      TopPopOper();
      Calculation();
      TopPopOper();
    } else {
      Minusization();
      if (buffer_operator_.top().priority > stack_operator_c_->top().priority) {
        stack_number_c_->push(LocalArifm(buffer_number_.top(), TopPopNum(),
                                      buffer_operator_.top().value));
        buffer_number_.pop();
        buffer_operator_.pop();
      } else {
        t_operator uppr_oprtr = TopPopOper();
        t_operator lowr_oprtr = stack_operator_c_->top();
        double uppr_num = TopPopNum();
        if (uppr_oprtr.priority <= lowr_oprtr.priority) {
          if (uppr_oprtr.priority == 3 && lowr_oprtr.priority == 3) {
            LocalCalc(uppr_num, uppr_oprtr.value);
          } else {
            buffer_number_.push(uppr_num);
            buffer_operator_.push(uppr_oprtr);
          }
        } else LocalCalc(uppr_num, uppr_oprtr.value);
      }
    }
   if (std::isnan(stack_number_c_->top())) return answer_ = stack_number_c_->top();
  }
  return answer_ = stack_number_c_->top();
}

t_operator CalcCalculation::TopPopOper() {
  t_operator oprtr = stack_operator_c_->top();
  stack_operator_c_->pop();
  return oprtr;
}

double& CalcCalculation::TopPopNum() {
  double& num = stack_number_c_->top();
  stack_number_c_->pop();
  return num;
}

void CalcCalculation::Minusization() {
  t_operator plus{};
  plus.priority = 1;
  plus.value = 1;
  if (stack_operator_c_->top().value == 2) {
    TopPopOper();
    stack_operator_c_->push(plus);
    stack_number_c_->push(TopPopNum() * (-1));
  }
}

double CalcCalculation::LocalArifm(double& uppr_num, double& lowr_num, int& oprtr) {
  double answer{0};
  switch (oprtr) {
    case 1:
      answer = lowr_num + uppr_num;
      break;
    case 2:
      answer = lowr_num - uppr_num;
      break;
    case 3:
      answer = lowr_num * uppr_num;
      break;
    case 4:
      answer = lowr_num / uppr_num;
      break;
    case 5:
      answer = fmod(lowr_num, uppr_num);
      break;
    case 6:
      answer = pow(lowr_num, uppr_num);
      break;
  }
  return answer;
}

void CalcCalculation::LocalCalc(double& uppr_num, int& oprtr) {
  if (IsTrigonometric(oprtr)) 
    stack_number_c_->push(LocalTrignm(uppr_num, oprtr));
  else 
    stack_number_c_->push(LocalArifm(uppr_num, TopPopNum(), oprtr));
}

bool CalcCalculation::IsTrigonometric(int& oprtr) {
  if (oprtr >= 10 && oprtr < 19) return true;
  return false;
}


double CalcCalculation::LocalTrignm(double& num, int& oprtr) {
  switch (oprtr) {
    case 10: return cos(num);

    case 11: return sqrt(num);

    case 12: return sin(num);

    case 13: return tan(num);

    case 14: return acos(num);

    case 15: return asin(num);

    case 16: return atan(num);

    case 17: return log(num);

    case 18: return log10(num);
  }
  return 0;
}

double& CalcCalculation::GetResult() { return answer_; };

void CalcCalculation::SetAnsDefault() { answer_ = 0; }

void CalcCalculation::GetStacks(std::stack<double>& stack_number,
                 std::stack<t_operator>&  stack_operator){
  stack_number_c_ = &stack_number;
  stack_operator_c_ = &stack_operator;
}

}; // namespace s21
