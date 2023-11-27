#ifndef CPP3_SMARTCALC_V2_0_VIEW_CREDIT_CREDIT_H_
#define CPP3_SMARTCALC_V2_0_VIEW_CREDIT_CREDIT_H_

#include <QWidget>

#include "../../controller/credit/credit_controller.h"

namespace Ui {
class Credit;
}

namespace s21 {

class Credit : public QWidget {
  Q_OBJECT

 public:
  Credit(CreditController &controller, QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void OnButtonCalculateClicked();

 private:
  Ui::Credit *ui_;
  CreditController controller_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_VIEW_CREDIT_CREDIT_H_
