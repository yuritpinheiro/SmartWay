#ifndef ALGORITMOS_BUSCA
#define ALGORITMOS_BUSCA
#include <celula.h>
#include <queue>
#include <vector>

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
    while(aux->get_tipo() != CHEGADA){

        for(int i = 0; i < 8; i++){
            if( aux->get_vizinho(i) != nullptr && aux->get_vizinho(i)->get_tipo() == LIVRE){

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

        aux = fila.top();
        fila.pop();
    }
}

/* --------------------- */

/* Busca em profundidade */

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
    if (celula->get_p_pai() != celula)
    {
        celula->get_item()->setBackgroundColor(Qt::green);
        marcar_rota(celula->get_pai());
    }
}

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

