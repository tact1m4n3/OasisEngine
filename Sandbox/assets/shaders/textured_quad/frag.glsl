#version 330

in vec2 v_TextureCoord;
in vec4 v_Color;
in float v_TextureId;

layout(location = 0) out vec4 f_Color;

uniform sampler2D u_Textures[16];

void main()
{
	f_Color = texture(u_Textures[int(v_TextureId)], v_TextureCoord) * v_Color;
}