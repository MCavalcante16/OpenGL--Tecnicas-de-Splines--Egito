#include <iostream>

using namespace std;

#include <gui.h>
#include <vector>
#include <aladin.h>

Spline *spline = new Spline();

Aladin aladin;
int mode=1;
CameraJogo *camAladin = new CameraJogo();
CameraDistante *camNormal = new CameraDistante(0,1,7, 0,1,0, 0,1,0);
bool viewAladin = false;
bool camJogoOn = false;
Vetor3D* p1 = new Vetor3D(-2, 1, 0);
Vetor3D* p2 = new Vetor3D(0, 3, 0);
Vetor3D* p3 = new Vetor3D(2, 2, 0);
Vetor3D* p4 = new Vetor3D(4, 3, 0);
bool trans_view;

int newpoint = 6;

//-------------------picking------------------
vector<Vetor3D> pontosControle;

int pontoSelecionado = 0; //names = [1,n] //n = pontosControle.size()
//bool transPontos = glutGUI::trans_obj; //= true;


void drawPiramide(){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glNormal3f(0,7,-7);
    GUI::setColor(0.83,0.67,0.50);
    glVertex3f(7,0,-7);
    glVertex3f(-7,0,-7);
    glVertex3f(0,7,0);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(-7,7,0);
    GUI::setColor(0.83,0.67,0.50);
    glVertex3f(-7,0,-7);
    glVertex3f(-7,0,7);
    glVertex3f(0,7,0);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0,7,7);
    GUI::setColor(0.83,0.67,0.50);
    glVertex3f(-7,0,7);
    glVertex3f(7,0,7);
    glVertex3f(0,7,0);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(7,7,0);
    GUI::setColor(0.83,0.67,0.50);
    glVertex3f(7,0,7);
    glVertex3f(7,0,-7);
    glVertex3f(0,7,0);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0,-7,0);
    GUI::setColor(0.83,0.67,0.50);
    glVertex3f(-7,0,7);
    glVertex3f(-7,0,-7);
    glVertex3f(7,0,-7);
    glVertex3f(7,0,7);
    glEnd();
    glPopMatrix();
}

void desenhaPontosDeControle()
{
    //desenhando pontos de controle
    for (int i=0; i<pontosControle.size(); i++) {
        //definindo cor da selecao
        if (i == pontoSelecionado-1) {
            GUI::setColor(1,1,1,1,true);
        } else {
            GUI::setColor(0,0,1,1,true);
        }
        //desenhando (definindo nomes para o picking)
        Vetor3D p = pontosControle[i];
        glPushName(i+1); //não se deve definir name = 0!
            GUI::drawSphere(p.x,p.y,p.z,0.1);
        glPopName();
    }
}

//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

//de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
//fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void cenario();

