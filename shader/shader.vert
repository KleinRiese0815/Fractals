#version 330 core
layout(loation = 0) in vec4  position;
uniform mat4 projection;
uniform mat4 view;

void main()
{
   gl_Position = view * projection * position;
}
