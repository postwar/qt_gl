uniform sampler2D Tex0;
uniform sampler2D Tex1;
varying vec4 specular;
varying vec4 diffuse;
varying vec4 ambient;
varying vec3 lightDir;
varying vec3 halfVector;

void main() {
	vec4 ambientLight = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 diffuseLight = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularLight = vec4(0.0, 0.0, 0.0, 0.0);
	
	vec4 textureMap = texture2D(Tex1, gl_TexCoord[0].st);
	vec4 normalMap = texture2D(Tex0, gl_TexCoord[1].st);
	
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

