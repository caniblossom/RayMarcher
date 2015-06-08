#version 330

uniform sampler2D tex0;

in  vec2 pPos;
out vec4 cOut;

void main() {
	cOut = texture(tex0, pPos);
}