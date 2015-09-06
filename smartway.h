#ifndef SMARTWAY_H
#define SMARTWAY_H

#include <QMainWindow>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QFrame>
#include <QVector>
#include <QSpacerItem>

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

    void on_chkPeso_toggled(bool checked);

    void on_txtPesoHorizontal_textEdited();

    void on_txtPesoVertical_textEdited();

    void on_txtPesoDiagonal_textEdited();

    //void on_celMapa_clicked(QFrame* celula);

private:
    Ui::SmartWay *ui;
    QIntValidator *int_validator;
    QDoubleValidator *double_validator;
    QVector<QFrame*> *mapa;

    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void criar_mapa(int altura, int largura);
    void apagar_mapa();
    bool pronto_calculo();

    int comeco_mapa;

    // Flags
    bool mapa_definido;
    bool partida_definida;
    bool chegada_definida;
    bool mostrar_pesos;
};

#endif // SMARTWAY_H
