#include "calcView.h"

#include "ui_calcView.h"

namespace s21 {

CalcView::CalcView(s21::CalcController* contr, QWidget* parent)
    : QMainWindow(parent), contr_(contr), ui_(new Ui::CalcView) {
  ui_->setupUi(this);

  ui_->label_result->setFocus();

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_BC, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_BO, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_pi, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_e, SIGNAL(clicked()), this, SLOT(InputSymvol()));
  connect(ui_->pushButton_qrt, SIGNAL(clicked()), this, SLOT(InputSymvol()));

  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(InputWithBr()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(InputWithBr()));

  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(InputMod()));

  connect(ui_->pushButton_AC, SIGNAL(clicked()), this, SLOT(ClearString()));
  connect(ui_->pushButton_EC, SIGNAL(clicked()), this, SLOT(ClearLast()));

  connect(ui_->pushButton_eq, SIGNAL(clicked()), this, SLOT(GetResult()));
  connect(ui_->pushButton_graf, SIGNAL(clicked()), this, SLOT(PaintGraffic()));
  connect(ui_->pushButton_getCred, SIGNAL(clicked()), this,
          SLOT(GetCreditResult()));
  connect(ui_->pushButton_dep_res, SIGNAL(clicked()), this,
          SLOT(GetDepositResult()));
}

CalcView::~CalcView() { delete ui_; }

void CalcView::InputSymvol() {
  QPushButton* button = (QPushButton*)sender();

  if (ui_->label_result->hasFocus()) {
    ui_->label_result->insert(button->text());
  }

  if (ui_->label_x->hasFocus()) {
    ui_->label_x->insert(button->text());
  }
}

void CalcView::InputWithBr() {
  QPushButton* button = (QPushButton*)sender();
  ui_->label_result->setText(ui_->label_result->text() + button->text() + '(');
}

void CalcView::ClearString() {
  if (ui_->label_result->hasFocus()) {
    ui_->label_result->setText("");
  }

  if (ui_->label_x->hasFocus()) {
    ui_->label_x->setText("");
  }
}

void CalcView::ClearLast() {
  if (ui_->label_result->hasFocus()) {
    QString label_text = ui_->label_result->text();
    label_text.chop(1);
    ui_->label_result->setText(label_text);
  }

  if (ui_->label_x->hasFocus()) {
    QString label_x = ui_->label_x->text();
    label_x.chop(1);
    ui_->label_x->setText(label_x);
  }
}

void CalcView::InputMod() {
  ui_->label_result->setText(ui_->label_result->text() + '%');
}

void CalcView::GetResult() {
  QString input_text = ui_->label_result->text();
  std::string str = input_text.toLocal8Bit().data();

  if (IsXHere(str)) {
    QString input_x = ui_->label_x->text();
    std::string str_x = input_x.toLocal8Bit().data();

    if (IsXHere(str_x)) {
      QMessageBox::critical(this, "", "Cannot call x inside x");
      return;
    }
    if (str_x.empty()) {
      QMessageBox::critical(this, "", "Enter x value");
      return;
    }
    SearchXAndPushX(str, str_x);
  }

  if (str.empty()) {
    QMessageBox::critical(this, "", "Empty expression");
    return;
  }

  if (!CheckStr(str)) return;

  SetCalcResult(str);
}

void CalcView::PaintGraffic() {
  if (!CheckOptions()) {
    QMessageBox::critical(
        this, "",
        "You can enter only numbers and once at the very beginning '-'");
    return;
  }

  GrafOptions opt;

  GetOptions(opt);

  if (!CheckGrafValue(opt)) {
    QMessageBox::critical(this, "",
                          "You can only enter between 1000000 and 1000000");
    return;
  }

  QString input_text = ui_->label_result->text();
  std::string str = input_text.toLocal8Bit().data();

  if (!IsXHere(str)) {
    QMessageBox::critical(this, "", "x missing");
    return;
  }

  if (!CheckStr(str)) return;

  СoordinatesPreparation(opt, str);

  DrawingGraphics();
}

void CalcView::GetCreditResult() {
  if (!CheckCreditOptions()) return;

  QModelIndex index;
  s21::CreditOptions crd;

  crd.summ = ui_->cred_summ->text().toDouble();
  crd.srok = ui_->cred_term->text().toDouble();
  crd.proc = ui_->cred_proc->text().toDouble();
  crd.every_m = 0;
  crd.pereplata = 0;
  crd.objaja = 0;

  QStandardItemModel* model = new QStandardItemModel(crd.srok, 1, this);

  ui_->table_pay->setModel(model);

  if (ui_->radioButton_ann->isChecked()) {
    crd = contr_->CalcCreditAni(crd);
  }

  for (int row = 0; row < model->rowCount(); ++row) {
    for (int col = 0; col < model->columnCount(); col++) {
      index = model->index(row, col);
      if (ui_->radioButton_diff->isChecked()) {
        crd.row = row;
        crd = contr_->CalcCreditDiff(crd);
      }
      model->setData(index, crd.every_m);
    }
  }

  model->setHeaderData(0, Qt::Horizontal, "Платёж в месяц");
  ui_->cred_pereplata->setText(QString::number(crd.pereplata, 'd', 2));
  ui_->cred_objaja->setText(QString::number(crd.objaja, 'd', 2));
}

