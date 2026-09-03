#pragma once

#include <iostream>
#include <vector>
#include "Vector.hpp"
#include <stdexcept>

class Mat2{
public:
    Mat2():mat2(2, std::vector<float>(2, 0.0f)){}
    Mat2(const float a) : mat2(2, std::vector<float>(2, a)){}
    std::vector<float>& operator[](const int rows){
        return mat2[rows];
    }
    const std::vector<float>& operator[](const int rows) const{
        return mat2[rows];
    }
    Mat2 operator+(const Mat2& m) const {
        Mat2 result;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                result[i][j] = mat2[i][j] + m[i][j];
            }
        }
        return result;
    }
    Mat2 operator-(const Mat2& m) const {
        Mat2 result;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                result[i][j] = mat2[i][j] - m[i][j];
            }
        }
        return result;
    }
    Mat2& operator*=(const float a){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                mat2[i][j] *= a;
            }
        }
        return *this;
    }
    Mat2 operator*(const float a) const {
        Mat2 result;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                result[i][j] = mat2[i][j] * a;
            }
        }
        return result;
    }
    Vector2f operator*(const Vector2f& v) const {
        Vector2f result;
        result.x = mat2[0][0] * v.x + mat2[0][1] * v.y;
        result.y = mat2[1][0] * v.x + mat2[1][1] * v.y;
        return result;
    }
    Mat2 operator*(const Mat2& m) const{
        Mat2 result;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 2; k++){
                    result[i][j] += mat2[i][k] * m[k][j];
                }
            }
        }
        return result;
    }
    Mat2 transpose() const {
        Mat2 result;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                result[i][j] = mat2[j][i];
            }
        }
        return result;
    }
    float determinant() const{
        return mat2[0][0] * mat2[1][1] - mat2[0][1] * mat2[1][0];
    }
    Mat2 inverse() const {
        float det = determinant();
        if(std::abs(det) < 1e-6f){
            throw std::runtime_error("No 0 allowed!");
        }
        Mat2 result;
        result[0][0] =  mat2[1][1] / det;
        result[0][1] = -mat2[0][1] / det;
        result[1][0] = -mat2[1][0] / det;
        result[1][1] =  mat2[0][0] / det;

        return result;
    }
    static Mat2 Identity(){
        Mat2 result;
        for(int i = 0; i < 2; i++){
            result[i][i] = 1.0f;
        }
        return result;
    }
private:
    std::vector<std::vector<float>>mat2;

};

class Mat3 {

public:

    Mat3(): mat3(3, std::vector<float>(3, 0.0f)) {}

    Mat3(float a): mat3(3, std::vector<float>(3, a)) {}

    std::vector<float>& operator[](int row) {
        return mat3[row];
    }

    const std::vector<float>& operator[](int row) const {
        return mat3[row];
    }

    Mat3 operator+(const Mat3& m) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = mat3[i][j] + m[i][j];
            }
        }
        return result;
    }

    Mat3 operator-(const Mat3& m) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = mat3[i][j] - m[i][j];
            }
        }
        return result;
    }

    Mat3& operator*=(float a) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat3[i][j] *= a;
            }
        }
        return *this;
    }

    Mat3 operator*(float a) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = mat3[i][j] * a;
            }
        }
        return result;
    }

    Vector3f operator*(const Vector3f& v) const {
        Vector3f result;
        result.x = mat3[0][0] * v.x + mat3[0][1] * v.y + mat3[0][2] * v.z;
        result.y = mat3[1][0] * v.x + mat3[1][1] * v.y + mat3[1][2] * v.z;
        result.z = mat3[2][0] * v.x + mat3[2][1] * v.y + mat3[2][2] * v.z;

        return result;
    }

    Mat3 operator*(const Mat3& m) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    result[i][j] += mat3[i][k] * m[k][j];
                }
            }
        }
        return result;
    }

    Mat3 transpose() const {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = mat3[j][i];
            }
        }
        return result;
    }

    // 删除第 row 行，第 col 列，得到 2x2 子矩阵

    Mat2 minorMatrix(int row, int col) const {
        Mat2 result;
        int r = 0;
        for (int i = 0; i < 3; ++i) {
            if (i == row)
                continue;
            int c = 0;
            for (int j = 0; j < 3; ++j) {
                if (j == col)
                    continue;
                result[r][c] = mat3[i][j];
                ++c;
            }
            ++r;
        }
        return result;
    }

    // 余子式

    float minor(int row, int col) const {
        return minorMatrix(row, col).determinant();
    }

    // 代数余子式

    float cofactor(int row, int col) const {
        float value = minor(row, col);
        if ((row + col) % 2 != 0) {
            value = -value;
        }
        return value;
    }

    float determinant() const {
        float det = 0.0f;
        for (int col = 0; col < 3; ++col) {
            det += mat3[0][col] * cofactor(0, col);
        }
        return det;
    }

    Mat3 cofactorMatrix() const {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = cofactor(i, j);
            }
        }
        return result;
    }

    Mat3 inverse() const {
        float det = determinant();
        if (std::abs(det) < 1e-6f) {
            throw std::runtime_error("Matrix is not invertible");
        }

        // 伴随矩阵 = 代数余子式矩阵的转置

        Mat3 adjugate = cofactorMatrix().transpose(); 
        return adjugate * (1.0f / det);

    }

    static Mat3 Identity() {
        Mat3 result;
        for (int i = 0; i < 3; ++i) {
            result[i][i] = 1.0f;
        }
        return result;
    }

