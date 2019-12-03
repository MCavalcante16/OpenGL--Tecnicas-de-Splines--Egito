#include "spline.h"
#include "gui.h"


Spline::Spline(){
    pontosAtuais = new Vetor3D[4];
    this->setMode(1);
    delta = 0.02;
}

void Spline::setPontosControle(vector<Vetor3D> pontosControle){
    pontosTotais.clear();

    vector<Vetor3D>::iterator it;
    for(it = pontosControle.begin(); it != pontosControle.end(); it++) {
        this->pontosTotais.push_back(*it);
    }

    for(int c = 0; c<pontosTotais.size() && pontosTotais.size() <= 4; c++){
        pontosAtuais[c] = pontosTotais[c];
    }

}



void Spline::setMode(int mode){
    this->mode = mode;


    //Interpoladora
    if(mode == 1){
        float MatrizA[4][4] = {
            {-4.5, 13.5, -13.5,  4.5},
            {   9,-22.5,    18, -4.5},
            {-5.5,    9,  -4.5,    1},
            {    1,   0,     0,    0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                Matriz[i][j] = MatrizA[i][j];
            }
        }
    }

    //Bezier
    else if(mode == 2){
        float MatrizA[][4] = {
            {-1, 3, -3, 1},
            { 3,-6,  3, 0},
            {-3, 3,  0, 0},
            { 1, 0,  0, 0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                Matriz[i][j] = MatrizA[i][j];
            }
        }

    }


    //Hermite
    else if(mode == 3){
        float MatrizA[][4] = {
            { 2,-2,  1,  1},
            {-3, 3, -2, -1},
            { 0, 0,  1,  0},
            { 1, 0,  0,  0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                Matriz[i][j] = MatrizA[i][j];
            }
        }
    }


    //Catmum-rom
    else if(mode == 4){
        float MatrizA[][4] = {
            {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
            { 2/2.0, -5/2.0, 4/2.0, -1/2.0},
            {-1/2.0, 0.0, 1/2.0, 0.0},
            {   0.0, 2/2.0, 0.0, 0.0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                Matriz[i][j] = MatrizA[i][j];
            }
        }
    }

    //Bspline
    else if(mode == 5){
        float MatrizA[][4] = {
            {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
            { 3/6.0, -6/6.0, 3/6.0, 0/6.0},
            {-3/6.0, 0/6.0, 3/6.0, 0/6.0},
            { 1/6.0, 4/6.0, 1/6.0, 0/6.0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                Matriz[i][j] = MatrizA[i][j];
            }
        }
    }

}

int Spline::getMode(){
    return this->mode;
}

Vetor3D Spline::funcaoU(float u){

    Vetor3D result;
    float vetorU[] = {pow(u, 3), pow(u, 2), u, 1};

    //UpxMp
    float upxmp[4];
    for(int i = 0; i<4; i++){
        upxmp[i] = 0;
        for(int j = 0; j<4; j++){
            upxmp[i] += vetorU[j] * Matriz[j][i];
        }
    }


    //xPb
    for(int i = 0; i<4; i++){
        result.x += upxmp[i] * pontosAtuais[i].x;
        result.y += upxmp[i] * pontosAtuais[i].y;
        result.z += upxmp[i] * pontosAtuais[i].z;
    }

    return result;
}

Vetor3D Spline::derivada1(float u){

    Vetor3D result;
    float vetorU[] = {3*pow(u, 2), 2*u, 1, 0};


    //UpxMp
    float upxmp[4];
    for(int i = 0; i<4; i++){
        upxmp[i] = 0;
        for(int j = 0; j<4; j++){
            upxmp[i] += vetorU[j] * Matriz[j][i];
        }
    }

    //xPb
    for(int i = 0; i<4; i++){
        result.x += upxmp[i] * pontosAtuais[i].x;
        result.y += upxmp[i] * pontosAtuais[i].y;
        result.z += upxmp[i] * pontosAtuais[i].z;
    }

    return result;

}

Vetor3D Spline::derivada2(float u){

    Vetor3D result;
    float vetorU[] = {6*u, 2, 0, 0};

    //upxmp
    float upxmp[4];
    for(int i = 0; i<4; i++){
        upxmp[i] = 0;
        for(int j = 0; j<4; j++){
            upxmp[i] += vetorU[j] * Matriz[j][i];
        }
    }

    //pb
    for(int i = 0; i<4; i++){
        result.x += upxmp[i] * pontosAtuais[i].x;
        result.y += upxmp[i] * pontosAtuais[i].y;
        result.z += upxmp[i] * pontosAtuais[i].z;
    }

    return result;

}

void Spline::drawAllTrilho(){

    //For para multiplicar T a cada 4 pontos de controle
    for(int i = 0; i<=pontosTotais.size()-4; i++){

        //Seleciona os proximos 4 pontos
        for(int j = 0; j<4; j++){
            pontosAtuais[j] = pontosTotais[i+j];
        }


        //Desenha nos intervalos de acordo com delta cada trilho
        for(float u = 0; u<=1; u+=delta){

            Vetor3D o = funcaoU(u);
            Vetor3D k = derivada1(u) * (-1);
            Vetor3D up = derivada2(u);
            Vetor3D i = up ^ k;
            Vetor3D j = k ^ i;

            k.normaliza();
            j.normaliza();
            i.normaliza();

            double T[] = {
                i.x, j.x, k.x, o.x,
                i.y, j.y, k.y, o.y,
                i.z, j.z, k.z, o.z,
                0   , 0   , 0   , 1
            };

            //Desenha o trilho no ponto gerado
            glPushMatrix();
                glColor3f(0, 0, 0);
                glMultTransposeMatrixd(T);
                draw1Trilho();
            glPopMatrix();

        }
    }

}

//Desenhar 1 trilho
void Spline::draw1Trilho(){

            glPushMatrix();
                GUI::setColor(1,1,1);
                glScaled(1, 0.1, 1);
                glColor3f(0.7, 0.4, 0.15);
                glutSolidCube(0.5);
                //GUI::drawSphere(0,0,0,0.01);
            glPopMatrix();


}

void Spline::upDelta() {
    double v = 0.001;
    if(delta + v >= 1) {
        delta = 1;
    } else {
        delta += v;
    }
}

void Spline::downDelta() {
    double v = 0.001;
    if(delta - v <= 0) {
        delta = v;
    } else {
        delta -= v;
    }
}

