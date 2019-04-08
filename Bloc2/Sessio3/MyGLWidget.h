#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
 #include <QMouseEvent> 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Model/model.h"
#include <string>
#include <iostream>


#define N_VAOs 1
#define N_instancies 3

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    struct camera
    {
		 glm::vec3 OBS, VRP, up;
		 float FOV, ra, znear, zfar;
		 float zoom;
		 camera (glm::vec3 arg_OBS, glm::vec3 arg_VRP, glm::vec3 arg_up, float arg_FOV, float arg_ra, float arg_znear, float arg_zfar)
		 {
			 OBS= arg_OBS;
			 VRP= arg_VRP;
			 up= arg_up;
			 FOV= arg_FOV;
			 ra= arg_ra;
			 znear= arg_znear;
			 zfar= arg_zfar;
			 zoom = 1.f;
		 }
		 camera(){}
	};
	struct capsa
	{
		glm::vec3 Min, Max, Centre;
	};
	struct transformacio
	{
		glm::vec3 translacio;
		glm::vec3 escalat;
		glm::vec3 rotacio;

	};
	struct VAO
	{
		GLuint vao;
		capsa Capsa;
		Model model;
	};
	struct instancia
	{
		transformacio transf;
		VAO* vao_general;
	};
	enum optica {ORTOGONAL, PRESPECTIVA};
	
	struct Esfera
	{
		glm::vec3 centre;
		float r;
		
	};
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
    
    virtual void mouseMoveEvent(QMouseEvent *e);


  private:
    void creaBuffers ();
    void creaBuffers_model(VAO& VAO_arg, const char ruta[]);
    void transf_model_ini(instancia& Instancia_arg, const transformacio& trans);
    void creaBuffers_terra(VAO& VAO_Model, int mida);
    void carregaShaders ();
    void modelTransform (const instancia& VAOArg);
    void modelTransformTerra ();
	void projectTransform();
	void viewTransform();
	void ini_cam();
	static void capsa_model_ini(const Model& m, capsa& c_model);
	static void capsa_terra_ini(capsa& c, int mida);
	
	void calcul_esfera(glm::vec3 punt_min, glm::vec3 punt_max);
	static void coord_maxmin(std::vector<double> vertices, glm::vec3& vec3_min, glm::vec3& vec3_max);
	static glm::vec3 vec3MaxOP(const glm::vec3& vec1, const glm::vec3& vec2);
	static glm::vec3 vec3MinOP(const glm::vec3& vec1, const glm::vec3& vec2);
	void calcul_Euler(glm::mat4& View);
	
    // attribute locations
    GLuint vertexLoc, colorLoc;
    // uniform locations
    GLuint transLoc;
    GLuint projLoc;
    GLuint viewLoc;
	//Camera
	camera cam;	
	float angle_inicial;
    // VAO
    VAO* VAOs;
       
    VAO VAO_Terra;
    
    //Instancies
    instancia* Instancies;

	//Angles Euler    //
    float Theta;
    float Psi;
    
    float x_ant;
    float y_ant;
    
    // Program
    QOpenGLShaderProgram *program;
    // Viewport
    GLint ample, alt;
        
    // Esfera contenidora
    Esfera esf;
    
    //Optica
    optica opt;
    
};

