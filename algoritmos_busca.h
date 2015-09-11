#ifndef ALGORITMOS_BUSCA
#define ALGORITMOS_BUSCA
#include <celula.h>

/* Algoritmo A* */



/* --------------------- */

/* Busca em profundidade */

void busca_profundidade(Celula *partida, Celula *chegada)
{
    if (partida == chegada){
        if (partida->get_g() < partida->get_h())
             definir_rota(partida);
        // Definir melhor rota

    } else {
        for (int i = 0; i < 8; i++){
            if (partida->get_vizinho(i) != nullptr
                    && partida->get_vizinho(i)->get_p_pai() == nullptr
                    && partida->get_vizinho(i)->get_tipo() != OBSTACULO){
                partida->get_vizinho(i)->set_g(partida->get_g() + (i % 2 == 0 ? (i % 4 == 0 ? peso_v : peso_h) : peso_d));
                partida->get_vizinho(i)->set_p_pai(partida);
                busca_profundidade(partida->get_vizinho(i), chegada);
            }
        }

        for (int i = 0; i < 8; i++){
            if (partida->get_vizinho(i) != nullptr){
                partida->get_vizinho(i)->set_p_pai(nullptr);
            }
        }
    }
}

/* --------------------- */

#endif // ALGORITMOS_BUSCA

