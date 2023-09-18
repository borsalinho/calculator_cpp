#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCCOMMON_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCCOMMON_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {

struct t_operator {
  int value;
  int priority;
};

using size_t = long unsigned int;

};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCCOMMON_H_
