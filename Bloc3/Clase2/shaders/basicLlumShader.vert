#version 330 core

in vec3 vertex;
out vec3 vert;
in vec3 normal;
out vec3 norm;


in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 matam;
out vec3 matdif;
out vec3 matspe;
out float matshi;

out mat3 matNormalInvers;
out vec3 posF;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform vec3 posFocus; 
uniform vec3 llumAmbient; 
uniform vec3 colFocus ; 
//Valors per als components que necessitem dels focus de llum
//vec3 colFocus = vec3(0.8, 0.8, 0.8);
//vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
//vec3 posFocus = vec3(1, 0, 1);  // en SCA

out vec3 fcolor;

void main()
{
	vert = vertex;
	norm = normal;
	matam = matamb;
	matdif = matdiff;
	matspe = matspec;
	matshi = matshin;
    mat4 matNormal = view * TG;
    matNormalInvers = inverse (transpose (mat3 (matNormal)));
    posF = (view * vec4(posFocus , 1.0)).xyz;
    gl_Position = proj * matNormal * vec4 (vertex, 1.0);
}
