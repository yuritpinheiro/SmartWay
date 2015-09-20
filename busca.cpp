#include "busca.h"

Busca::Busca(Celula *partida, Celula *chegada, int peso_h, int peso_v, int peso_d)
{
    this->partida = partida;
    this->chegada = chegada;
    this->peso_h = peso_h;
    this->peso_v = peso_v;
    this->peso_d = peso_d;
}

void Busca::run(){
    busca_prof(partida);

    if(chegada->get_pai() != nullptr)
    {
        marcar_rota(chegada);
        //*rota_definida = true;
    }
    else
    {
        QIcon i;
        i.addFile(QStringLiteral(":"), QSize());
        chegada->get_item()->setIcon(i);
        chegada->get_item()->setText("X");
    }
}

void Busca::definir_rota(Celula *celula)
{
    if (celula->get_p_pai() != celula)
    {
        celula->set_pai(celula->get_p_pai());
        definir_rota(celula->get_pai());
    }
}

void Busca::marcar_rota(Celula *celula)
{
    QIcon icon;
    Celula *p = celula->get_pai();
    if (p->get_tipo() != PARTIDA)
    {
        if (p->get_x() > celula->get_x())
        {
            if (p->get_y() > celula->get_y())
            {
                icon.addFile(QStringLiteral(":/imagens/no.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else if (p->get_y() < celula->get_y())
            {
                icon.addFile(QStringLiteral(":/imagens/so.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else
            {
                icon.addFile(QStringLiteral(":/imagens/o.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
        }
        else if (p->get_x() < celula->get_x())
        {
            if (p->get_y() > celula->get_y())
            {
                icon.addFile(QStringLiteral(":/imagens/nd.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else if (p->get_y() < celula->get_y())
            {
                icon.addFile(QStringLiteral(":/imagens/sd.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else
            {
                icon.addFile(QStringLiteral(":/imagens/l.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
        }
        else
        {
            if (p->get_y() > celula->get_y())
            {
                icon.addFile(QStringLiteral(":/imagens/n.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else
            {
                icon.addFile(QStringLiteral(":/imagens/s.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
        }

        celula->get_pai()->get_item()->setIcon(icon);
        celula->get_pai()->get_item()->setBackgroundColor(Qt::green);
        if (celula->get_tipo() == CHEGADA)
        {
            icon.addFile(QStringLiteral(":/imagens/chegada_2.png"), QSize(), QIcon::Normal, QIcon::Off);
            celula->get_item()->setIcon(icon);
            celula->get_item()->setBackgroundColor(Qt::green);
        }
        marcar_rota(celula->get_pai());
    }
    else
    {
        icon.addFile(QStringLiteral(":/imagens/largada_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        p->get_item()->setIcon(icon);
        p->get_item()->setBackgroundColor(Qt::green);
    }
}

void Busca::busca_prof(Celula *partida){
    if (partida != chegada)
    {
        for (int i = 0; i < 8; i++)
        {
            Celula *v = partida->get_vizinho(i);
            if (v != nullptr && v->get_tipo() != OBSTACULO && v->get_p_pai() == nullptr )
            {
                v->set_g(partida->get_g() + (i % 2 ? peso_d : (i % 4 ? peso_h : peso_v)));
                v->set_p_pai(partida);
                v->get_item()->setBackgroundColor(Qt::darkGreen);

                busca_prof(v);

                v->get_item()->setBackgroundColor(Qt::white);
                v->set_g(0);
                v->set_p_pai(nullptr);
            }
        }
    }
    else
    {
        if (partida->get_h() > partida->get_g())
        {
            partida->set_h(partida->get_g());
            definir_rota(partida);
        }
    }
}
