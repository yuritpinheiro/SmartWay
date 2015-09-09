#ifndef CELULA_H
#define CELULA_H

#define PARTIDA 0
#define CHEGADA 1
#define OBSTACULO 2
#define LIVRE 3

class Celula
{
public:
    Celula();
    int getF();
    void setF(int f);

    int getG();
    void setG(int g);

    int getH();
    void setH(int h);

    int getTipo();
    void setTipo(int tipo);

    Celula *getPai();
    void setPai(Celula *pai);

private:
    int f, g, h;
    int tipo;
    Celula *pai;
};

#endif // CELULA_H
