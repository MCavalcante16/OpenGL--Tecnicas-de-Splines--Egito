//#include "trilho.h"

////Construtor
//Spline::Spline()
//{
//    this->Mode(3);
//    pontos = new Vetor3D[4];
//    delta = 0.1f;

//}

////cria pontos de controle
//void Spline::geraPontosControle(vector<Vetor3D> pontosControle){
//    pontosC.clear();

//    vector<Vetor3D>::iterator it;
//    for(it=pontosControle.begin(); it != pontosControle.end(); it++){
//        pontosC.push_back(*it);
//    }
//    for(int c = 0; c<pontosC.size() && pontosC.size()<=4; c++){
//        pontos[c] = pontosC[c];
//    }
//}




//void Spline::Mode(int m){
//    this->tipo = m;
//    //Interpoladora
//    if(m==0){
//        float MatrizAux[4][4] = {
//            {-4.5, 13.5, -13.5, 4.5},
//            {   9,-22.5,    18,-4.5},
//            {-5.5,    9,  -4.5,   1},
//            {    1,   0,     0,   0}
//        };

//        for(int i = 0; i<4; i++){
//            for(int j = 0; j<4; j++){
//                Matriz[i][j] = MatrizAux[i][j];
//            }
//        }
//    }

//    //Bezier
//    if(m==1){
//        float MatrizAux[4][4] = {
//            {-1, 3, -3, 1},
//            {3, -6, 3, 0},
//            {-3, 3, 0, 0},
//            {1, 0, 0, 0}
//        };


//        for(int i = 0; i<4; i++){
//            for(int j = 0; j<4; j++){
//                Matriz[i][j] = MatrizAux[i][j];
//            }
//        }
//    }

//    //Hermite
//    if(m==2){
//        float MatrizAux[4][4] = {
//            {2, -2, 1, 1},
//            {-3, 3, -2, -1},
//            {0, 0, 1, 0},
//            {1, 0, 0, 0}
//        };

//        for(int i = 0; i<4; i++){
//            for(int j = 0; j<4; j++){
//                Matriz[i][j] = MatrizAux[i][j];
//            }
//        }
//    }


//    //Catmum-rom
//    if(m==3){
//        float MatrizAux[4][4] = {
//            {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
//            {2/2.0, -5/2.0, 4/2.0, -1/2.0},
//            {-1/2.0, 0.0, 1/2.0, 0.0},
//            {0.0, 2/2.0, 0.0, 0.0}
//        };

//        for(int i = 0; i<4; i++){
//            for(int j = 0; j<4; j++){
//                Matriz[i][j] = MatrizAux[i][j];
//            }
//        }
//    }


//    //Bspline
//    if(m==4){
//        float MatrizAux[4][4] = {
//            {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
//            {3/6.0, -6/6.0, 3/6.0, 0/6.0},
//            {-3/6.0, 0/6.0, 3/6.0, 0/6.0},
//            {1/6.0, 4/6.0, 1/6.0, 0/6.0}
//        };

//        for(int i = 0; i<4; i++){
//            for(int j = 0; j<4; j++){
//                Matriz[i][j] = MatrizAux[i][j];
//            }
//        }
//    }
//}

////Gera o'
//Vetor3D Spline::funcaoU(double u){
//    double vetorU[] = {pow(u,3), pow(u,2), u, 1};
//    double upxmp[4];
//    Vetor3D result;

//    //Up x Mp
//    for(int i = 0; i<4; i++){
//        upxmp[i] = 0;
//        for(int j = 0; j<4; j++){
//            upxmp[i] += vetorU[j] * Matriz[j][i];
//        }
//    }

//    //x Pb
//    for(int c=0; c<4; c++){
//        result.x += upxmp[c] * pontos[c].x;
//        result.y += upxmp[c] * pontos[c].y;
//        result.z += upxmp[c] * pontos[c].z;
//    }

//    return result;
//}

////gera k'
//Vetor3D Spline::derivada1(double u){
//    double vetorU[] = {pow(3*u,2), 2*u, 1, 0};
//    double upxmp[4];
//    Vetor3D result;

