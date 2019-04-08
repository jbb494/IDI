#include "MyGLWidget.h"



MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat

  Theta = 0;
  Psi = 0;
  
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  
  VAOs = new VAO[N_VAOs];
  
  Instancies = new instancia[N_instancies];
  
  carregaShaders();
  creaBuffers();
  
  ini_cam();

  opt = PRESPECTIVA;
  projectTransform();
  
  viewTransform();

}

void MyGLWidget::paintGL () 
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i<N_instancies; i++)
	{		
	  // Carreguem la transformació de model
	  modelTransform (Instancies[i]);

	  // Activem el VAO per a pintar la caseta 
	  glBindVertexArray ((Instancies[i].vao_general)->vao);

	  // pintem
	  glDrawArrays(GL_TRIANGLES, 0, (Instancies[i].vao_general)->model.faces().size()*3);
	}
  modelTransformTerra();

  glBindVertexArray (VAO_Terra.vao);

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  
  glBindVertexArray (0);
}
void MyGLWidget::modelTransformTerra()
{
  glm::mat4 transform (1.0f);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}
void MyGLWidget::modelTransform (const instancia& Instancia_arg) 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  		
  glm::vec3 cent = glm::vec3((Instancia_arg.vao_general)->Capsa.Centre.x, (Instancia_arg.vao_general)->Capsa.Centre.y - ((Instancia_arg.vao_general)->Capsa.Max.y-(Instancia_arg.vao_general)->Capsa.Min.y)/2 , (Instancia_arg.vao_general)->Capsa.Centre.z);

  transform = glm::translate(transform, Instancia_arg.transf.translacio);
  
  transform = glm::rotate(transform, Instancia_arg.transf.rotacio.x, glm::vec3(1,0,0));
  transform = glm::rotate(transform, Instancia_arg.transf.rotacio.y, glm::vec3(0,1,0));
  transform = glm::rotate(transform, Instancia_arg.transf.rotacio.z, glm::vec3(0,0,1));

  transform = glm::scale(transform, Instancia_arg.transf.escalat);
  transform = glm::translate(transform, -cent);
  
  
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
  
  
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;
	
  cam.ra = ample / (float)alt;
  
  if(cam.ra < 1)
  {
	 cam.FOV = 2.f*glm::atan(glm::tan(angle_inicial)/cam.ra);
  }else
  {
	 cam.FOV = 2*angle_inicial;

  }

  	 
  //Hem d'actualitzar projectTransform
  projectTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      Instancies[0].transf.escalat += glm::vec3(0.05);
      break;
    }
    case Qt::Key_D: { // escalar a més petit
     Instancies[0].transf.escalat -= glm::vec3(0.05);
      break;
    case Qt::Key_R:{
	  Instancies[0].transf.rotacio += glm::vec3(0.f,M_PI/12,0.f);
	  break;
	} case Qt::Key_O:{
	  if(opt == PRESPECTIVA)opt = ORTOGONAL;
	  else if(opt == ORTOGONAL)opt = PRESPECTIVA;
	  projectTransform();
	  break;
	}case Qt::Key_Z:{
	  cam.zoom-=0.1;
	  projectTransform();
	  break;
	}case Qt::Key_X:{
	  cam.zoom+=0.1;
	  projectTransform();
	  break;
	}
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {
	makeCurrent();
	
	if(e->x() > x_ant) Psi -= 0.03;
	else if(e->x() < x_ant) Psi += 0.03;
	
	if(e->y() > y_ant) Theta -= 0.03;
	else if(e->y() < y_ant) Theta += 0.03;
	
	x_ant = e->x();
	y_ant = e->y();
	viewTransform();
	update();
}

void MyGLWidget::creaBuffers () 
{
  // Dades Homer
  // Dos VBOs, un amb posició i l'altre amb color
	char ruta[90] = "./Models/Patricio.obj";

	transformacio transf_vec[N_VAOs];
  
   transf_vec[0].translacio = glm::vec3(2.f, 0.f, 2.f);
   transf_vec[0].rotacio = glm::vec3(0.f, 0.f, 0.f);
   transf_vec[0].escalat = glm::vec3(1.f, 1.f, 1.f);
   
   transf_vec[1].translacio = glm::vec3(0.f, 0.f, 0.f);
   transf_vec[1].rotacio = glm::vec3(0.f, M_PI, 0.f);
   transf_vec[1].escalat = glm::vec3(1.f, 1.f, 1.f);
   
   transf_vec[2].translacio = glm::vec3(-2.f, 0.f, -2.f);
   transf_vec[2].rotacio = glm::vec3(0.f, M_PI/2, 0.f);
   transf_vec[2].escalat = glm::vec3(1.f, 1.f, 1.f);

	for(int i = 0; i<N_VAOs; i++)
	{
		creaBuffers_model(VAOs[i], ruta);
		capsa_model_ini(VAOs[i].model, VAOs[i].Capsa);
	}
	
	creaBuffers_terra(VAO_Terra, 5);
	//Patricios
	for(int i = 0; i<N_instancies; i++)
	{
		Instancies[i].vao_general = &VAOs[0];	
		Instancies[i].transf = transf_vec[i];
	}
	//esfera
	glm::vec3 esf_max, esf_min;
	
	esf_max = VAO_Terra.Capsa.Max;
	
	std::cout << "Terra Max.x: " << VAO_Terra.Capsa.Max.x << std::endl;
	
	esf_min = VAO_Terra.Capsa.Min;

	for(int i = 0; i<N_instancies; i++)
	{				
		transf_model_ini(Instancies[i], transf_vec[i]);


		glm::vec3 Mida_Instancia = (Instancies[i].vao_general)->Capsa.Max- (Instancies[i].vao_general)->Capsa.Min;

		glm::vec3 Capsa_Max_real = glm::vec3(Mida_Instancia.x*Instancies[i].transf.escalat.x,Mida_Instancia.y*Instancies[i].transf.escalat.y, (Mida_Instancia.z*Instancies[i].transf.escalat.z))+ Instancies[i].transf.translacio;

		glm::vec3 Capsa_Min_real = glm::vec3(-Mida_Instancia.x*Instancies[i].transf.escalat.x,0.f, (-Mida_Instancia.z*Instancies[i].transf.escalat.z))+ Instancies[i].transf.translacio;
		
		esf_max = vec3MaxOP(esf_max, Capsa_Max_real);

		esf_min = vec3MinOP(esf_min, Capsa_Min_real);
		
		std::cout << "esf_max.x: " <<esf_max.x << " = " << "Capsa_Max.x: "  << Capsa_Max_real.x << std::endl;
	}		

	calcul_esfera(esf_min, esf_max);

	std::cout << "esf_min: " << std::endl << "x: "<< esf_min.x << "y: "<< esf_min.y <<"z: "<< esf_min.z << std::endl; 
	
	std::cout << "esf_max: " << std::endl << "x: "<< esf_max.x << "y: "<< esf_max.y <<"z: "<< esf_max.z << std::endl; 

	//std::cout << "Patricio_max_y: " << VAOs[0].Capsa.Max.y << "Patricio_min_y: " << VAOs[0].Capsa.Min.y << std::endl;

    glBindVertexArray (0);
}
void MyGLWidget::capsa_terra_ini(capsa& c_terra_arg, int mida_terra)
{
	c_terra_arg.Min = glm::vec3(-1*mida_terra/2.f,0,-1*mida_terra/2.f);
	
	c_terra_arg.Max = glm::vec3(1*mida_terra/2.f,0,1*mida_terra/2.f);
	
	c_terra_arg.Centre.x = (c_terra_arg.Max.x+c_terra_arg.Min.x)/2;
	
	c_terra_arg.Centre.y = (c_terra_arg.Max.y+c_terra_arg.Min.y)/2;
	
	c_terra_arg.Centre.z = (c_terra_arg.Max.z+c_terra_arg.Min.z)/2;
}

void MyGLWidget::capsa_model_ini(const Model& m, capsa& c_model)
{
	coord_maxmin(m.vertices(), c_model.Min, c_model.Max);
	
	c_model.Centre.x = (c_model.Max.x+c_model.Min.x)/2;
	
	c_model.Centre.y = (c_model.Max.y+c_model.Min.y)/2;
	
	c_model.Centre.z = (c_model.Max.z+c_model.Min.z)/2;
}


void MyGLWidget::creaBuffers_terra(VAO& VAO_terra , int mida_terra)
{
	 //VAO terra
  glGenVertexArrays(1, &VAO_Terra.vao);
  glBindVertexArray(VAO_Terra.vao);

  glm::vec3 vertex[6];
  vertex[0] = glm::vec3(-1*mida_terra/2.f,0,-1*mida_terra/2.f);
  vertex[1] = glm::vec3(1*mida_terra/2.f,0,-1*mida_terra/2.f);
  vertex[2] = glm::vec3(1*mida_terra/2.f,0,1*mida_terra/2.f);
  vertex[3] = glm::vec3(-1*mida_terra/2.f,0,1*mida_terra/2.f);
  vertex[4] = glm::vec3(1*mida_terra/2.f,0,1*mida_terra/2.f);
  vertex[5] = glm::vec3(-1*mida_terra/2.f,0,-1*mida_terra/2.f);
  
  
  glm::vec3 color[6];
  color[0] = glm::vec3(0.5,0.2,1);
  color[1] = glm::vec3(0.5,0.2,1);
  color[2] = glm::vec3(0.5,0.2,1);
  color[3] = glm::vec3(0.5,0.2,1);
  color[4] = glm::vec3(0.5,0.2,1);
  color[5] = glm::vec3(0.5,0.2,1);
  
  
  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
 
  
  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  capsa_terra_ini(VAO_Terra.Capsa, mida_terra);

}



void MyGLWidget::creaBuffers_model(VAO& VAO_arg , const char ruta[])
{
	char ruta2[80] = "./Models/Patricio.obj";
	
	VAO_arg.model.load(ruta2);
	//VAO_arg.model.load("./Models/Patricio.obj");

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_arg.vao);
  glBindVertexArray(VAO_arg.vao);

  GLuint VBO_Homer[2];
  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*3*VAO_arg.model.faces().size(), VAO_arg.model.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*3*VAO_arg.model.faces().size(), VAO_arg.model.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

	

}
void  MyGLWidget::transf_model_ini(instancia& Instancia_arg, const transformacio& trans)
{
	float mida_y_model = ((Instancia_arg.vao_general)->Capsa.Max.y - (Instancia_arg.vao_general)->Capsa.Min.y);
	Instancia_arg.transf.escalat = glm::vec3(trans.escalat.x/ mida_y_model, trans.escalat.y/mida_y_model ,trans.escalat.z/mida_y_model );
	Instancia_arg.transf.translacio = trans.translacio;
	Instancia_arg.transf.rotacio = trans.rotacio;

}
void MyGLWidget::coord_maxmin(std::vector<double> vertices, glm::vec3& vec3_min, glm::vec3& vec3_max)
{
	unsigned int i;
	
	vec3_max = glm::vec3((float)vertices[0],(float) vertices[1], (float)vertices[2]);
		
	vec3_min = glm::vec3((float)vertices[0],(float) vertices[1], (float)vertices[2]);

	for(i = 3; i<vertices.size(); i+=3)
	{
		vec3_max = vec3MaxOP(vec3_max, glm::vec3((float)vertices[i], (float)vertices[i+1], (float)vertices[i+2]));

		vec3_min = vec3MinOP(vec3_min, glm::vec3((float)vertices[i], (float)vertices[i+1], (float)vertices[i+2]));
	}

}
glm::vec3 MyGLWidget::vec3MaxOP(const glm::vec3& vec1, const glm::vec3& vec2)
{
	glm::vec3 vec_ret = vec1;
	
	if(vec1.x < vec2.x)vec_ret.x = (float)vec2.x;
	if(vec1.y < vec2.y)vec_ret.y = (float)vec2.y;
	if(vec1.z < vec2.z)vec_ret.z = (float)vec2.z;
	
	return vec_ret;
	
}

