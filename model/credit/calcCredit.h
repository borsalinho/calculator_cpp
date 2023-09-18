#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CREDIT_CALCCREDIT_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CREDIT_CALCCREDIT_H_

#include "../common/calcCommon.h"

namespace s21 {

struct CreditOptions {
  double summ;
  double proc;
  double srok;
  double every_m;
  double pereplata;
  double objaja;
  int row;
};

using size_t = long unsigned int;

class CalcCredit {
 public:
  CalcCredit() = default;
  ~CalcCredit() = default;

  s21::CreditOptions& GetCreditResAnui(CreditOptions& crd); //
  s21::CreditOptions& GetCreditResDiff(CreditOptions& crd); //

};
};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CREDIT_CALCCREDIT_H_
