#ifndef CELULA_H
#define CELULA_H

#define PARTIDA 0
#define CHEGADA 1
#define OBSTACULO 2
#define LIVRE 3

#include <QTableWidgetItem>
#include <functional>

class Celula
{
public:
    Celula();
    double get_f() const;
    void set_f(double f);

    double get_g();
    void set_g(double g);

    double get_h();
    void set_h(double h);

    int get_tipo();
    void set_tipo(int tipo);

    int get_x();
    void set_x(int x);

    int get_y();
    void set_y(int y);

    Celula *get_pai();
    void set_pai(Celula *pai);

    Celula *get_p_pai();
    void set_p_pai(Celula *p_pai);

    Celula *get_vizinho(int i);
    void set_vizinho(Celula *vizinho, int i);

    QTableWidgetItem *get_item();
    void set_item(QTableWidgetItem *item);

private:

    int tipo;
    int x, y;
    double f, g, h;
    Celula *pai, *p_pai;
    Celula *vizinhos[8];
    QTableWidgetItem *item;

    /*
     ___________
    |_7_|_0_|_1_|
    |_6_|_x_|_2_|
    |_5_|_4_|_3_|
    */

};

struct avaliar_custo : public std::binary_function<Celula*, Celula*, bool>
{
    bool operator()(const Celula* lhs, const Celula* rhs) const
    {
        return lhs->get_f() > rhs->get_f();
    }
};

#endif // CELULA_H
