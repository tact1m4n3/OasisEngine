#version 330

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TextureId;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec2 v_TextureCoord;
out vec4 v_Color;
out float v_TextureId;

void main()
{
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Position, 1.0);
	v_TextureCoord = a_TextureCoord;
	v_Color = a_Color;
	v_TextureId = a_TextureId;
}
