
#include "../inc/Matrix.h"
#include <iostream>
#include <cmath>
#include <cstring>

//fovy = Field of view in y direction (Campo de visión en la dirección y)
//aspect = Aspect ratio (Relación de aspecto)
//near = Near plane (Plano cercano)
//far = Far plane (Plano lejano)

Vector3 normalize(Vector3 v) //Esta funcion normaliza el vecto a longitud 1
{
    float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return {v.x / magnitude, v.y / magnitude, v.z / magnitude};
}

Vector3 sub(Vector3 v1, Vector3 v2)  //Esta funcion resta dos vectores
{
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3 cross(Vector3 v1, Vector3 v2) //Esta funcion realiza el producto cruz de dos vectores
{
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

float dot(Vector3 v1, Vector3 v2) //Esta funcion realiza el producto punto de dos vectores
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


Matrix4 identity() //Esta funcion crea una matriz identidad
{
    Matrix4 m;
    std::memset(m.m, 0, sizeof(m.m));
    m.m[0][0] = 1.0f;
    m.m[1][1] = 1.0f;
    m.m[2][2] = 1.0f;
    m.m[3][3] = 1.0f;
    return m;
}

Matrix4 perspective(float fovy, float aspect, float near, float far) //Esta funcion crea una matriz de perspectiva
{
    float f = 1.0f / std::tan(fovy / 2.0f);
    Matrix4 m;
    std::memset(m.m, 0, sizeof(m.m));
    m.m[0][0] = f / aspect;
    m.m[1][1] = f;
    m.m[2][2] = (far + near) / (near - far);
    m.m[2][3] = -1.0f;
    m.m[3][2] = (2.0f * far * near) / (near - far);
    return m;
}

Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up) //Esta funcion crea una matriz de vista
{
    Vector3 f = normalize(sub(center, eye));
    Vector3 s = normalize(cross(f, up));
    Vector3 u = cross(s, f);
    Matrix4 m;
    std::memset(m.m, 0, sizeof(m.m));
    m.m[0][0] = s.x;
    m.m[0][1] = s.y;
    m.m[0][2] = s.z;
    m.m[1][0] = u.x;
    m.m[1][1] = u.y;
    m.m[1][2] = u.z;
    m.m[2][0] = -f.x;
    m.m[2][1] = -f.y;
    m.m[2][2] = -f.z;
    m.m[3][0] = -dot(s, eye);
    m.m[3][1] = -dot(u, eye);
    m.m[3][2] = dot(f, eye);
    m.m[3][3] = 1.0f;
    return m;
}

Matrix4 rotate(Matrix4 m, float angle, Vector3 axis) //Esta funcion rota una matriz
{
    Vector3 a = normalize(axis);
    float s = std::sin(angle);
    float c = std::cos(angle);
    float t = 1.0f - c;
    Matrix4 r;
    r.m[0][0] = t * a.x * a.x + c;
    r.m[0][1] = t * a.x * a.y + s * a.z;
    r.m[0][2] = t * a.x * a.z - s * a.y;
    r.m[0][3] = 0.0f;
    r.m[1][0] = t * a.x * a.y - s * a.z;
    r.m[1][1] = t * a.y * a.y + c;
    r.m[1][2] = t * a.y * a.z + s * a.x;
    r.m[1][3] = 0.0f;
    r.m[2][0] = t * a.x * a.z + s * a.y;
    r.m[2][1] = t * a.y * a.z - s * a.x;
    r.m[2][2] = t * a.z * a.z + c;
    r.m[2][3] = 0.0f;
    r.m[3][0] = 0.0f;
    r.m[3][1] = 0.0f;
    r.m[3][2] = 0.0f;
    r.m[3][3] = 1.0f;
    Matrix4 result;
    std::memset(result.m, 0, sizeof(result.m));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                result.m[i][j] += m.m[i][k] * r.m[k][j];
            }
        }
    }
    return result;
}

Matrix4 rotateAroundCenter(Matrix4 m, float angle, Vector3 axis, Vector3 center) //Esta funcion rota una matriz alrededor de un punto
{
    Matrix4 translation = translateMatrix(-center.x, -center.y, -center.z);
    Matrix4 rotation = rotate(identity(), angle, axis);
    Matrix4 invTranslation = translateMatrix(center.x, center.y, center.z);
    return translation * rotation *  invTranslation * m;
}

Matrix4 translateMatrix(float x, float y, float z)
{
    Matrix4 m = identity();
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}

Vector3 calculateObjectCenter(const std::vector<Vertex>& vertices)
{
    Vector3 center = {0.0f, 0.0f, 0.0f};
    for (const Vertex& vertex : vertices)
    {
        center.x += vertex.x;
        center.y += vertex.y;
        center.z += vertex.z;
    }
    return {center.x / static_cast<float>(vertices.size()), center.y / static_cast<float>(vertices.size()), center.z / static_cast<float>(vertices.size())};
}

