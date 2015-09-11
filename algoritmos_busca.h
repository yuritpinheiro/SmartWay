#ifndef ALGORITMOS_BUSCA
#define ALGORITMOS_BUSCA
#include <celula.h>

/* Algoritmo A* */



/* --------------------- */

/* Busca em profundidade */

void definir_rota(Celula *celula);
void busca_profundidade(Celula *partida, Celula *chegada, double peso_v, double peso_h, double peso_d);

void definir_rota(Celula *celula)
{
    if (celula->get_p_pai() != celula)
    {
        celula->set_pai(celula->get_p_pai());
        definir_rota(celula->get_pai());
    }
}

void busca_profundidade(Celula *partida, Celula *chegada, double peso_v, double peso_h, double peso_d)
{
    if (partida == chegada)
    {
        if (partida->get_g() < partida->get_h())
        {
            partida->set_h(partida->get_g());
            definir_rota(partida);
        }
        // Definir melhor rota

    } else {
        for (int i = 0; i < 8; i++)
        {
            if (partida->get_vizinho(i) != nullptr
                    && partida->get_vizinho(i)->get_p_pai() == nullptr
                    && partida->get_vizinho(i)->get_tipo() != OBSTACULO)
            {
                partida->get_vizinho(i)->set_g(partida->get_g() + (i % 2 == 0 ? (i % 4 == 0 ? peso_v : peso_h) : peso_d));
                partida->get_vizinho(i)->set_p_pai(partida);
                busca_profundidade(partida->get_vizinho(i), chegada, peso_v, peso_h, peso_d);
                partida->get_vizinho(i)->set_p_pai(nullptr);
                partida->get_vizinho(i)->set_g(0);
            }
        }
    }
}

/* --------------------- */

#endif // ALGORITMOS_BUSCA

