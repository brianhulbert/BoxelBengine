#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;

void main() {
   gl_Position = u_MVP * position;
   v_texCoord = textCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

in vec2 v_texCoord;

void main() {

   color = texture(u_Texture, v_texCoord);

   if (color.w < 0.3f) {
	   color = vec4(v_texCoord.x, 0.0f, v_texCoord.y, 0.3f);
   }
}