void CalcView::GetDepositResult() {
  s21::DepositOptions opt;

  GetDepositOptions(opt);

  if (!CheckDepositOptions(opt)) return;

  opt = contr_->CalcDeposit(opt);

  double res_summ_end = opt.summ + opt.res_sum_proc;
  double res_nalog = opt.res_sum_proc * opt.nalog_proc / 100;

  SetDepositRes(opt,res_nalog, res_summ_end);

}



void CalcView::SetDepositRes(s21::DepositOptions& opt, double res_nalog, double res_summ_end){
    ui_->dep_nach_pros->setText(QString::number(opt.res_sum_proc, 'g', 15));
    ui_->dep_summ_naloga->setText(QString::number(res_nalog, 'g', 15));
    ui_->dep_summ_end->setText(QString::number(res_summ_end, 'g', 15));
}

void CalcView::GetDepositOptions(s21::DepositOptions& opt) {
  opt.summ = ui_->dep_summ->text().toDouble();
  opt.srok = ui_->dep_srok->text().toDouble();
  opt.proc = ui_->dep_pros_stav->text().toDouble();
  opt.nalog_proc = ui_->dep_nal_stav->text().toDouble();
  opt.per_vupl = ui_->dep_period_vuplat->text().toDouble();
  opt.kap_proc = ui_->dep_kapi_pros->text().toDouble();
  opt.snayt_mec = ui_->dep_snuat_mec->text().toDouble();
  opt.snyat_summ = ui_->dep_snuat_summ->text().toDouble();
  opt.popol_mec = ui_->dep_popol_mec->text().toDouble();
  opt.popol_summ = ui_->dep_popol_summ->text().toDouble();
}

bool CalcView::CheckDepositOptions(s21::DepositOptions& opt) {
  if (opt.summ <= 0) {
    QMessageBox::critical(this, "",
                          "Deposit amount not entered or entered incorrectly");
    return false;
  }
  if (opt.srok <= 0) {
    QMessageBox::critical(this, "",
                          "Placement term not entered or entered incorrectly");
    return false;
  }
  if (opt.srok > std::floor(opt.srok) || opt.srok < 0) {
    QMessageBox::critical(
        this, "",
        "The placement period must be an integer and a positive number");
    return false;
  }
  if (opt.proc <= 0) {
    QMessageBox::critical(this, "",
                          "Interest rate not entered or entered incorrectly");
    return false;
  }
  if (opt.per_vupl > std::floor(opt.per_vupl) || opt.per_vupl < 0) {
    QMessageBox::critical(
        this, "",
        "The frequency of payments must be an integer and a positive number");
    return false;
  }
  if (opt.kap_proc > std::floor(opt.kap_proc) || opt.srok < 0) {
    QMessageBox::critical(
        this, "",
        "Interest capitalization must be an integer and a positive number");
    return false;
  }
  if (opt.snayt_mec > std::floor(opt.snayt_mec) || opt.snayt_mec < 0) {
    QMessageBox::critical(this, "",
                          "Enter a partial withdrawal. month must be an "
                          "integer and a positive number");
    return false;
  }
  if (opt.popol_mec > std::floor(opt.popol_mec) || opt.popol_mec < 0) {
    QMessageBox::critical(
        this, "", "Replenishment must be an integer and a positive number");
    return false;
  }

  return true;
}

bool CalcView::CheckStr(std::string& str) {
  if (contr_->Validation(str) != "no_err") {
    QMessageBox::critical(this, "", contr_->GetError().c_str());
    contr_->SetErrDefault();
    return false;
  }

  return true;
}

bool CalcView::CheckCreditOptions() {
  int f = 1;

  if (ui_->cred_summ->text().toDouble() == 0) {
    QMessageBox::critical(this, "", "Cумму кредита введена не корректно");
    f = 0;
  }

  if (ui_->cred_term->text().toDouble() == 0) {
    QMessageBox::critical(this, "", "Срок кредита указано не корректно");
    f = 0;
  }

  if (ui_->cred_term->text().toDouble() >
      std::floor(ui_->cred_term->text().toDouble())) {
    QMessageBox::critical(this, "", "Срок кредита должен быть целым числом");
    f = 0;
  }

  if (ui_->cred_proc->text().toDouble() == 0) {
    QMessageBox::critical(this, "", "Процент указана не верно");
    f = 0;
  }

  if (!ui_->radioButton_ann->isChecked() &&
      !ui_->radioButton_diff->isChecked()) {
    QMessageBox::critical(this, "", "Выберите тип кредита");
    f = 0;
  }

  if (!f) return false;
  return true;
}

