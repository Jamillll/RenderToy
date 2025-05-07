#version 330 core
in vec2 texCoords;
out vec4 FragColour;

uniform sampler2D u_FramebufferTexture;

void main()
{
	FragColour = texture(u_FramebufferTexture, texCoords); 
}