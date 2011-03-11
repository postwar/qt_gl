varying vec4 position;

void main() {
	gl_FragColor = vec4(position.x / 1000.0, 1.0, 1.0, 1.0);
}
