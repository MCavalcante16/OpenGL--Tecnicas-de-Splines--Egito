#ifndef ALADIN_H
#define ALADIN_H
#include<gui.h>
#include<spline.h>


class Aladin
{
public:
    Aladin();

    double u;
    double velocidade;
    bool on;
    bool cam;


    void drawTapete(float size);
    void drawMembro(float size);
    void drawRetangulo3d(float size);
    void drawCubo(float size);
    void drawAladin(Spline trilho, CameraJogo *cam);
    void SpeedUp();
    void Speedown();


};

#endif // ALADIN_H
