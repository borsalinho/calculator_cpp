#include "calcCredit.h"

namespace s21 {

s21::CreditOptions& CalcCredit::GetCreditResAnui(CreditOptions& crd) {
  double i = crd.proc / 100 / 12;
  crd.every_m = crd.summ * (i + (i / (pow(1 + i, crd.srok) - 1)));
  crd.objaja = crd.srok * crd.every_m;
  crd.pereplata = crd.objaja - crd.summ;
  return crd;
}

s21::CreditOptions& CalcCredit::GetCreditResDiff(CreditOptions& crd) {
  crd.every_m = 0;
  crd.every_m =
      crd.summ / crd.srok +
      (crd.summ - (crd.summ / crd.srok) * (crd.row)) * ((crd.proc / 100) / 12);
  crd.objaja = crd.objaja + crd.every_m;
  crd.pereplata = crd.objaja - crd.summ;
  return crd;
}

} // namespace s21