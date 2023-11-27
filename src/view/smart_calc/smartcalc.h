#ifndef CPP3_SMARTCALC_V2_0_VIEW_SMARTCALC_H_
#define CPP3_SMARTCALC_V2_0_VIEW_SMARTCALC_H_

#include <QMainWindow>
#include <QMap>
#include <QPushButton>

#include "../../controller/smart_calc/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

namespace s21 {

class SmartCalc : public QMainWindow {
  Q_OBJECT

 public:
  SmartCalc(Controller *controller, QWidget *parent = nullptr);
  ~SmartCalc();

 private slots:
  void OnButtonsClicked();
  void OnButtonCreditClicked();
  void OnButtonDepositClicked();
  void OnButtonGraphClicked();
  void OnButtonEqualClicked();
  void OnButtonCClicked();
  void OnButtonDelClicked();

 private:
  Ui::SmartCalc *ui_;
  QMap<QPushButton *, QString> buttons_map_;
  Controller *controller_;

  void ConnectButtons();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_VIEW_SMARTCALC_H_
