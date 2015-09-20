#ifndef BUSCA_H
#define BUSCA_H

#include <QThread>
#include <celula.h>

class Busca : public QThread
{
private:
    void run();

    void busca_prof(Celula *partida);
    void definir_rota(Celula *celula);
    void marcar_rota(Celula *celula);
    Celula *partida, *chegada;
    int peso_h, peso_v, peso_d;

public:
    Busca(Celula *partida, Celula *chegada, int peso_h, int peso_v, int peso_d);
};

#endif // BUSCA_H
