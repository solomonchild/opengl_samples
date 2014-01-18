#version 400
out vec4 frag_colour;
uniform vec4 input_color;
void main () {
	frag_colour = input_color;
}