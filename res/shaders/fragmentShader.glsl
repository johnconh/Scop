#version 330 core

in vec3 ourColor;
in vec3 FragPos;

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

    vec3 normal = normalize(vec3(0.0, 0.0, 1.0));
    vec3 lightDir = normalize(vec3(lightPos - FragPos));
    vec3 viewDir = normalize(vec3(cameraPos - FragPos));
    vec3 reflectDir = reflect(lightDir, normal);
    
    float ambientStrength = 0.1;
    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    float specularStrength = pow(max(dot(viewDir, reflectDir), shininess), shininess);
    
    vec3 ambient = ambientStrength * ambientColor * ourColor;
    vec3 diffuse = diffuseStrength * diffuseColor * ourColor;
    vec3 specular = specularStrength * specularColor * ourColor;

    vec3 refractedLightDir = refract(-lightDir, normal, 1.0 / refraction);
    float refractionEffect = max(dot(normal, refractedLightDir), 0.0);
    vec3 refractionColor = refractionEffect * vec3(1.0, 1.0, 1.0);

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

    FragColor = vec4(color, transparency);
}