//    //Up x Mp
//    for(int i = 0; i<4; i++){
//        upxmp[i]=0;
//        for(int j = 0; j<4; j++){
//            upxmp[i] += vetorU[j] * Matriz[j][i];
//        }
//    }

//    //x Pb
//    for(int c=0; c<4; c++){
//        result.x += upxmp[c] * pontos[c].x;
//        result.y += upxmp[c] * pontos[c].y;
//        result.z += upxmp[c] * pontos[c].z;
//    }

//    return result;
//}


////gera up
//Vetor3D Spline::derivada2(double u){
//    double vetorU[] = {6*u, 2, 0, 0};
//    double upxmp[4];
//    Vetor3D result;

//    //Up x Mp
//    for(int i = 0; i<4; i++){
//        upxmp[i]=0;
//        for(int j = 0; j<4; j++){
//            upxmp[i] += vetorU[j] * Matriz[j][i];
//        }
//    }

//    //x Pb
//    for(int c=0; c<4; c++){
//        result.x += upxmp[c] * pontos[c].x;
//        result.y += upxmp[c] * pontos[c].y;
//        result.z += upxmp[c] * pontos[c].z;
//    }

//    return result;
//}


//void Spline::drawAllTrilho(){
//    Vetor3D ponto;

//    //è necessario ir de 4 em 4 pontos
//    for(int i=0; i<pontosC.size()-4; i++){

//        //Aqui eu copio os 4 proximos pontos para p
//        for(int j=0; j<4;j++){
//            ponto = pontosC[i+j];
//            pontos[j] = ponto;
//        }

//        //Aqui crio a matriz T e aplico o desenho em cada intervalo entre os 4 pontos
//        for(float u=0; u<=1; u += delta){

//            //Cria i', j', k' e o'
//            Vetor3D o = funcaoU(u);

//            Vetor3D k = derivada1(u)*(-1);
//            Vetor3D up = derivada2(u);
//            Vetor3D i = up ^ k;
//            Vetor3D j = k ^ i;

//            k.normaliza();
//            j.normaliza();
//            i.normaliza();


//            //Cria Matriz
//            double T[] = {
//                i.x, j.x, k.x, o.x,
//                i.y, j.y, k.y, o.y,
//                i.z, j.z, k.z, o.z,
//                0,0,0,1
//            };

//            //Desenha 1 trilho
//            glPushMatrix();
//                glColor3f(0, 0, 0);
//                glMultTransposeMatrixd(T);
//                draw1Trilho();
////                glPushMatrix();
////                    glutSolidCube(5.0);
////                glPopMatrix();
//            glPopMatrix();
//        }
//    }
//}

//void Spline::draw1Trilho(){
//    glPushMatrix();
//        glRotated(90, 1, 0, 0);
//        glScaled(1, 0.1, 0.25);
//        glColor3f(0.7, 0.4, 0.15);
//        glutSolidCube(0.5);
//    glPopMatrix();


//    glPushMatrix();
//        glTranslated(-0.15, 0, 0);
//        glRotated(90, 0, 1, 0);
//        glScaled(1, 0.1, 0.25);
//        glColor3f(0.5, 0.5, 0.5);
//        glutSolidCube(0.25);
//    glPopMatrix();

//    glPushMatrix();
//        glTranslated(0.15, 0, 0);
//        glRotated(90, 0, 1, 0);
//        glScaled(1, 0.1, 0.25);
//        glColor3f(0.5, 0.5, 0.5);
//        glutSolidCube(0.25);
//    glPopMatrix();
//}


//void Spline::incrementaDelta() {
//    float v = 0.001;
//    if(delta + v >= 1) {
//        delta = 1;
//    } else {
//        delta += v;
//    }
//}

//void Spline::decrementaDelta() {
//    float v = 0.001;
//    if(delta - v <= 0) {
//        delta = v;
//    } else {
//        delta -= v;
//    }
//}
