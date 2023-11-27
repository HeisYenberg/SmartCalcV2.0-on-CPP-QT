#include <QApplication>

#include "view/smart_calc/smartcalc.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::SmartCalc view(&controller);
  view.show();
  return a.exec();
}
