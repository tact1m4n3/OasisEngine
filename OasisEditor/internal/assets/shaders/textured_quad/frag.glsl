#version 330

in vec2 v_TextureCoord;
in vec4 v_Color;
in float v_TextureId;

layout(location = 0) out vec4 f_Color;

uniform sampler2D u_Textures[16];

void main()
{
	vec4 color = v_Color;

	switch(int(v_TextureId))
	{
		case  0: color *= texture(u_Textures[ 0], v_TextureCoord); break;
		case  1: color *= texture(u_Textures[ 1], v_TextureCoord); break;
		case  2: color *= texture(u_Textures[ 2], v_TextureCoord); break;
		case  3: color *= texture(u_Textures[ 3], v_TextureCoord); break;
		case  4: color *= texture(u_Textures[ 4], v_TextureCoord); break;
		case  5: color *= texture(u_Textures[ 5], v_TextureCoord); break;
		case  6: color *= texture(u_Textures[ 6], v_TextureCoord); break;
		case  7: color *= texture(u_Textures[ 7], v_TextureCoord); break;
		case  8: color *= texture(u_Textures[ 8], v_TextureCoord); break;
		case  9: color *= texture(u_Textures[ 9], v_TextureCoord); break;
		case 10: color *= texture(u_Textures[10], v_TextureCoord); break;
		case 11: color *= texture(u_Textures[11], v_TextureCoord); break;
		case 12: color *= texture(u_Textures[12], v_TextureCoord); break;
		case 13: color *= texture(u_Textures[13], v_TextureCoord); break;
		case 14: color *= texture(u_Textures[14], v_TextureCoord); break;
		case 15: color *= texture(u_Textures[15], v_TextureCoord); break;
	}

	f_Color = color;
}