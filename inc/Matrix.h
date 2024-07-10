#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include "Vector3.h"
#include "Vertex.h"

struct Matrix4 {
    float m[4][4];
};

Matrix4 identity();
Matrix4 perspective(float fovy, float aspect, float near, float far);
Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);
Matrix4 rotate(Matrix4 m, float angle, Vector3 axis);
Matrix4 translateMatrix(float x, float y, float z);
Matrix4 operator*(const Matrix4& a, const Matrix4& b);
Matrix4 rotateAroundCenter(float angle, Vector3 axis, Vector3 center);
Vector3 calculateObjectCenter(const std::vector<Vertex>& vertices);

#endif