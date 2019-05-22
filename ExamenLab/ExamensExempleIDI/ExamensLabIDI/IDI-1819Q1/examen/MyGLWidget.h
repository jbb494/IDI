#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:
    void createBuffersModel ();
    void createBuffersPilota ();
    void createBuffersPorteria ();
    void createBuffersTerra ();
    void carregaShaders ();
    void iniEscena ();
    void iniCamera ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformIdent ();
    void modelTransformModel ();
    void modelTransformPilota ();
    void calculaCapsaModel (Model &p, float &escala, glm::vec3 &CentreBase);

    void mouPilota (int alfa);
    void iniciPilota ();
    void tractamentGol();
    bool aturaPorter();
	void modelTransformModel2 ();
	void viewTransform2 ();
	void projectTransform2 ();
//<<>>	

    // VAO i VBO names
    GLuint VAO_Patr, VAO_Pil, VAO_Port, VAO_Terra;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc, colfocusLoc;

    // model
    Model patr, pil;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centreBaseModel, centreBasePil;
    float escalaModel, escalaPil;
    // radi de l'escena
    float radiEsc;
    glm::vec3 posPilota;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float Psi, Theta;

float FOV, FOV2, angle_inicial, ra;

	glm::vec3 colFocus;

    // per al moviment de la pilota
    QTimer timer;
    int anglePilota;
	bool cameraGlob;
	glm::vec3 offsetPorter;

  public slots:
    void mourePilota ();
	void canviaCamera(bool);
	void canviaGraus(int graus);
	void reset();
signals:
	void resetSlider(int);
	void canviaCameraSignal();
};

