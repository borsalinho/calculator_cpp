#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CREDIT_CALCDEPOSIT_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CREDIT_CALCDEPOSIT_H_

#include "../common/calcCommon.h"

namespace s21 {

struct DepositOptions {
  double summ;
  double srok;
  double proc;
  double nalog_proc;
  double per_vupl;
  double kap_proc;
  double snayt_mec;
  double snyat_summ;
  double popol_mec;
  double popol_summ;
  double res = 0;
  double res_buff = 0;
  double res_sum_proc = 0;
};

class CalcDeposit {
 public:
  CalcDeposit() = default;
  ~CalcDeposit() = default;

  s21::DepositOptions& CalcDepositRes(s21::DepositOptions& o);

};
};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CREDIT_CALCDEPOSIT_H_
