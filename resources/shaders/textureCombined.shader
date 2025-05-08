#Vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 fragTexCoords;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	fragTexCoords = texCoords;
}

#Fragment
#version 330 core
in vec2 fragTexCoords;
out vec4 FragColour;

uniform sampler2D u_Texture;

void main()
{
	FragColour = texture(u_Texture, fragTexCoords);
}