#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexture;

out vec3 ourColor;
out vec3 FragPos;
out vec3 Normal;
out vec2 Texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalize (aNormal);
    ourColor = aColor;
    Texture = vec2(aTexture.x, aTexture.y);
}