#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include "Vector3.h"
#include "Vertex.h"

struct Matrix4 
{
    float m[4][4];

    Matrix4 operator*(const Matrix4& other) const 
    {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k)
                {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }
};

struct Vector4
{
    float x, y, z, w;

    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
        : x(x), y(y), z(z), w(w){}

    Vector4 operator*(const Matrix4& m) const 
    {
        Vector4 result;
        result.x = x * m.m[0][0] + y * m.m[0][1] + z * m.m[0][2] + w * m.m[0][3];
        result.y = x * m.m[1][0] + y * m.m[1][1] + z * m.m[1][2] + w * m.m[1][3];
        result.z = x * m.m[2][0] + y * m.m[2][1] + z * m.m[2][2] + w * m.m[2][3];
        result.w = x * m.m[3][0] + y * m.m[3][1] + z * m.m[3][2] + w * m.m[3][3];
        return result;
    }
};

Matrix4 identity();
Matrix4 perspective(float fovy, float aspect, float near, float far);
Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);
Matrix4 rotate(Matrix4 m, float angle, Vector3 axis);
Matrix4 translateMatrix(float x, float y, float z);
//Matrix4 operator*(const Matrix4& a, const Matrix4& b);
Matrix4 rotateAroundCenter(Matrix4 m, float angle, Vector3 axis, Vector3 center);
Vector3 calculateObjectCenter(const std::vector<Vertex>& vertices);

#endif