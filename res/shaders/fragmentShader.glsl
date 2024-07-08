#version 330 core

in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;

struct Material
{
    float Ni;
    float Ns;
    float d;
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    int illum;
};

out vec4 FragColor;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    vec3 ambientColor = material.Ka;
    vec3 diffuseColor = material.Kd;
    vec3 specularColor = material.Ks;
    float shininess = material.Ns;
    float transparency = material.d;
    float refraction = material.Ni;
    vec3 color;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    
    float ambientStrength = 1.0;
    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    
    vec3 ambient = ambientStrength * ambientColor;
    vec3 diffuse = diffuseStrength * diffuseColor;
    vec3 specular = specularStrength * specularColor;

    if (material.illum == 0)
    {
        color = ambientColor;
    }
    else if (material.illum == 1)
    {
        color =  ambient + diffuse;
    }
    else if (material.illum == 2)
    {
        color = ambient + diffuse + specular;
    }

    FragColor = vec4(color * ourColor, transparency);
}