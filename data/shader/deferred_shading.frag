uniform sampler2D Tex0;
uniform sampler2D Tex1;
uniform sampler2D Tex2;
varying vec4 position;
// varying vec3 normal;

void main() {
	vec4 color = texture2D(Tex0, gl_TexCoord[0].st);
	vec4 normal = texture2D(Tex1, gl_TexCoord[1].st);
	vec4 specular = texture2D(Tex2, gl_TexCoord[2].st);
	
	float x = position.x / 800.0 + 0.5;
	float y = position.y / 600.0 + 0.5;
	float z = position.z / 1024.0;
	
	float nx = normal.x * 2.0 - 1.0;
	float ny = normal.y * 2.0 - 1.0;
	float nz = normal.z * 2.0 - 1.0;

	gl_FragData[0] = vec4(x, y, z, 1.0);
	gl_FragData[0] = vec4(1.0, 0.0, 0.0, 1.0); // vec4(nx, ny, nz, 1.0);
	gl_FragData[0] = vec4(0.0, 1.0, 0.0, 1.0); // vec4(color.rgb, 1.0);
	gl_FragData[0] = vec4(0.0, 0.0, 1.0, 1.0); // vec4(specular.rgb, 1.0);
}
