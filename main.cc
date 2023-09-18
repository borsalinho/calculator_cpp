#include <QApplication>

// #include "model/calcModel.h"
#include "view/calcView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  
  s21::CalcModel m;
  s21::CalcController c(&m);
  s21::CalcView w(&c);
  w.show();
  return a.exec();
}
