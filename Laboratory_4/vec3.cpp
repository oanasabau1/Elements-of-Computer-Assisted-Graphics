#include"vec3.h"

namespace egc {
    vec3& vec3::operator =(const vec3& srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        return *this;
    }

    vec3 vec3::operator +(const vec3& srcVector) const {
        return vec3(this->x + srcVector.x, this->y + srcVector.y, this->z + srcVector.z);
    }

    vec3& vec3::operator +=(const vec3& srcVector) {
        this->x = this->x + srcVector.x;
        this->y = this->y + srcVector.y;
        this->z = this->z + srcVector.z;
        return *this;
    }

    vec3 vec3::operator *(float scalarValue) const {
        return vec3(this->x * scalarValue, this->y * scalarValue, this->z * scalarValue);
    }

    vec3 vec3::operator -(const vec3& srcVector) const {
        return vec3(this->x - srcVector.x, this->y - srcVector.y, this->z - srcVector.z);
    }

    vec3& vec3::operator -=(const vec3& srcVector) {
        this->x = this->x - srcVector.x;
        this->y = this->y - srcVector.y;
        this->z = this->z - srcVector.z;
        return *this;
    }

    vec3 vec3::operator -() const {
        return vec3(-this->x, -this->y, -this->z);
    }

    float vec3::length() const {
        float norma = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        return norma;
    }

    vec3& vec3::normalize() {
        float norma = length();
        x = x / norma;
        y = y / norma;
        z = z / norma;
        return *this;
    }

    float dotProduct(const vec3& v1, const vec3& v2) {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }

    vec3 crossProduct(const vec3& v1, const vec3& v2) {
        vec3 produs;
        produs.x = v1.y * v2.z - v1.z * v2.y;
        produs.y = v1.z * v2.x - v1.x * v2.z;
        produs.z = v1.x * v2.y - v1.y * v2.x;
        return produs;
    }
}