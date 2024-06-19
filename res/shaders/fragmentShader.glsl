#version 330 core

in vec3 ourColor;
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

void main()
{
    vec3 ambienColor = material.Ka;
    vec3 diffuseColor = material.Kd;
    vec3 specularColor = material.Ks;
    float shininess = material.Ns;
    float transparency = material.Ni;
    vec3 color;

    if (material.illum == 0)
    {
        color = ambienColor;
    }
    else if (material.illum == 1)
    {
        color = ambienColor + diffuseColor;
    }
    else if (material.illum == 2)
    {
        vec3 normal = normalize(vec3(0.0, 0.0, 1.0));
        vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
        vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));
        vec3 reflectDir = reflect(-lightDir, normal);
        
        float ambientStrength = 0.1;
        float diffuseStrength = max(dot(normal, lightDir), 0.0);
        float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        
        vec3 ambient = ambientStrength * ambienColor;
        vec3 diffuse = diffuseStrength * diffuseColor;
        vec3 specular = specularStrength * specularColor * (1.0 - transparency);

        color = ambient + diffuse + specular;
    }

    FragColor = vec4(color * ourColor, 1);
}