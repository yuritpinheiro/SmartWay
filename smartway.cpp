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

    mapa_definido = false;
    partida_definida = false;
    chegada_definida = false;
    mostrar_pesos = false;
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

        SmartWay::apagar_mapa();
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

void SmartWay::on_celMapa_clicked(int celula)
{
    //mapa->at(celula)->setIcon();
    if (ui->radioPartida->isChecked())
    {
        //ui->radioPartida->setChecked(false);
        if (!partida_definida)
        {
            mapa->at(celula)->setText("P");
            partida_definida = true;
            partida = celula;
        }
//        else if (celula == partida)
//        {
//            mapa->at(celula)->setText("");
//            partida_definida = false;
//            partida = -1;
//        }
    }

    if (ui->radioChegada->isChecked())
    {
        //ui->radioPartida->setChecked(false);
        if (!chegada_definida)
        {
            mapa->at(celula)->setText("C");
            chegada_definida = true;
            chegada = celula;
        }
//        else if (celula == partida)
//        {
//            mapa->at(celula)->setText("");
//            partida_definida = false;
//            partida = -1;
//        }
    }

    if (ui->radioObstaculos->isChecked())
    {
        //ui->radioPartida->setChecked(false);
        mapa->at(celula)->setText("O");
        partida_definida = true;
        partida = celula;
//        else if (celula == partida)
//        {
//            mapa->at(celula)->setText("");
//            partida_definida = false;
//            partida = -1;
//        }
    }
    ui->btnCalcular->setEnabled(pronto_calculo());
}

void SmartWay::apagar_mapa()
{
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != 0)
    {
        if (child->widget())
            child->widget()->setParent(NULL);
        ui->gridLayout->removeItem(child);

        delete child;
    }
}

void SmartWay::criar_mapa(int altura, int largura)
{
    mapa = new QVector<QPushButton*>(altura*largura);
    mapa_sinais = new QSignalMapper(this);
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            int k = i + (j * largura);
            mapa->replace(k, new QPushButton());
            mapa->at(k)->setMinimumSize(48,48);
            mapa->at(k)->setMaximumSize(48,48);

            mapa_sinais->setMapping(mapa->at(k), k);

            connect(mapa->at(k), SIGNAL(clicked()), mapa_sinais, SLOT(map()));

            connect(mapa_sinais, SIGNAL(mapped(int)), this, SLOT(on_celMapa_clicked(int)));

            ui->gridLayout->addWidget(mapa->at(k), i, j, 1, 1, 0);
        }
    }
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->gridLayout->addItem(horizontalSpacer, 0, largura, 1, 1);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
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
