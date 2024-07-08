#ifndef MATRIX_H
#define MATRIX_H

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Matrix4 {
    float m[4][4];
};

Matrix4 identity();
Matrix4 perspective(float fovy, float aspect, float near, float far);
Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);
Matrix4 rotate(Matrix4 m, float angle, Vector3 axis);

#endif