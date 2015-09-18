#include "smartway.h"
#include "ui_smartway.h"
#include <float.h>
#include <algoritmos_busca.h>

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

        partida = nullptr;
        partida_definida = false;

        chegada = nullptr;
        chegada_definida = false;

        apagar_mapa(ui->txtAltura->text().toInt());
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

        ui->btnCalcular->setEnabled(false);

        criar_mapa(ui->txtAltura->text().toInt(), ui->txtLargura->text().toInt());
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

void SmartWay::on_tabelaMapa_itemClicked(QTableWidgetItem *item)
{
    QIcon icon;

    if (isPartida(item))
    {
        if (ui->radioPartida->isChecked())
        {
            partida->set_p_pai(nullptr);
            partida->set_pai(nullptr);
            partida = nullptr;
            mapa[item->row()][item->column()].set_tipo(LIVRE);
            icon.addFile(QStringLiteral(":"), QSize(), QIcon::Normal, QIcon::Off);
            partida_definida = false;
            item->setIcon(icon);
        }
    }
    else if (isChegada(item))
    {
        if (ui->radioChegada->isChecked())
        {
            chegada = nullptr;
            mapa[item->row()][item->column()].set_tipo(LIVRE);
            icon.addFile(QStringLiteral(":"), QSize(), QIcon::Normal, QIcon::Off);
            chegada_definida = false;
            item->setIcon(icon);
        }
    }
    else if (isObstaculo(item))
    {
        if (ui->radioObstaculos->isChecked())
        {
            mapa[item->row()][item->column()].set_tipo(LIVRE);
            icon.addFile(QStringLiteral(":"), QSize(), QIcon::Normal, QIcon::Off);
            item->setIcon(icon);
        }
    }
    else
    {
        if (ui->radioPartida->isChecked() && !partida_definida)
        {
            partida = &mapa[item->row()][item->column()];
            partida->set_p_pai(partida);
            partida->set_pai(partida);
            mapa[item->row()][item->column()].set_tipo(PARTIDA);
            icon.addFile(QStringLiteral(":/imagens/largada_1.png"), QSize(), QIcon::Normal, QIcon::Off);
            partida_definida = true;
            item->setIcon(icon);
        }
        else if (ui->radioChegada->isChecked() && !chegada_definida)
        {
            chegada = &mapa[item->row()][item->column()];
            mapa[item->row()][item->column()].set_tipo(CHEGADA);
            icon.addFile(QStringLiteral(":/imagens/chegada_1.png"), QSize(), QIcon::Normal, QIcon::Off);
            chegada_definida = true;
            item->setIcon(icon);
        }
        else if (ui->radioObstaculos->isChecked())
        {
            mapa[item->row()][item->column()].set_tipo(OBSTACULO);
            icon.addFile(getObstaculo(), QSize(), QIcon::Normal, QIcon::Off);
            item->setIcon(icon);
        }
    }
    ui->btnCalcular->setEnabled(pronto_calculo());
}

void SmartWay::on_comboAlgoritmo_currentIndexChanged(int index)
{
    ui->btnCalcular->setEnabled(pronto_calculo());
    alg_select = index;
}

void SmartWay::on_btnCalcular_clicked()
{
    if (ui->comboAlgoritmo->currentIndex() == 0){
        chegada->set_h(0);
        calcular_heuristica(mapa,
                            ui->txtAltura->text().toInt(),
                            ui->txtLargura->text().toInt(),
                            chegada);
        a_estrela(partida,
                  ui->txtPesoHorizontal->text().toDouble(),
                  ui->txtPesoVertical->text().toDouble(),
                  ui->txtPesoDiagonal->text().toDouble());
    }

    if (ui->comboAlgoritmo->currentIndex() == 1)
    {
        chegada->set_h(DBL_MAX);
        busca_prof(partida, chegada,
                   ui->txtPesoVertical->text().toDouble(),
                   ui->txtPesoHorizontal->text().toDouble(),
                   ui->txtPesoDiagonal->text().toDouble());

        marcar_rota(chegada);
    }
}

