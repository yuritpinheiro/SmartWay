#ifndef ALGORITMOS_BUSCA
#define ALGORITMOS_BUSCA
#include <celula.h>
#include <queue>
#include <vector>

void definir_rota(Celula *celula)
{
    if (celula->get_p_pai() != celula)
    {
        celula->set_pai(celula->get_p_pai());
        definir_rota(celula->get_pai());
    }
}


void marcar_rota(Celula *celula)
{
    QIcon icon;
    if (celula->get_tipo() != PARTIDA)
    {
        Celula *p = celula->get_pai();
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
        if (celula->get_tipo() == CHEGADA)
        {
            icon.addFile(QStringLiteral(":/imagens/chegada_2.png"), QSize(), QIcon::Normal, QIcon::Off);
            celula->get_item()->setIcon(icon);
        }
        marcar_rota(celula->get_pai());
    }
    else
    {
        icon.addFile(QStringLiteral(":/imagens/largada_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        celula->get_item()->setIcon(icon);
    }
}

/* Algoritmo A* */

void calcular_heuristica(Celula ** mapa, int altura, int largura, Celula* chegada)
{
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            mapa[i][j].set_h(abs(chegada->get_x() - i) + abs(chegada->get_y() - j));
        }
    }
}

void a_estrela(Celula *partida, double h, double v, double d){
    std::priority_queue<Celula*, std::vector<Celula*>, avaliar_custo> fila;

    Celula *aux = partida;
    double custo_horizontal = h; //recebo da interface
    double custo_vertical = v;
    double custo_diagonal = d;
    double g, f;

    aux->set_g(0);
    //int a = -2;
    while(aux->get_tipo() != CHEGADA){

        for(int i = 0; i < 8; i++){
            if( aux->get_vizinho(i) != nullptr && aux->get_vizinho(i)->get_tipo() != OBSTACULO){

                if(i == 0 || i == 4){
                    g = custo_vertical + aux->get_g();
                }else if(i == 2 || i == 6){
                    g = custo_horizontal + aux->get_g();;
                }else{
                    g = custo_diagonal + aux->get_g();;
                }

                f = g + aux->get_vizinho(i)->get_h();

                if(aux->get_vizinho(i)->get_pai()== nullptr || (aux->get_vizinho(i)->get_pai()!= nullptr && aux->get_vizinho(i)->get_g() > g)){
                    aux->get_vizinho(i)->set_pai(aux);
                    aux->get_vizinho(i)->set_g(g);
                    aux->get_vizinho(i)->set_f(f);
                    fila.push(aux->get_vizinho(i));

                }
            }
        }

        //a = fila.top()->get_tipo();
        aux = fila.top();


        fila.pop();
    }

   marcar_rota(aux->get_pai());
}

/* --------------------- */

/* Busca em profundidade */

void busca_prof(Celula *partida, Celula *chegada, int peso_h, int peso_v, int peso_d)
{
    if (partida != chegada)
    {
        //partida->get_item()->setBackground(Qt::red);
        for (int i = 0; i < 8; i++)
        {
            Celula *v = partida->get_vizinho(i);
            if (v != nullptr && v->get_tipo() != OBSTACULO && v->get_p_pai() == nullptr )
            {
                v->set_g(partida->get_g() + (i % 2 ? peso_d : (i % 4 ? peso_h : peso_v)));
                v->set_p_pai(partida);

                busca_prof(v, chegada, peso_h, peso_v, peso_d);

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

/* --------------------- */

#endif // ALGORITMOS_BUSCA

