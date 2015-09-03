#ifndef SMARTWAY_H
#define SMARTWAY_H

#include <QMainWindow>

namespace Ui {
class SmartWay;
}

class SmartWay : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartWay(QWidget *parent = 0);
    ~SmartWay();

private:
    Ui::SmartWay *ui;
};

#endif // SMARTWAY_H
