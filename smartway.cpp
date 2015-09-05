#include "smartway.h"
#include "ui_smartway.h"

SmartWay::SmartWay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartWay)
{
    ui->setupUi(this);

    int_validator = new QIntValidator(this);
    ui->txtAltura->setValidator(int_validator);
    ui->txtLargura->setValidator(int_validator);
    double_validator = new QDoubleValidator(this);
    ui->txtPesoDiagonal->setValidator(double_validator);
    ui->txtPesoHorizontal->setValidator(double_validator);
    ui->txtPesoVertical->setValidator(double_validator);

}

SmartWay::~SmartWay()
{
    delete ui;
}
void SmartWay::on_txtAltura_textEdited()
{
    if(ui->txtAltura->text().isEmpty() || ui->txtLargura->text().isEmpty()){
        ui->btnDefinirMapa->setEnabled(false);
    } else {
        ui->btnDefinirMapa->setEnabled(true);
    }
}

void SmartWay::on_txtLargura_textEdited()
{
    if(ui->txtAltura->text().isEmpty() || ui->txtLargura->text().isEmpty()){
        ui->btnDefinirMapa->setEnabled(false);
    } else {
        ui->btnDefinirMapa->setEnabled(true);
    }
}

void SmartWay::on_btnDefinirMapa_clicked()
{
    if (mapa_definido){
        mapa_definido = false;

        // Desbloquear entrada de largura e altura
        ui->txtAltura->setEnabled(true);
        ui->txtLargura->setEnabled(true);
        ui->btnDefinirMapa->setText("Definir Área");

        // Bloquear seleção de marcações
        ui->radioChegada->setEnabled(false);
        ui->radioObstaculos->setEnabled(false);
        ui->radioPartida->setEnabled(false);

        // Bloquear entrada de pesos
        ui->txtPesoDiagonal->setEnabled(false);
        ui->txtPesoHorizontal->setEnabled(false);
        ui->txtPesoVertical->setEnabled(false);

        SmartWay::apagarMapa();
    } else {
        mapa_definido = true;

        // Bloquear entrada de largura e altura
        ui->txtAltura->setEnabled(false);
        ui->txtLargura->setEnabled(false);
        ui->btnDefinirMapa->setText("Redefinir Área");

        // Desbloquear seleção de marcações
        ui->radioChegada->setEnabled(true);
        ui->radioObstaculos->setEnabled(true);
        ui->radioPartida->setEnabled(true);

        // Desbloquear entrada de pesos
        ui->txtPesoDiagonal->setEnabled(true);
        ui->txtPesoHorizontal->setEnabled(true);
        ui->txtPesoVertical->setEnabled(true);

        SmartWay::criarMapa();
    }
}

void SmartWay::apagarMapa()
{

}

void SmartWay::criarMapa()
{

}

void SmartWay::on_chkPeso_toggled(bool checked)
{
    mostrar_pesos = checked;
}
