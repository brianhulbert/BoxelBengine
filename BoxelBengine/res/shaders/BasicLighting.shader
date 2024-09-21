#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;

out VS_OUT {
    vec2 v_texCoord;
	vec3 v_fragPos;
} vs_out;

uniform mat4 u_MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main() {
   gl_Position = proj * view * model * position;
   vs_out.v_texCoord = textCoord;
   vs_out.v_fragPos = vec3(model * vec4(position));
}

#shader geometry
#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 v_texCoord;
	vec3 v_fragPos;
} gs_in[];

out vec2 texCoord;
out vec3 fragPos;
out vec3 normal;

vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
} 

void main(){
	normal = GetNormal();

	gl_Position = gl_in[0].gl_Position;
	texCoord = gs_in[0].v_texCoord;
	fragPos = gs_in[0].v_fragPos;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	texCoord = gs_in[1].v_texCoord;
	fragPos = gs_in[1].v_fragPos;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	texCoord = gs_in[2].v_texCoord;
	fragPos = gs_in[2].v_fragPos;
	EmitVertex();
	EndPrimitive();
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform vec3 lightPos;
uniform vec3 lightColor;

in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;

void main() {
   float ambientLight = 0.1;

   vec3 lightDir = normalize(lightPos - fragPos);
   float diff = max(dot(normal, lightDir), ambientLight);
   vec3 diffuse = diff * lightColor;

   color = texture(u_Texture, texCoord) * vec4(diffuse, 1.0); 

   if (color.w < 0.3f) {
	   color = vec4(texCoord.x, 0.0f, texCoord.y, 0.3f);
   }
}
