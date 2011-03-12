varying vec4 position;
varying vec3 normal;

void main() {
	position = gl_ModelViewProjectionMatrix * gl_Vertex;
	normal = normalize(gl_NormalMatrix * gl_Normal);
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
	gl_TexCoord[2] = gl_MultiTexCoord2;
	
	gl_Position = position;
}
