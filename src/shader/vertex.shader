#version 330

layout(location = 0) in vec2 vPos;
out vec2 pPos;

void main() {
	pPos = vPos;
	gl_Position = vec4(2.0 * vPos - vec2(1.0), 0.0, 1.0);
}

