#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 translation;
layout(location = 3) in vec3 rotation;

out vec2 v_texCoord;

uniform mat4 PV;

mat4 rotationMatrix(vec3 angles) {
    float c1 = cos(angles.x); float s1 = sin(angles.x); // Pitch
    float c2 = cos(angles.y); float s2 = sin(angles.y); // Yaw
    float c3 = cos(angles.z); float s3 = sin(angles.z); // Roll

    mat4 rotX = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, c1, -s1, 0.0,
        0.0, s1, c1, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 rotY = mat4(
        c2, 0.0, s2, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -s2, 0.0, c2, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 rotZ = mat4(
        c3, -s3, 0.0, 0.0,
        s3, c3, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return rotZ * rotY * rotX; // Rotation order: Z * Y * X
}

void main() {
    mat4 M = mat4(1.0); // Initialize to identity matrix

    // Apply rotation
    mat4 rotMat = rotationMatrix(rotation);
    M = rotMat * M;

    //Apply translation
    mat4 transMat = mat4(1.0);
    transMat[3].xyz = uTranslation; // Set translation in the fourth column
    M = transMat * M;

    mat4 MVP = PV * M;

    gl_Position = MVP * position;
    v_texCoord = textCoord;
};

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
};