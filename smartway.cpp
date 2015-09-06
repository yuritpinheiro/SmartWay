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

        SmartWay::apagar_mapa(ui->txtAltura->text().toInt(), ui->txtLargura->text().toInt());
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

        SmartWay::criar_mapa(ui->txtAltura->text().toInt(), ui->txtLargura->text().toInt());
    }
}

void SmartWay::on_chkPeso_toggled(bool checked)
{
    mostrar_pesos = checked;
}

void SmartWay::on_txtPesoHorizontal_textEdited()
{
    ui->btnCalcular->setEnabled(pronto_calculo());
}

void SmartWay::on_txtPesoVertical_textEdited()
{
    ui->btnCalcular->setEnabled(pronto_calculo());
}

void SmartWay::on_txtPesoDiagonal_textEdited()
{
    ui->btnCalcular->setEnabled(pronto_calculo());
}

void SmartWay::apagar_mapa(int altura, int largura)
{

}

void SmartWay::criar_mapa(int altura, int largura)
{
    mapa = new QVector<QFrame*>(altura*largura);
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            mapa->insert(i + j, new QFrame());
            mapa->at(i + j)->setMinimumSize(48,48);
            mapa->at(i + j)->setMaximumSize(48,48);
            mapa->at(i + j)->setFrameShape(QFrame::StyledPanel);
            mapa->at(i + j)->setFrameShadow(QFrame::Raised);
            ui->gridLayout->addWidget(mapa->at(i + j), i, j, 1, 1, 0);
        }
    }
    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->gridLayout->addItem(horizontalSpacer, 0, largura, 1, 1);

    QSpacerItem *verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->gridLayout->addItem(verticalSpacer_2, altura, 0, 1, 1);
}

bool SmartWay::pronto_calculo()
{
    return (partida_definida
            && chegada_definida
            && mapa_definido
            && !ui->txtPesoDiagonal->text().isEmpty()
            && !ui->txtPesoHorizontal->text().isEmpty()
            && !ui->txtPesoVertical->text().isEmpty());
}
