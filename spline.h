#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "bib/Vetor3D.h"
#include <vector>
#include "bib/Desenha.h"

using namespace std;

class Spline
{
public:
    Spline();

    int mode;
    float delta;
    float Matriz[4][4];
    Vetor3D* pontosAtuais;
    vector<Vetor3D> pontosTotais;


    Vetor3D funcaoU(float u);
    Vetor3D derivada1(float u);
    Vetor3D derivada2(float u);

    void setPontosControle(vector<Vetor3D> pontosControle);

    void drawAllTrilho();
    void draw1Trilho();
    void upDelta();
    void downDelta();



    void setMode(int mode);
    int getMode();



};

#endif // SPLINE_H