private:

    std::vector<std::vector<float>> mat3;

};

class Mat4 {
public:
    Mat4() : mat4(4, std::vector<float>(4, 0.0f)) {}

    Mat4(float a) : mat4(4, std::vector<float>(4, a)) {}

    std::vector<float>& operator[](int row) {
        return mat4[row];
    }

    const std::vector<float>& operator[](int row) const {
        return mat4[row];
    }

    Mat4 operator+(const Mat4& m) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result[i][j] = mat4[i][j] + m[i][j];
            }
        }
        return result;
    }

    Mat4 operator-(const Mat4& m) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result[i][j] = mat4[i][j] - m[i][j];
            }
        }
        return result;
    }

    Mat4& operator*=(float a) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                mat4[i][j] *= a;
            }
        }
        return *this;
    }

    Mat4 operator*(float a) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result[i][j] = mat4[i][j] * a;
            }
        }
        return result;
    }

    Vector4f operator*(const Vector4f& v) const {
        Vector4f result;
        result.x = mat4[0][0] * v.x + mat4[0][1] * v.y + mat4[0][2] * v.z + mat4[0][3] * v.w;
        result.y = mat4[1][0] * v.x + mat4[1][1] * v.y + mat4[1][2] * v.z + mat4[1][3] * v.w;
        result.z = mat4[2][0] * v.x + mat4[2][1] * v.y + mat4[2][2] * v.z + mat4[2][3] * v.w;
        result.w = mat4[3][0] * v.x + mat4[3][1] * v.y + mat4[3][2] * v.z + mat4[3][3] * v.w;
        return result;
    }

    Mat4 operator*(const Mat4& m) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    result[i][j] += mat4[i][k] * m[k][j];
                }
            }
        }
        return result;
    }

    Mat4 transpose() const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result[i][j] = mat4[j][i];
            }
        }
        return result;
    }

    // 删除第 row 行，第 col 列，得到 3x3 子矩阵

    Mat3 minorMatrix(int row, int col) const {
        Mat3 result;
        int r = 0;
        for (int i = 0; i < 4; ++i) {
            if (i == row)
                continue;
            int c = 0;
            for (int j = 0; j < 4; ++j) {
                if (j == col)
                    continue;
                result[r][c] = mat4[i][j];
                ++c;
            }
            ++r;
        }
        return result;
    }

    // 余子式

    float minor(int row, int col) const {
        return minorMatrix(row, col).determinant();
    }

    // 代数余子式

    float cofactor(int row, int col) const {
        float value = minor(row, col);
        if ((row + col) % 2 != 0) {
            value = -value;
        }
        return value;
    }

    float determinant() const {
        float det = 0.0f;
        for (int col = 0; col < 4; ++col) {
            det += mat4[0][col] * cofactor(0, col);
        }
        return det;
    }

    Mat4 cofactorMatrix() const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result[i][j] = cofactor(i, j);
            }
        }
        return result;
    }

    Mat4 inverse() const {
        float det = determinant();
        if (std::abs(det) < 1e-6f) {
            throw std::runtime_error("Matrix is not invertible");
        }
        Mat4 adjugate = cofactorMatrix().transpose();
        return adjugate * (1.0f / det);
    }

    static Mat4 Identity() {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            result[i][i] = 1.0f;
        }
        return result;
    }
private:
    std::vector<std::vector<float>> mat4;
};