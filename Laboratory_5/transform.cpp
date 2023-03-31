#include "transform.h" 

namespace egc {
    mat3 translate(const vec2 translateArray) {
        mat3 T;
        T.at(0, 2) = translateArray.x;
        T.at(1, 2) = translateArray.y;
        return T;
    }

    mat3 translate(float tx, float ty) {
        mat3 T;
        T.at(0, 2) = tx;
        T.at(1, 2) = ty;
        return T;
    }

    mat3 scale(const vec2 scaleArray) {
        mat3 T;
        T.at(0, 0) = scaleArray.x;
        T.at(1, 1) = scaleArray.y;
        return T;

    }

    mat3 scale(float sx, float sy) {
        mat3 T;
        T.at(0, 0) = sx;
        T.at(1, 1) = sy;
        return T;

    }

    mat3 rotate(float angle) {
        mat3 T;
        T.at(0, 0) = cos(angle * PI / 180);
        T.at(0, 1) = -sin(angle * PI / 180);
        T.at(1, 0) = sin(angle * PI / 180);
        T.at(1, 1) = cos(angle * PI / 180);
        return T;
    }

    mat4 translate(const vec3 translateArray) {
        mat4 T;
        T.at(0, 3) = translateArray.x;
        T.at(1, 3) = translateArray.y;
        T.at(2, 3) = translateArray.z;
        return T;
    }

    mat4 translate(float tx, float ty, float tz) {
        mat4 T;
        T.at(0, 3) = tx;
        T.at(1, 3) = ty;
        T.at(2, 3) = tz;
        return T;
    }

    mat4 scale(const vec3 scaleArray) {
        mat4 T;
        T.at(0, 0) = scaleArray.x;
        T.at(1, 1) = scaleArray.y;
        T.at(2, 2) = scaleArray.z;
        return T;
    }

    mat4 scale(float sx, float sy, float sz) {
        mat4 T;
        T.at(0, 0) = sx;
        T.at(1, 1) = sy;
        T.at(2, 2) = sz;
        return T;
    }

    mat4 rotateX(float angle) {
        mat4 T;
        T.at(1, 1) = cos(angle * PI / 180);
        T.at(1, 2) = -sin(angle * PI / 180);
        T.at(2, 1) = sin(angle * PI / 180);
        T.at(2, 2) = cos(angle * PI / 180);
        return T;
    }

    mat4 rotateY(float angle) {
        mat4 T;
        T.at(0, 0) = cos(angle * PI / 180);
        T.at(0, 2) = sin(angle * PI / 180);
        T.at(2, 0) = -sin(angle * PI / 180);
        T.at(2, 2) = cos(angle * PI / 180);
        return T;
    }

    mat4 rotateZ(float angle) {
        mat4 T;
        T.at(0, 0) = cos(angle * PI/ 180);
        T.at(0, 1) = -sin(angle * PI/ 180);
        T.at(1, 0) = sin(angle * PI/ 180);
        T.at(1, 1) = cos(angle * PI/ 180);
        return T;
    }


}