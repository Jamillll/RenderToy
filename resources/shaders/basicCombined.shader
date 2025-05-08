#Vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;

out vec3 vertexColour;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	vertexColour = colour;
}

#Fragment
#version 330 core
in vec3 vertexColour;
out vec4 FragColour;

void main()
{
	FragColour = vec4(vertexColour, 1.0); 
}