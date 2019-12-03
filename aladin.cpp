#include "aladin.h"

Aladin::Aladin()
{
    u=0;
    velocidade=0.009;
    on=true;
    cam=false;
}

void Aladin::drawTapete(float size){
    glPushMatrix();
        glBegin(GL_POLYGON);
            glNormal3f(0,1,0);
            GUI::setColor(1,1,0);
            glVertex3f(0,0.00001,size+(size/2));
            glVertex3f(size,0.00001,size+(size/2));
            glVertex3f(size,0.00001,0);
            glVertex3f(0,0.00001,0);
        glEnd();
        glBegin(GL_POLYGON);
            glNormal3f(0,1,0);
            GUI::setColor(0.8745,0.1098,1);
            glVertex3f(size/8,0.001,(size*2)-((size*2)/3.4));
            glVertex3f(size-(size/8),0.001,(size*2)-((size*2)/3.4));
            glVertex3f(size-(size/8),0.001,size/8);
            glVertex3f(size/8,0.001,size/8);
        glEnd();
    glPopMatrix();
}

void Aladin::drawMembro(float size){
    glPushMatrix();
    //baixo
    glBegin(GL_POLYGON);
        glNormal3f(0,-1,0);
        glVertex3f(0,0,0);
        glVertex3f(size,0,0);
        glVertex3f(size,0,size);
        glVertex3f(0,0,size);
    glEnd();
    //cima
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(0,size*2,size);
        glVertex3f(size,size*2,size);
        glVertex3f(size,size*2,0);
        glVertex3f(0,size*2,0);
    glEnd();
    //frente
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(0,0,size);
        glVertex3f(size,0,size);
        glVertex3f(size,size*2,size);
        glVertex3f(0,size*2,size);
    glEnd();
    //tras
    glBegin(GL_POLYGON);
        glNormal3f(0,0,-1);
        glVertex3f(0,size*2,0);
        glVertex3f(size,size*2,0);
        glVertex3f(size,0,0);
        glVertex3f(0,0,0);
    glEnd();
    //direita
    glBegin(GL_POLYGON);
        glNormal3f(1,0,0);
        glVertex3f(size,size*2,0);
        glVertex3f(size,size*2,size);
        glVertex3f(size,0,size);
        glVertex3f(size,0,0);
    glEnd();
    //esquerda
    glBegin(GL_POLYGON);
        glNormal3f(-1,0,0);
        glVertex3f(0,0,size);
        glVertex3f(0,size*2,size);
        glVertex3f(0,size*2,0);
        glVertex3f(0,0,0);
    glEnd();
    glPopMatrix();
}

void Aladin::drawCubo(float size){
    glPushMatrix();
        //baixo
        glBegin(GL_POLYGON);
            glNormal3f(0,-1,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,0,0);
            glVertex3f(size,0,0);
            glVertex3f(size,0,size);
            glVertex3f(0,0,size);
        glEnd();
        //cima
        glBegin(GL_POLYGON);
            glNormal3f(0,1,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,size,size);
            glVertex3f(size,size,size);
            glVertex3f(size,size,0);
            glVertex3f(0,size,0);
        glEnd();
        //frente
        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,0,size);
            glVertex3f(size,0,size);
            glVertex3f(size,size,size);
            glVertex3f(0,size,size);
        glEnd();
        //tras
        glBegin(GL_POLYGON);
            glNormal3f(0,0,-1);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,size,0);
            glVertex3f(size,size,0);
            glVertex3f(size,0,0);
            glVertex3f(0,0,0);
        glEnd();
        //direita
        glBegin(GL_POLYGON);
            glNormal3f(1,0,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(size,size,0);
            glVertex3f(size,size,size);
            glVertex3f(size,0,size);
            glVertex3f(size,0,0);
        glEnd();
        //esquerda
        glBegin(GL_POLYGON);
            glNormal3f(-1,0,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,0,size);
            glVertex3f(0,size,size);
            glVertex3f(0,size,0);
            glVertex3f(0,0,0);
        glEnd();
    glPopMatrix();
}

void Aladin::drawRetangulo3d(float size){
    glPushMatrix();
        //baixo
        glBegin(GL_POLYGON);
            glNormal3f(0,-1,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,0,0);
            glVertex3f(size,0,0);
            glVertex3f(size,0,size+(size/2));
            glVertex3f(0,0,size+(size/2));
        glEnd();
        //cima
        glBegin(GL_POLYGON);
            glNormal3f(0,1,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,(size/2),size+(size/2));
            glVertex3f(size,(size/2),size+(size/2));
            glVertex3f(size,(size/2),0);
            glVertex3f(0,(size/2),0);

        glEnd();
        //frente
        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,0,size+(size/2));
            glVertex3f(size,0,size+(size/2));
            glVertex3f(size,size/2,size+(size/2));
            glVertex3f(0,size/2,size+(size/2));
        glEnd();
        //tras
        glBegin(GL_POLYGON);
            glNormal3f(0,0,-1);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,size/2,0);
            glVertex3f(size,size/2,0);
            glVertex3f(size,0,0);
            glVertex3f(0,0,0);
        glEnd();
        //direita
        glBegin(GL_POLYGON);
            glNormal3f(1,0,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(size,size/2,0);
            glVertex3f(size,size/2,size+(size/2));
            glVertex3f(size,0,size+(size/2));
            glVertex3f(size,0,0);
        glEnd();
        //esquerda
        glBegin(GL_POLYGON);
            glNormal3f(-1,0,0);
            GUI::setColor(0.83,0.67,0.46);
            glVertex3f(0,0,size+(size/2));
            glVertex3f(0,size/2,size+(size/2));
            glVertex3f(0,size/2,0);
            glVertex3f(0,0,0);
        glEnd();
    glPopMatrix();
}