glm::vec3 MyGLWidget::vec3MinOP(const glm::vec3& vec1, const glm::vec3& vec2)
{
	glm::vec3 vec_ret = vec1;
	
	if(vec1.x > vec2.x)vec_ret.x = (float)vec2.x;
	if(vec1.y > vec2.y)vec_ret.y = (float)vec2.y;
	if(vec1.z > vec2.z)vec_ret.z = (float)vec2.z;
	
	return vec_ret;

}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");

  projLoc = glGetUniformLocation(program->programId(), "proj");

  viewLoc = glGetUniformLocation(program->programId(), "view");
    
}

void MyGLWidget::calcul_esfera(glm::vec3 punt_min, glm::vec3 punt_max)
{
	float diametre = glm::distance(punt_min, punt_max);
	
	esf.r = diametre/2;
	
	esf.centre.x = (punt_max.x+punt_min.x)/2;
	
	esf.centre.y = (punt_max.y+punt_min.y)/2;
	
	esf.centre.z = (punt_max.z+punt_min.z)/2;
	
}
void MyGLWidget::ini_cam()
{
	//camera (OBS, VRP, up, FOV, ra, znear, zfar)
	

	float d = 4*esf.r;

    glm::vec3 OBS = glm::vec3(esf.centre.x,esf.centre.y,esf.centre.z + d);

	float znear = d - esf.r;
	
	angle_inicial = glm::asin(esf.r/(d));

	cam = camera(OBS, esf.centre, glm::vec3(0,1,0), 2*angle_inicial, 1.0f, znear, znear+esf.r*2);
}


