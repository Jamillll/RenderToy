#Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 u_MVP;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = u_MVP * vec4(aPos, 1.0);
}

#Fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    // Potential bug: A genuine texture coordinate is set to 0, 0
    if (TexCoords != vec2(0, 0))
    {
        FragColor = texture(texture_diffuse1, TexCoords);
    }
    else
    {
        FragColor = vec4(1, 1, 1, 1); 
    }
}