void Aladin::SpeedUp(){
    velocidade+=0.0001;
}

void Aladin::Speedown(){
    velocidade-=0.0001;
}


void Aladin::drawAladin(Spline spline, CameraJogo *camAladin){


    if(on){
        u+=velocidade;
    }

    //Retorna o aladin para o final quando u<0
    if(u<0){
        u=1;
    }

    Vetor3D ponto;

    static int first = 0;
    for(int j = 0; j<4; j++){
       ponto = spline.pontosTotais[first+j];
       spline.pontosAtuais[j] = ponto;
    }

    //Calculo de T
    //Cria i', j', k' e o'
    Vetor3D o = spline.funcaoU(u);
    Vetor3D k = spline.derivada1(u);
    Vetor3D up = spline.derivada2(u)*(-1);
    k.normaliza();
    up.normaliza();
    Vetor3D i = up ^ k;
    i.normaliza();
    Vetor3D j = k ^ i;




    //Cria Matriz
    double T[] = {
        i.x, j.x, k.x, o.x,
        i.y, j.y, k.y, o.y,
        i.z, abs(j.z), k.z, o.z,
        0,0,0,1
    };


    //Quando o aladin chegar no ultimo ponto, voltar para o inicio
    if(u>1){
        u=0;
        first++;
        if(first > (spline.pontosTotais.size()-4)){
            first=0;
        }
    }

    //Finalmente o desenho
    glPushMatrix();
        //Colocando objeto de acordo com T, com translação correspondente.
        glMultTransposeMatrixd(T);
        glTranslated(-0.1, 0.075, 0);

        //perna1
        glPushMatrix();
            glTranslated((0.2/2.5),0,0.2/2.6);
            GUI::setColor(1,1,1);
            drawMembro(0.2/4);
        glPopMatrix();
        //perna2
        glPushMatrix();
            glTranslated((0.2/2.5),0,(0.2/3)*2.5);
            GUI::setColor(1,1,1);
            drawMembro(0.2/4);
        glPopMatrix();
        //tronco
        glPushMatrix();
            GUI::setColor(0.8745,0.1098,1);
            glTranslated((0.2/2.8),0.2/3,(0.2/3)*1.75);
            drawMembro(0.2/3);
        glPopMatrix();
        //braco1
        glPushMatrix();
            GUI::setColor(0.83,0.67,0.46);
            glTranslated((0.2/2.5),0.2,(0.2/3)*2.8);
            glRotated(125,1,0,0);
            drawMembro(0.2/4);
        glPopMatrix();
        //braco2
        glPushMatrix();
            GUI::setColor(0.83,0.67,0.46);
            glTranslated((0.2/2.5),0.2/1.25,(0.2/1.4));
            glRotated(-125,1,0,0);
            drawMembro(0.2/4);
        glPopMatrix();
        //cabeca
        glPushMatrix();
            GUI::setColor(0.83,0.67,0.46);
            glTranslated((0.2/3),0.2,(0.2/1.8));
            drawCubo(0.2/2.5);
        glPopMatrix();
        //chapeu
        glPushMatrix();
            GUI::setColor(0.8745,0.1098,1);
            GUI::drawSphere(0.2/1.9,0.2+(0.2/2.6),0.2/1.35,0.2/10);
        glPopMatrix();

        //olhos
             glPushMatrix();
                 GUI::setColor(1,1,1);
                 GUI::drawSphere((0.2/8)*2.8,0.2+(0.2/4),(0.2/8)*7,0.2/20);
             glPopMatrix();
             glPushMatrix();
                 GUI::setColor(1,1,1);
                 GUI::drawSphere((0.2/8)*2.8,0.2+(0.2/4),(0.2/8)*5,0.2/20);
             glPopMatrix();
             glPushMatrix();
                 GUI::setColor(0,0,0);
                 GUI::drawSphere((0.2/8)*2.5,0.2+(0.2/4),(0.2/8)*7,0.2/50);
             glPopMatrix();
             glPushMatrix();
                 GUI::setColor(0,0,0);
                 GUI::drawSphere((0.2/8)*2.5,0.2+(0.2/4),(0.2/8)*5,0.2/50);
             glPopMatrix();

        //boca
             glPushMatrix();
                 glTranslated((0.2/8)*2.5,0.2+(0.2/10),(0.2/8)*5.5);
                 GUI::setColor(0,0,0);
                 drawRetangulo3d(0.2/12);
             glPopMatrix();

        //tapete
             drawTapete(0.2);
    glPopMatrix();

    camAladin->c = *new Vetor3D(o.x+1, o.y, o.z);
    if(j.y>0) camAladin->e = *new Vetor3D(o.x-2, o.y+1, o.z);
    else      camAladin->e = *new Vetor3D(o.x-2, o.y-1, o.z);
    camAladin->u = *new Vetor3D(j.x, j.y, j.z);

}



