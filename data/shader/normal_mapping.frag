uniform sampler2D Tex0;
uniform sampler2D Tex1;
uniform sampler2D Tex2;
varying vec3 lightDir;
varying vec3 halfVector;


/**
 * http://wiki.gamedev.net/index.php/OpenGL:Tutorials:GLSL_Bump_Mapping
 */
void main() {
	vec4 ambient = (gl_LightSource[0].ambient + gl_LightModel.ambient) * gl_FrontMaterial.ambient;
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 textureMap = texture2D(Tex0, gl_TexCoord[0].st);
	vec4 normalMap = texture2D(Tex1, gl_TexCoord[0].st);
	vec4 specularMap = texture2D(Tex2, gl_TexCoord[0].st);
	
	vec3 normal = normalize(normalMap.rgb) * 2.0 - 1.0;
	float lambert = dot(normal, normalize(lightDir));
	
	if (lambert > 0.0) {
		diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * lambert;
		
		float specularStrength = max(dot(normal, normalize(halfVector)), 0.0);
		specular = specularMap * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(specularStrength, gl_FrontMaterial.shininess);
	}
	
	vec4 light = vec4(ambient.rgb + diffuse.rgb + specular.rgb, gl_FrontMaterial.diffuse.a);
	vec4 color = textureMap;
	
	// gl_FragColor = light * color;
	gl_FragData[0] = light * color;
}

/*
void main() {
	// Compute the specular, diffuse and ambient terms
	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular;
	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	vec4 ambient = gl_FrontMaterial.ambient * (gl_LightSource[0].ambient) + gl_LightModel.ambient);

	vec4 ambientLight = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 diffuseLight = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularLight = vec4(0.0, 0.0, 0.0, 0.0);
	
	vec4 textureMap = texture2D(Tex0, gl_TexCoord[0].st);
	vec4 normalMap = texture2D(Tex1, gl_TexCoord[0].st);
	
	vec3 normal = normalize(normalMap.rgb) * 2.0 - 1.0;
	
	
	ambientLight = ambient;
	
	
	float intensity = max(dot(normal, normalize(lightDir)), 0.0);

	if (intensity > 0.0) {
		diffuseLight = diffuse * intensity;
		
		vec3 halfV = normalize(halfVector);
		float NdotHV = max(dot(normal, halfV), 0.0);
		
		specularLight = specular * pow(NdotHV, gl_FrontMaterial.shininess);
	}
	
	vec4 light = ambientLight + diffuseLight + specularLight;

	vec3 colorLight = light.rgb;
	float alphaLight = gl_FrontMaterial.diffuse.a;
	
	vec3 colorTexture = textureMap.rgb;
	float alphaTexture = textureMap.a;

	gl_FragColor = vec4(colorTexture * colorLight, alphaTexture * alphaLight);
}
*/

/*
uniform sampler2D Tex0;
uniform sampler2D Tex1;
varying vec3 lightDir;
varying vec3 normal;

void main() {
	vec4 textureMap = texture2D(Tex1, gl_TexCoord[0].st);
	vec4 normalMap = texture2D(Tex0, gl_TexCoord[1].st);
	
	vec3 normal;
	normal = normalMap.rgb;
	normal = normalize(normal) * 2.0 - 1.0;
	
	float intensity = max(dot(normalize(normal), normalize(lightDir)), 0.0);
	
	gl_FragColor = textureMap * intensity;
}
*/


/*
// Source: http://wiki.delphigl.com/index.php/Tutorial_glsl2
varying vec3 normal;
varying vec3 v;
varying vec3 lightvec;
 
void main(void) {
	vec3 Eye             = normalize(-v);

	vec3 Reflected       = normalize( reflect( -lightvec, normal )); 
	//hat den selben effekt wie
	//vec3 Reflected       = normalize( 2.0 * dot(normal, lightvec) *  normal - lightvec);

	vec4 IAmbient        = gl_LightSource[0].ambient;
	vec4 IDiffuse        = gl_LightSource[0].diffuse * max(dot(normal, lightvec), 0.0);
	vec4 ISpecular       = gl_LightSource[0].specular * pow(max(dot(Reflected, Eye), 0.0), gl_FrontMaterial.shininess);
	gl_FragColor         = gl_FrontLightModelProduct.sceneColor + IAmbient + IDiffuse + ISpecular;
}
*/

