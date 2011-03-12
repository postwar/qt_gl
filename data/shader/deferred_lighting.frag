uniform sampler2D Tex0;
uniform sampler2D Tex1;
uniform sampler2D Tex2;
uniform sampler2D Tex3;

void main(void) {
	vec4 position = texture2D(Tex0, gl_TexCoord[0].st);
	vec4 normal = texture2D(Tex1, gl_TexCoord[0].st);
	vec4 color = texture2D(Tex2, gl_TexCoord[0].st); 
	vec4 specular = texture2D(Tex3, gl_TexCoord[0].st);

	gl_FragColor = 1.0 * position + 1.0 * normal + 1.0 * color + 1.0 * specular;
} 
