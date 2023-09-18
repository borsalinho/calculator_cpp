#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCMODEL_H_
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCMODEL_H_

#include "../model/validator/calcValidator.h"
#include "../model/parser/calcParser.h"
#include "../model/calculate/calcCalculate.h"
#include "../model/credit/calcCredit.h"
#include "../model/deposit/calcDeposit.h"

namespace s21 {

class CalcModel {
 public:

   CalcModel(){
       p_.GetStacks(stack_number_, stack_operator_);
       c_.GetStacks(stack_number_, stack_operator_);
   }
   CalcModel(std::string str) { // for tests
       p_.GetStacks(stack_number_, stack_operator_);
       c_.GetStacks(stack_number_, stack_operator_);
    if (v_.Validation(str) == "no_err") {
        p_.Parser(str);
        c_.Calculation();
    }
  };
  ~CalcModel() = default;

  s21::CalcValidator& GetValidPtr(){
      return v_;
  }
  s21::CalcCalculation& GetCalcPtr(){
      return c_;
  }
  s21::CalcParser& GetParserPtr() {
      return p_;
  }
  s21::CalcCredit& GetCreditPtr(){
      return cr_;
  }
  s21::CalcDeposit& GetDepositPtr(){
      return dcr_;
  }

 private:
  s21::CalcValidator v_;
  s21::CalcCalculation c_;
  s21::CalcParser p_;
  s21::CalcCredit cr_;
  s21::CalcDeposit dcr_;

  std::stack<double> stack_number_;
  std::stack<t_operator> stack_operator_;

};
};  // namespace s21

#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_MODEL_CALCMODEL_H_
