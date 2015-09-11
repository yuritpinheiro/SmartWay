#include "celula.h"

Celula::Celula()
{
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->tipo = LIVRE;
}

double Celula::get_f()
{
    return this->f;
}

void Celula::set_f(double f)
{
    this->f = f;
}


double Celula::get_g()
{
    return this->g;
}

void Celula::set_g(double g)
{
    this->g = g;
}


double Celula::get_h()
{
    return this->h;
}

void Celula::set_h(double h)
{
    this->h = h;
}


int Celula::get_tipo()
{
    return this->tipo;
}

void Celula::set_tipo(int tipo)
{
    this->tipo = tipo;
}


Celula * Celula::get_pai()
{
    return this->pai;
}

void Celula::set_pai(Celula * pai)
{
    this->pai = pai;
}


Celula* Celula::get_p_pai()
{
    return this->p_pai;
}

void Celula::set_p_pai(Celula * p_pai)
{
    this->p_pai = p_pai;
}

Celula * Celula::get_vizinho(int i)
{
    return this->vizinhos[i];
}

void Celula::set_vizinho(Celula * vizinho, int i)
{
    this->vizinhos[i] = vizinho;
}