void SmartWay::apagar_mapa(int altura)
{
    ui->tabelaMapa->setRowCount(0);
    ui->tabelaMapa->setColumnCount(0);

    for (int i = 0; i < altura; ++i)
        delete [] mapa[i];
    delete [] mapa;

}

void SmartWay::criar_mapa(int altura, int largura)
{
    ui->tabelaMapa->setRowCount(altura);
    ui->tabelaMapa->setColumnCount(largura);

    mapa = new Celula*[altura];

    for (int i = 0; i < altura; i++)
        mapa[i] = new Celula[largura];

    QTableWidgetItem *item;
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            item = new QTableWidgetItem();
            ui->tabelaMapa->setItem(i, j, item);

            mapa[i][j].set_tipo(LIVRE);
            mapa[i][j].set_p_pai(nullptr);
            mapa[i][j].set_pai(nullptr);
            mapa[i][j].set_item(item);
            if (i > 0)
                mapa[i][j].set_vizinho(&mapa[i-1][ j ], 0);
            else
                mapa[i][j].set_vizinho(nullptr, 0);

            if (i > 0 && j+1 < largura)
                mapa[i][j].set_vizinho(&mapa[i-1][j+1], 1);
            else
                mapa[i][j].set_vizinho(nullptr, 1);

            if (j+1 < largura)
                mapa[i][j].set_vizinho(&mapa[ i ][j+1], 2);
            else
                mapa[i][j].set_vizinho(nullptr, 2);

            if (i+1 < altura && j+1 < largura)
                mapa[i][j].set_vizinho(&mapa[i+1][j+1], 3);
            else
                mapa[i][j].set_vizinho(nullptr, 3);

            if (i+1 < altura)
                mapa[i][j].set_vizinho(&mapa[i+1][ j ], 4);
            else
                mapa[i][j].set_vizinho(nullptr, 4);

            if (i+1 < altura && j > 0)
                mapa[i][j].set_vizinho(&mapa[i+1][j-1], 5);
            else
                mapa[i][j].set_vizinho(nullptr, 5);

            if (j > 0)
                mapa[i][j].set_vizinho(&mapa[ i ][j-1], 6);
            else
                mapa[i][j].set_vizinho(nullptr, 6);

            if (i > 0 && j > 0)
                mapa[i][j].set_vizinho(&mapa[i-1][j-1], 7);
            else
                mapa[i][j].set_vizinho(nullptr, 7);
        }
    }
}

bool SmartWay::pronto_calculo()
{
    return (partida_definida
            && chegada_definida
            && mapa_definido
            && !ui->txtPesoDiagonal->text().isEmpty()
            && !ui->txtPesoHorizontal->text().isEmpty()
            && !ui->txtPesoVertical->text().isEmpty()
            && ui->comboAlgoritmo->currentIndex() != -1);
}

bool SmartWay::isPartida(QTableWidgetItem *item)
{
    return mapa[item->row()][item->column()].get_tipo() == PARTIDA ? true : false;;
}

bool SmartWay::isChegada(QTableWidgetItem *item)
{
    return mapa[item->row()][item->column()].get_tipo() == CHEGADA ? true : false;
}

bool SmartWay::isObstaculo(QTableWidgetItem *item)
{
    return mapa[item->row()][item->column()].get_tipo() == OBSTACULO ? true : false;
}

QString SmartWay::getObstaculo()
{
    int i = rand() % 9;
    switch (i) {
    case 0:
        return QStringLiteral(":/imagens/obs_1.png");
        break;
    case 1:
        return QStringLiteral(":/imagens/obs_2.png");
        break;
    case 2:
        return QStringLiteral(":/imagens/obs_3.png");
        break;
    case 3:
        return QStringLiteral(":/imagens/obs_4.png");
        break;
    case 4:
        return QStringLiteral(":/imagens/obs_5.png");
        break;
    case 5:
        return QStringLiteral(":/imagens/obs_6.png");
        break;
    case 6:
        return QStringLiteral(":/imagens/obs_7.png");
        break;
    case 7:
        return QStringLiteral(":/imagens/obs_8.png");
        break;
    case 8:
        return QStringLiteral(":/imagens/obs_9.png");
        break;
    default:
        return QStringLiteral(":");
        break;
    }
}
