#include "calcDeposit.h"

namespace s21 {
    s21::DepositOptions& CalcDeposit::CalcDepositRes(s21::DepositOptions& o){
        for (double i = 0; i < o.srok; i++) {
          o.res = (o.summ * o.proc * 365 / 12 / 365) / 100;
          o.res_buff = o.res_buff + o.res;
          if (--o.kap_proc == 0) {
            o.summ = o.summ + o.res_buff;
            o.kap_proc = o.kap_proc;
            o.res_buff = 0;
          }
          if (--o.per_vupl == 0) {
            o.per_vupl = o.per_vupl;
            o.res = 0;
          }
          if (--o.snayt_mec == 0) {
            o.summ = o.summ - o.snyat_summ;
            o.snayt_mec = o.snayt_mec;
          }
          if (--o.popol_mec == 0) {
            o.summ = o.summ + o.popol_summ;
            o.popol_mec = o.popol_mec;
          }
            o.res_sum_proc = o.res_sum_proc + o.res;
        }
        return o;
    }

} // namespace s21