void CalcView::СoordinatesPreparation(GrafOptions& o, std::string& str) {
  double xBegin, xEnd, step, X;

  ui_->widget->clearGraphs();
  const double& visible_area = o.x_min + o.x_max;
  step = ScaleDependency(visible_area);

  xBegin = o.x_min;
  xEnd = o.x_max+ step;

  ui_->widget->xAxis->setRange(o.x_min, o.x_max);
  ui_->widget->yAxis->setRange(o.y_min, o.y_max);

  std::string string_x;
  std::string str_buffer;
  for (X = xBegin; X <= xEnd; X += step) {

    str_buffer = str;
    string_x = std::to_string(X);
    SearchXAndPushX(str_buffer, string_x);
    if (!std::isnan(contr_->CalcGraffic(str_buffer))){
        x_.push_back(X);
        y_.push_back(contr_->GetAnswer());
    } else contr_->SetAnsDefault();
  }
}

bool CalcView::CheckOptions() {
  QString x_min = ui_->label_x_min->text();
  std::string str_x_min = x_min.toLocal8Bit().data();

  if (str_x_min[0] == '-') str_x_min.erase(0, 1);
  if (!IsDigitalStr(str_x_min)) return false;

  QString x_max = ui_->label_x_max->text();
  std::string str_x_max = x_max.toLocal8Bit().data();

  if (str_x_max[0] == '-') str_x_max.erase(0, 1);
  if (!IsDigitalStr(str_x_max)) return false;

  QString y_min = ui_->label_y_min->text();
  std::string str_y_min = y_min.toLocal8Bit().data();

  if (str_y_min[0] == '-') str_y_min.erase(0, 1);
  if (!IsDigitalStr(str_y_min)) return false;

  QString y_max = ui_->label_y_max->text();
  std::string str_y_max = y_max.toLocal8Bit().data();

  if (str_y_max[0] == '-') str_y_max.erase(0, 1);
  if (!IsDigitalStr(str_y_max)) return false;

  return true;
}

bool CalcView::IsDigitalStr(const std::string& str) {
  unsigned long i = 0;

  while (i < str.size()) {
    if (!std::isdigit(str[i++])) return false;
  }

  return true;
}

void CalcView::GetOptions(GrafOptions& o) {

  o.x_min = ui_->label_x_min->text().toDouble();
  o.x_max = ui_->label_x_max->text().toDouble();
  o.y_min = ui_->label_y_min->text().toDouble();
  o.y_max = ui_->label_y_max->text().toDouble();
}

bool CalcView::CheckGrafValue(GrafOptions& o) {
  if (o.x_min >= -1000000 && o.x_max <= 1000000 && o.y_min >= -1000000 &&
      o.y_max <= 1000000 ) {
    return true;
  }

  return false;
}

void CalcView::DrawingGraphics() {
  ui_->widget->addGraph();
  ui_->widget->graph(0)->addData(x_, y_);
  ui_->widget->replot();
  x_.clear();
  y_.clear();
}

double CalcView::ScaleDependency(const double& d) {
  double result = 0;

  if (d <= 10)
    result = 0.01;
  else if (d > 10 && d <= 100)
    result = 0.1;
  else if (d > 100 && d <= 1000)
    result = 1;
  else if (d > 1000 && d <= 10000)
    result = 10;
  else if (d > 10000 && d <= 100000)
    result = 100;
  else if (d > 100000 && d <= 1000000)
    result = 100;

  return result;
}

void CalcView::SearchXAndPushX(std::string& str, std::string& x) {
  if (x[0] == '-' || x[0] == '+') {
    x.insert(x.begin(), '(');
    x.push_back(')');
    contr_->ChangeMaxSize();
  }

  std::string::size_type pos = 0;
  pos = str.find('x', pos);
  str.erase(pos, 1);
  str.insert(pos, x);

  if (IsXHere(str)) {
    SearchXAndPushX(str, x);
  }
}

void CalcView::SetCalcResult(std::string& str) {
  contr_->Calculation(str);
  double num = contr_->GetAnswer();
  QString result = QString::number(num, 'g', 25);
  ui_->label_result->setText("");
  ui_->label_result->setText(result);
  contr_->SetAnsDefault();
}

bool CalcView::IsXHere(const std::string& str) {
  if (str.find('x')!=std::string::npos) return true;
  return false;
}

void CalcView::on_radioButton_capital_clicked() {
  ui_->dep_period_vuplat->setText("0");
  ui_->dep_period_vuplat->setDisabled(1);
  ui_->dep_kapi_pros->setDisabled(0);
}

void CalcView::on_radioButton_vuplata_clicked() {
  ui_->dep_kapi_pros->setText("0");
  ui_->dep_period_vuplat->setDisabled(0);
  ui_->dep_kapi_pros->setDisabled(1);
}

}; // namespace s21
