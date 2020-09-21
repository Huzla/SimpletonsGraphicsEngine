#version 330 core
layout (location = 0) in vec3 aPos; // position attribute located in attribute 0.
layout (location = 1) in vec3 aNormal; // texture coordinates located in attribute 1.
layout (location = 2) in vec2 aTexCoords; // texture coordinates located in attribute 1.

uniform mat4 viewModel;
uniform mat4 projection;   

out vec3 vertexColor; // Vertex color for the fragment shader.
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;


void main()
{
    gl_Position = projection * viewModel * vec4(aPos, 1.0f);
    TexCoord = aTexCoords;

    FragPos = vec3(viewModel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(viewModel))) * aNormal;
}