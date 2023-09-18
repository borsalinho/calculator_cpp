#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_CONTROLLER_CALCCONTROLLER_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_CONTROLLER_CALCCONTROLLER_H_

#include <QVector>
#include <iostream>

#include "../model/calcModel.h"

namespace s21 {

class CalcController {
 public:
  CalcController(){};
  CalcController(s21::CalcModel* m) :m_(m){};

  double CalcGraffic(std::string& str);
  double& GetAnswer();
  std::string& GetError();
  void ChangeMaxSize();
  void SetErrDefault();
  void SetAnsDefault();
  void Calculation(std::string& str);
  std::string& Validation(std::string& str);
  s21::CreditOptions& CalcCreditAni(s21::CreditOptions& cr);
  s21::CreditOptions& CalcCreditDiff(s21::CreditOptions& cr);
  s21::DepositOptions& CalcDeposit(s21::DepositOptions& crd);

 private:

  CalcModel* m_;

};
}  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_CONTROLLER_CALCCONTROLLER_H_