void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport principal
    glViewport(0, 0, width, height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
            cenario();

    //viewport frente===========================
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 0, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 0, width/4, height/4);
    }
        glLoadIdentity();
        Vetor3D eye = *new Vetor3D(0.0, 1.0, 15.0);
        Vetor3D center = *new Vetor3D(0.0, 0.1, 0.0);
        gluLookAt(eye.x,eye.y,eye.z, center.x,center.y,center.z, 0.0,1.0,0.0);
        cenario();
    //==========================================

    //viewport Cima=============================
    if (!scissored) {
        //misturando com a principal
        glViewport(3*width/4, 0, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(3*width/4, 0, width/4, height/4);
    }
        glLoadIdentity();
        Vetor3D eye2 = *new Vetor3D(0, 15, 0);
        Vetor3D center2 = *new Vetor3D(1, 0, 0);
        gluLookAt(eye2.x,eye2.y,eye2.z, center2.x,center2.y,center2.z, 0.0,1.0,0.0);
        cenario();
    //==========================================

    //viewport lado=================================
    if (!scissored) {
        //misturando com a principal
        glViewport(3*width/4, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(3*width/4, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
        Vetor3D eye3 = *new Vetor3D(15, 1, 0);
        Vetor3D center3 = *new Vetor3D(-1, 0, 0);
        gluLookAt(eye3.x,eye3.y,eye3.z, center3.x,center3.y,center3.z, 0.0,1.0,0.0);
        cenario();
    //==============================================

    //viewport gopro================================
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
        Vetor3D eye4 = camAladin->e;
        Vetor3D center4 = camAladin->c;
        gluLookAt(eye4.x,eye4.y,eye4.z, center4.x,center4.y,center4.z, 0.0,1.0,0.0);
        cenario();
    //===============================================
}
//-------------------viewPorts------------------

void cenario() {


    //GUI::setLight(1,1,3,5,true,false);
    //GUI::setLight(2,-1.5,0.5,-1,true,false);
    GUI::setLight(3,-5,3,5,true,false);
    GUI::drawOrigin(0.5);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    GUI::setColor(0.83,0.67,0.46);
    GUI::drawFloor(30,30,1,1);

    glPushMatrix();
    glTranslated(2,0,-9);
    drawPiramide();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,0,9);
    drawPiramide();
    glPopMatrix();
//    trilho->geraPontosControle(pontosControle);
//    trilho->drawAllTrilho();
    glPushMatrix();
    spline->setPontosControle(pontosControle);
    spline->drawAllTrilho();
    aladin.drawAladin(*spline, camAladin);
    glPopMatrix();


    //GUI::setColor(1,0,0);
    //GUI::drawFloor();
    Desenha::drawGrid( 5, 0, 1, 1 );


    glPushMatrix();
    desenhaPontosDeControle();
    glPopMatrix();

}

void desenha() {
    GUI::displayInit();



    if (!viewports) {
        cenario();
    } else {
        viewPorts();
    }

    //transladando ponto selecionado atraves do picking
    //if (pontoSelecionado > 0 and pontoSelecionado <= objetos.size()) {
    if (pontoSelecionado!=0) {
        pontosControle[pontoSelecionado-1].x += glutGUI::dtx;
        pontosControle[pontoSelecionado-1].y += glutGUI::dty;
        pontosControle[pontoSelecionado-1].z += glutGUI::dtz;
    }

    GUI::displayEnd();
}

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {

    //Controle de Objeto, luz e viewport
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        //transPontos = glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    case 'V':
        trans_view = !trans_view;

    //========================================//


    //Ativar/Desativar ViewPorts - Configuracao
    case 'v':
        viewports = !viewports;
        break;
    case 's':
        scissored = !scissored;
        break;
    //========================================//

    //Detalhismo da Spline
    case '+':
        spline->upDelta();
        break;
    case '-':
        spline->downDelta();
        break;
    //========================================//

    //Alterar Velocidade
    case 'i':
        aladin.SpeedUp();
        break;
    case 'k':
        aladin.Speedown();
        break;
    //========================================//

    //novo ponto
    case 'n': {
        Vetor3D temp;
        temp.x = newpoint;
        temp.y = 2;
        temp.z = 0;
        pontosControle.push_back(temp);
        newpoint+=2;
        break;
    }
    //========================================//

    //delecao de ponto
    case 'm': {
        if(pontosControle.size()>4){
            pontosControle.pop_back();
            newpoint-=2;
        }
        break;
    }
    //========================================//



    //============alterar spline=============//
    case 'b':{
        if (mode + 1 > 5) mode = 1;
        else mode ++;
        spline->setMode(mode);
        break;
    }
    //========================================//



    //===Ativar camera acompanhando aladin====//
    case 'j':{
        if(!aladin.cam){
            delete glutGUI::cam;
            glutGUI::cam = camAladin;
            aladin.cam = true;
        }
        else{
            delete glutGUI::cam;
            glutGUI::cam = camNormal;
            aladin.cam = false;
        }
    }
    //========================================//
    default:
        break;
    }
    //========================================//
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                glutGUI::lbpressed = false;
            }
        }
    }
}

int main()
{
    cout << "Hello World!" << endl;

    int n = 5;
    float dist = 1.0;
    pontosControle.push_back(*p1);
    pontosControle.push_back(*p2);
    pontosControle.push_back(*p3);
    pontosControle.push_back(*p4);


    GUI gui = GUI(800,600,desenha,teclado,mouse);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}
