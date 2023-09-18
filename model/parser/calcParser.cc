#include "calcParser.h"

namespace s21 {

void CalcParser::Parser(std::string& str) {
  t_operator zero{};
  zero.priority = -1;
  zero.value = 800;

  stack_operator_p_->push(zero);

  for (size_t i = 0; i < str.size();) {
    if (MyIsDigit(str[i])) {
      double numb_d_;

      if (IsDigitDotExp(str[i])) {
        std::string numb_s_ = {};

        while (IsDigitDotExp(str[i])) {
          numb_s_.push_back(str[i++]);
          if (str[i - 1] == 'e' && (str[i] == '-' || str[i] == '+'))
            numb_s_.push_back(str[i++]);
        }
        
        numb_d_ = std::stod(numb_s_.c_str());
      } else {
        if (str[i] == 'p')
          numb_d_ = M_PI;
        else {
          i++;
          numb_d_ = INFINITY;
        }
        i = i + 2;
      }
      
      stack_number_p_->push(numb_d_);
    } else {
      if (IsOperator(str[i])) {
        if ((str[i] == '-' || str[i] == '+') && (str[i - 1] == '(' || i == 0))
          stack_number_p_->push(0);
        stack_operator_p_->push(IdentOperator(str[i++]));

      } else stack_operator_p_->push(IdentFunc(str, i));
    }
  }
}

bool CalcParser::MyIsDigit(char c) {
  if ((IsDigitDotExp(c)) || (c == 'i') || (c == 'p')) return true;
  return false;
}

bool CalcParser::IsDigitDotExp(char c) {
  if ((std::isdigit(c)) || (c == 'e') || (c == '.')) return true;
  return false;
}

bool CalcParser::IsOperator(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' ||
      c == '(' || c == ')')
    return true;
  return false;
}

t_operator CalcParser::IdentOperator(char c) {
  t_operator operator_{};
  switch (c) {
    case '+':
      AssignValuePriory(1, 1, operator_);
      break;
    case '-':
      AssignValuePriory(1, 2, operator_);
      break;
    case '*':
      AssignValuePriory(2, 3, operator_);
      break;
    case '/':
      AssignValuePriory(2, 4, operator_);
      break;
    case '%':
      AssignValuePriory(2, 5, operator_);
      break;
    case '^':
      AssignValuePriory(3, 6, operator_);
      break;
    case ')':
      AssignValuePriory(90, 90, operator_);
      break;
    case '(':
      AssignValuePriory(0, 800, operator_);
      break;
  }
  return operator_;
}

void CalcParser::AssignValuePriory(int p, int v, t_operator& t) {
  t.priority = p;
  t.value = v;
}

t_operator CalcParser::IdentFunc(std::string str, size_t& i) {
  t_operator operator_{};

  std::string buff;
  while(IsTrigoChar(str[i])){
    buff.push_back(str[i++]);
    for (auto& q : functions_){
      if (q.str == buff){
        AssignValuePriory(q.p, q.v, operator_);
        break;
      }
    }
  }

  return operator_;
}

bool CalcParser::IsTrigoChar(char c) {
  if (c == 'c' || c == 'o' || c == 'x' ||
      c == 'q' || c == 'r' || c == 't' ||
      c == 'i' || c == 'n' || c == 'a' ||
      c == 'l' || c == 'g' || c == 's'
      ) return true;
  return false;
}

void CalcParser::GetStacks(std::stack<double>& stack_number,
                 std::stack<t_operator>&  stack_operator){
    stack_number_p_ = &stack_number;
    stack_operator_p_ = &stack_operator;
}

} // namespace s21
