# CheatSheet IDI ExamenLab (OpenGL i GLSM)

##Transformacions Geomètriques (*TG*)

```c
glm::mat4() = glm::scale(glm::mat4(), glm::vec3());
```
```c
glm::mat4() = glm::translate(glm::mat4(), glm::vec3());
```
```c
glm::mat4() = glm::rotate(glm::mat4(), (float), glm::vec3());
```

###*Aplicació*

A la funció Transform:

```c
TG = I;
```
```c
TG = glm::translate(TG, posObjecte);
```
```c
TG = glm::scale(TG, glm::vec3(escala_x, escala_y, escala_z);
```
```c
TG = glm::rotate(TG, angle_x, glm::vec3(1,0,0));
```
```c
TG = glm::rotate(TG, angle_x, glm::vec3(0,1,0));
```
```c
TG = glm::rotate(TG, angle_x, glm::vec3(0,0,1));
```
```c
TG = glm::translate(TG, centreObjecte);
```


##Project i View Transform

### Project Transform

```c
glm::mat4() = glm::perspective((float) , (float), (float), (float));
```
```c
glm::mat4() = glm::ortho((float), (float), (float), (float), (float), (float));
```

\pagebreak

#### *Aplicació*

```c
float radiEsc = distance(CapsaEscenaMin, CapsaEscenaMax)/2.f;
```
```c
float angle_inicial = glm::asin(radiEsc/(2*radiEsc));
```

![Esfera Escena](Images/EsferaEscena.png){width=200px}

```c
float FOV = angle_inicial*2;
```
```c
float ra = amplada/altura;
```
\vspace{0.4cm}

```c
Proj = glm::perspective(FOV , ra, radiEsc, 3.0f*radiEsc);
```
```c
Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, 3.0f*radiEsc);
```
##View Transform (Euler)

```c
float d = glm::distance(OBS, VRP);
```
```c
View = glm::translate(glm::vec3(1.f), glm::vec3(0.f, 0.f, -1*d));
```
```c
View = glm::rotate(View, Phi, glm::vec3(0,0,1)); 
``` 
//Phi  = $\phi$

```c
View = glm::rotate(View, Theta, glm::vec3(1,0,0)); 
``` 
//Theta  = $\theta$

```c
View = glm::rotate(View, Psi, glm::vec3(0,1,0)); 
``` 
//Psi  = $\psi$

```c
View = glm::translate(View, glm::vec3(-1*VRP.x, -1*VRP.y, -1*VRP.z)); 
```
\pagebreak

##View Transform (lookAt)

```c
View = glm::lookAt(OBS, VRP, up);
```

##Resize

```c
ra = ample / (float)alt;
```
```c
if(ra < 1)
{
	FOV = 2.f*glm::atan(glm::tan(angle_inicial )/ra);
}else
{
	FOV = 2*angle_inicial;
}
```

#Shaders

##Càlcul de color al Vertex Shader	

Uniforms i variables IN / OUT:

```c
in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 index;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum
//vec3 colFocus = vec3(0.8, 0.8, 0.8);
vec3 colFocus = vec3(0, 1, 1);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocus = vec3(1, 1, 1); 

out vec3 fcolor;
```

Dintre el main del vertex shader:


```c
mat4 matNormal = view * TG;
```
```c
mat3 matNormalInvers = inverse (transpose (mat3 (matNormal)));
```
```c
vec3 coordSCO = (matNormal * vec4 ( vertex, 1.0)).xyz ;
```
```c
vec3 posF = (/*view * */ vec4(posFocus , 1.0)).xyz;
```
```c
vec3 L = posF- coordSCO;
```
```c
vec3 normalNormal = matNormalInvers * normal;
```
```c
L = normalize(L);
```
```c
normalNormal = normalize(normalNormal );
```
```c
vec3 a;
```
```c
fcolor = Phong(normalNormal, L, vec4(coordSCO, 1.0));
```
```c
gl_Position = proj * view * TG * vec4 (vertex, 1.0);
```

##Càlcul de color al Fragment Shader

```c
mat4 matNormal = view * TG;
```
```c
vec3 coordSCO = (matNormal * vec4 (vert, 1.0)).xyz ;
```
```c
vec3 L = posF - coordSCO;
```
```c
vec3 normalNormal = matNormalInvers * norm;
```
```c
L = normalize(L);
```
```c
normalNormal = normalize(normalNormal );
```
```c
vec3 a;
```
```c
a = Phong(normalNormal, L, vec4(coordSCO, 1.0));
```
```c
FragColor = vec4(a,1);	
```

## Uniforms

```c
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); 
```
//count = 1 

```c
void glUniformMatrix4fv(GLint location, GLsizei count, 	GLboolean transpose,
const GLfloat *value);
``` 
//count = 1
