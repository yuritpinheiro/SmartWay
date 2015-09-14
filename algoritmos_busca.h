#ifndef ALGORITMOS_BUSCA
#define ALGORITMOS_BUSCA
#include <celula.h>
#include <queue>
#include <vector>

/* Algoritmo A* */

using namespace std;

struct avaliar_caminho
{
    bool operator()(const Celula& a,const Celula& b) const
    {
        return a.f < b.f;
    }
};

void a_estrela(Celula *partida, double h, double v, double d){
    priority_queue<Celula, vector<Celula>, avaliar_caminho> fila;

    Celula *aux = partida;
    double custo_horizontal = h; //recebo da interface
    double custo_vertical = v;
    double custo_diagonal = d;
    double g = 0, f;


    aux->set_g(0);
    while(aux->get_tipo()!= CHEGADA){

        for(int i = 0; i < 8; i++){
            if( aux->get_vizinho(i) != nullptr && aux->get_vizinho(i)->get_tipo() == LIVRE){

                    if(i == 1 || i == 5){
                        g = custo_vertical + aux->get_g();
                    }else if(i == 3 || i == 7){
                        g = custo_horizontal + aux->get_g();;
                    }else{
                        g = custo_diagonal + aux->get_g();;
                    }

                    f = g + aux->get_vizinho(i)->get_h();

                    if(aux->get_vizinho(i)->get_pai()== nullptr || (aux->get_vizinho(i)->get_pai()!= nullptr && aux->get_vizinho(i)->get_g() < g)){
                        aux->get_vizinho(i)->set_pai(aux);
                        aux->get_vizinho(i)->set_g(g);
                        aux->get_vizinho(i)->set_f(f);
                        //fila.push(aux->get_vizinho(i));
                    }
            }
        }

        //aux = fila.top();
        fila.pop();
    }

        //priotity_queue.pop();

}
        //teste dos irmãos ??

/* --------------------- */

/* Busca em profundidade */



/* --------------------- */

#endif // ALGORITMOS_BUSCA

