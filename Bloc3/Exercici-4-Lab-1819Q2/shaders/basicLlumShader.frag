#version 330 core
in vec3 vert;
in vec3 norm ;
in mat3 matNormalInvers;
in vec3 posF;

in vec3 matam;
in vec3 matdif;
in vec3 matspe;
in float matshi;
uniform mat4 view;
uniform mat4 TG;
uniform vec3 posFocus; 
uniform vec3 llumAmbient; 
uniform vec3 colFocus ; 

out vec4 FragColor;

vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matam;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdif * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);
    // Calculem R i V
    if ((dot(NormSCO,L) < 0) || (matshi == 0))
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0 )
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), matshi);
    return (colRes + matspe * colFocus * shine); 
}
void main()
{	
	mat4 matNormal = view * TG;
	vec3 coordSCO = (matNormal * vec4 (vert, 1.0)).xyz ;
	vec3 L = posF - coordSCO;
	vec3 normalNormal = matNormalInvers * norm;
	L = normalize(L);
	normalNormal = normalize(normalNormal );
	vec3 a; 
	a = Phong(normalNormal, L, vec4(coordSCO, 1.0));
	FragColor = vec4(a,1.0);	
	//FragColor = vec4(matdif, 1);
}
