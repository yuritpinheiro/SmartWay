#include "celula.h"

Celula::Celula()
{
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->tipo = LIVRE;
}

int Celula::getF()
{
    return this->f;
}

void Celula::setF(int f)
{
    this->f = f;
}


int Celula::getG()
{
    return this->g;
}

void Celula::setG(int g)
{
    this->g = g;
}


int Celula::getH()
{
    return this->h;
}

void Celula::setH(int h)
{
    this->h = h;
}


int Celula::getTipo()
{
    return this->tipo;
}

void Celula::setTipo(int tipo)
{
    this->tipo = tipo;
}
