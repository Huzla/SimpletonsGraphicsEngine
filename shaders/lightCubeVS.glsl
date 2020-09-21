#version 330 core
layout (location = 0) in vec3 aPos; // position attribute located in attribute 0.

uniform mat4 transformation;

void main()
{
    gl_Position = transformation * vec4(aPos, 1.0f);
}