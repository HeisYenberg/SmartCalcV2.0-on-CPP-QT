#ifndef CPP3_SMARTCALC_V2_0_VIEW_GRAPH_GRAPH_H_
#define CPP3_SMARTCALC_V2_0_VIEW_GRAPH_GRAPH_H_

#include <QWidget>

#include "../../controller/smart_calc/controller.h"

namespace Ui {
class Graph;
}

namespace s21 {

class Graph : public QWidget {
  Q_OBJECT

 public:
  Graph(Controller *controller, QWidget *parent = nullptr);
  ~Graph();

 private slots:
  void OnButtonGraphClicked();

 private:
  Ui::Graph *ui_;
  s21::Controller *controller_;
  friend class SmartCalc;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_VIEW_GRAPH_GRAPH_H_
