#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in uint neighbors;
layout(location = 2) in uint voxelType;

out VS_OUT {
    vec4 v_fragColor;
	vec3 v_localPos;
	mat4 v_M;
	mat4 v_VP;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	if(voxelType){
		vs_out.v_M = model;
		vs_out.v_VP = proj * view;
		gl_Position = vs_out.v_VP * model * position;
		vs_out.v_fragColor = vec4(1.0);
		vs_out.v_localPos = position;
	}
	else{
		gl_Position = vec3(max(float));
	}
};

#shader geometry
#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec4 v_fragColor;
	vec3 v_localPos;
	mat4 v_M;
	mat4 v_VP;
} gs_in[];

out vec4 fragColor;
out vec3 worldPos;
out vec3 normal;

void main(){
	fragColor = gl_in[0].v_fragColor;

	vec3 worldP[3]; //world space positions of the vertices
	vec3 clipP[3];  //clip space positions of the vertices

	worldP[0] = gs_in[0].v_M * gs_in[0].v_localPos;
	clipP[0] = gs_in[0].gl_Position;
	worldP[1] = gs_in[0].v_M * (gl_in[0].v_localPos + vec3(0.0, 1.0, 0));
	clipP[1] = gl_in[0].v_VP * worldP[1];
	worldP[2] = gs_in[0].v_M * (gl_in[0].v_localPos + vec3(1.0, 0.0, 0));
	clipP[2] = gl_in[0].v_VP * worldP[2];

	normal = normalize(cross(clipP[0]-clipP[1], clipP[2]-clipP[1]));

	gl_Position = clipP[0];
	worldPos = worldP[0];
	EmitVertex();

	gl_Position = clipP[0];
	worldPos = worldP[0];
	EmitVertex();
	
	gl_Position = clipP[0];
	worldPos = worldP[0];
	EmitVertex();

	EndPrimitive();
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;

in vec4 fragColor;
in vec3 worldPos;
in vec3 normal;

void main() {
   float ambientLight = 0.1;

   vec3 lightDir = normalize(lightPos - worldPos);
   float diff = max(dot(normal, lightDir), ambientLight);
   vec3 diffuse = diff * lightColor;

   color = fragColor * vec4(diffuse, 1.0); 

   if (color.w < 0.3f) {
	   color = vec4(texCoord.x, 0.0f, texCoord.y, 0.3f);
   }
};