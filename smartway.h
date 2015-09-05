#ifndef SMARTWAY_H
#define SMARTWAY_H

#include <QMainWindow>
#include <QIntValidator>
#include <QDoubleValidator>

namespace Ui {
class SmartWay;
}

class SmartWay : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartWay(QWidget *parent = 0);
    ~SmartWay();

private slots:
    void on_txtAltura_textEdited();

    void on_txtLargura_textEdited();

    void on_btnDefinirMapa_clicked();

private:
    Ui::SmartWay *ui;
    QIntValidator *int_validator;
    QDoubleValidator *double_validator;

    void criarMapa();
    void apagarMapa();

    // Flags
    bool mapa_definido;
    bool partida_definida;
    bool chegada_definida;

};

#endif // SMARTWAY_H