void MyGLWidget::projectTransform()
{
	// glm::perspective (FOV en radians, ra window, znear, zfar)
	glm::mat4 Proj;
	if(opt == PRESPECTIVA)Proj = glm::perspective (cam.FOV*cam.zoom, cam.ra, cam.znear, cam.zfar);
	else if(opt == ORTOGONAL)
	{
		if(cam.ra>1 )Proj = glm::ortho(-1*esf.r*cam.ra,esf.r*cam.ra,-1*esf.r,esf.r, cam.znear, cam.zfar);
		else Proj = glm::ortho(-1*esf.r,esf.r,-1*esf.r/cam.ra,esf.r/cam.ra, cam.znear, cam.zfar);
	}
	
	glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
	//glm::lookAt (OBS, VRP, UP)
	glm::mat4 View (1.0f);
	//View = glm::lookAt (cam.OBS, cam.VRP, cam.up);

	calcul_Euler(View);
	
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::calcul_Euler(glm::mat4& View)
{
	float d = glm::distance(cam.OBS, cam.VRP);

  View = glm::translate(View, glm::vec3(0.f, 0.f, -1*d));
  View = glm::rotate(View, 0.f, glm::vec3(0,0,1));
  View = glm::rotate(View, Theta, glm::vec3(1,0,0));
  View = glm::rotate(View, Psi, glm::vec3(0,1,0));

  View = glm::translate(View, glm::vec3(-1*cam.VRP.x, -1*cam.VRP.y, -1*cam.VRP.z)); 
}

