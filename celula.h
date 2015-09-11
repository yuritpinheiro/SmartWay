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
    double get_f();
    void set_f(double f);

    double get_g();
    void set_g(double g);

    double get_h();
    void set_h(double h);

    int get_tipo();
    void set_tipo(int tipo);

    Celula *get_pai();
    void set_pai(Celula *pai);

    Celula *get_p_pai();
    void set_p_pai(Celula *p_pai);

    Celula *get_vizinho(int i);
    void set_vizinho(Celula *vizinho, int i);

private:
    double f, g, h;
    int tipo;
    Celula *pai, *p_pai;
    Celula *vizinhos[8];

    /*
     ___________
    |_7_|_0_|_1_|
    |_6_|_x_|_2_|
    |_5_|_4_|_3_|
    */

};

#endif // CELULA_H
