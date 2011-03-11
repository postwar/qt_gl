uniform sampler2D tex;

void main() {
	vec4 color = vec4(gl_Color);
	
	if (texture2D(tex, vec2(gl_TexCoord[0])).a == 0.0) {
		color.a = 0.0;
	} else {
		color.a = 1.0;
	}
	
	gl_FragColor = color;
}
