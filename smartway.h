#ifndef SMARTWAY_H
#define SMARTWAY_H

#include <QMainWindow>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QVector>
#include <QSpacerItem>
#include <QPushButton>
#include <QSignalMapper>
#include <QTableWidgetItem>
#include <celula.h>
#include <QGenericMatrix>
#include <QString>
#include <busca.h>

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

    void on_tabelaMapa_itemClicked(QTableWidgetItem *item);

    void on_comboAlgoritmo_currentIndexChanged(int index);

    void on_btnCalcular_clicked();

private:
    Ui::SmartWay *ui;
    QIntValidator *int_validator;
    QDoubleValidator *double_validator;

    QSignalMapper *mapa_sinais;

    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void criar_mapa(int altura, int largura);
    void apagar_mapa(int altura);
    bool pronto_calculo();
    bool isPartida(QTableWidgetItem *item);
    bool isChegada(QTableWidgetItem *item);
    bool isObstaculo(QTableWidgetItem *item);

    QString getObstaculo();

    Celula ** mapa;

    Celula *partida, *chegada;

    // Flags
    bool mapa_definido;
    bool partida_definida;
    bool chegada_definida;
    bool mostrar_pesos;
    bool rota_definida = false;

    int alg_select;
};

#endif // SMARTWAY_H
