#include "celula.h"

Celula::Celula()
{
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->tipo = LIVRE;
}

int Celula::get_f()
{
    return this->f;
}

void Celula::set_f(int f)
{
    this->f = f;
}


int Celula::get_g()
{
    return this->g;
}

void Celula::set_g(int g)
{
    this->g = g;
}


int Celula::get_h()
{
    return this->h;
}

void Celula::set_h(int h)
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


Celula * Celula::get_p_pai()
{
    return this->p_pai;
}

void Celula::set_p_pai(Celula * p_pai)
{
    this->p_pai = p_pai;
}
