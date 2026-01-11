#version 330 core

in vec2 v_TextureCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor = texture(u_Texture, v_TextureCoord);
   gl_FragColor = texColor * 0.7 + u_Color * 0.3;
}
