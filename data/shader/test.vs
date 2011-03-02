varying vec3 lightDir;
varying vec3 halfVector;

void main() {
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_TexCoord[2] = gl_TextureMatrix[2] * gl_MultiTexCoord2;
	gl_FrontColor = gl_Color;
	
	// now normalize the light's direction. Note that according to the OpenGL
	// specification, the light is stored in eye space. Also since we're talking
	// about a directional light, the position field is actually direction
	lightDir = normalize(vec3(gl_LightSource[0].position));

	// Normalize the halfVector to pass it to the fragment shader
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
}




/*
varying vec4 specular;
varying vec4 diffuse;
varying vec4 ambient;
varying vec3 lightDir;
varying vec3 halfVector;

void main() {
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_FrontColor = gl_Color;
	
	// now normalize the light's direction. Note that according to the OpenGL
	// specification, the light is stored in eye space. Also since we're talking
	// about a directional light, the position field is actually direction
	lightDir = normalize(vec3(gl_LightSource[0].position));

	// Normalize the halfVector to pass it to the fragment shader
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
				
	// Compute the specular, diffuse and ambient terms
	specular = gl_FrontMaterial.specular * gl_LightSource[0].specular;
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = (gl_FrontMaterial.ambient * gl_LightSource[0].ambient)
				+ (gl_FrontMaterial.ambient * gl_LightModel.ambient);
}
*/



/*
varying vec3 lightDir;
varying vec3 normal;

void main() {
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_FrontColor = gl_Color;
	
	// first transform the normal into eye space and normalize the result
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	// now normalize the light's direction. Note that according to the OpenGL
	// specification, the light is stored in eye space. Also since we're talking
	// about a directional light, the position field is actually direction
	lightDir = normalize(vec3(gl_LightSource[0].position));
}
*/

