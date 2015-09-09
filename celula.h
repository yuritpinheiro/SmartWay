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
    int get_f();
    void set_f(int f);

    int get_g();
    void set_g(int g);

    int get_h();
    void set_h(int h);

    int get_tipo();
    void set_tipo(int tipo);

    Celula *get_pai();
    void set_pai(Celula *pai);

    Celula *get_p_pai();
    void set_p_pai(Celula *p_pai);

private:
    int f, g, h;
    int tipo;
    Celula *pai, *p_pai;
};

#endif // CELULA_H
