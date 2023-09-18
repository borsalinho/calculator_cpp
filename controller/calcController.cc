#include "calcController.h"

namespace s21 {

void CalcController::Calculation(std::string& str) {
  m_->GetParserPtr().Parser(str);
  
  m_->GetCalcPtr().Calculation();
}

std::string& CalcController::Validation(std::string& str) {
  return m_->GetValidPtr().Validation(str);
}

double CalcController::CalcGraffic(std::string& str) {
  m_->GetParserPtr().Parser(str);
  return m_->GetCalcPtr().Calculation();

}

s21::CreditOptions& CalcController::CalcCreditDiff(s21::CreditOptions& cr) {
  return m_->GetCreditPtr().GetCreditResDiff(cr);
}

s21::CreditOptions& CalcController::CalcCreditAni(s21::CreditOptions& cr) {
  return m_->GetCreditPtr().GetCreditResAnui(cr);
}

s21::DepositOptions& CalcController::CalcDeposit(s21::DepositOptions& crd) {
//  return m_->GetCreditPtr().GetCreditResDiff(crd);
    return m_->GetDepositPtr().CalcDepositRes(crd);
}

void CalcController::SetErrDefault() { m_->GetValidPtr().SetErrDefault(); }
void CalcController::SetAnsDefault() { m_->GetCalcPtr().SetAnsDefault(); }

double& CalcController::GetAnswer() { return m_->GetCalcPtr().GetResult(); }

std::string& CalcController::GetError() { return m_->GetValidPtr().GetError(); }

void CalcController::ChangeMaxSize() { m_->GetValidPtr().UpMaxSize(); }
}  // namespace s21
