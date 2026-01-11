#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord;

out vec2 v_TextureCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
mat4 u_MVPMatrix;

void main()
{
   u_MVPMatrix = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix;
   gl_Position = u_MVPMatrix * position;
   v_TextureCoord = textureCoord;
}
