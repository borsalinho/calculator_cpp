#ifndef CPP_SMARTCALC_V2_0_1_SRC_MYCALC_VIEW_CALCVIEW_H
#define CPP_SMARTCALC_V2_0_1_SRC_MYCALC_VIEW_CALCVIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QVector>

#include "../controller/calcController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

namespace s21 {

class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(s21::CalcController* contr, QWidget* parent = nullptr);
  ~CalcView();

 private slots:

  void InputSymvol();
  void ClearString();
  void ClearLast();
  void InputMod();
  void InputWithBr();
  void GetResult();
  void PaintGraffic();
  void GetCreditResult();
  void GetDepositResult();
  void on_radioButton_capital_clicked();
  void on_radioButton_vuplata_clicked();

 private:

 struct GrafOptions {
    double x_min;
    double x_max;
    double y_min;
    double y_max;
  };

  bool CheckCreditOptions();
  void GetOptions(GrafOptions& o);
  bool CheckOptions();
  bool IsDigitalStr(const std::string& str);
  void SetCalcResult(std::string& str);
  bool IsXHere(const std::string& str);
  void SearchXAndPushX(std::string& str, std::string& x);
  double ScaleDependency(const double& d);
  void DrawingGraphics();
  bool CheckGrafValue(GrafOptions& o);
  void СoordinatesPreparation(GrafOptions& o, std::string& str);
  bool CheckStr(std::string& str);
  void GetDepositOptions(s21::DepositOptions& opt);
  bool CheckDepositOptions(s21::DepositOptions& opt);
  void SetDepositRes(s21::DepositOptions& opt, double res_nalog, double res_summ_end);

 private:
  QVector<double> x_, y_;

  s21::CalcController* contr_;
  Ui::CalcView* ui_;
};

} // namespace s21
#endif  // CPP_SMARTCALC_V2_0_1_SRC_MYCALC_VIEW_CALCVIEW_H
