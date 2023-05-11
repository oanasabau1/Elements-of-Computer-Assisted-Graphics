#include "projection.h"

namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height) {
        mat4 viewTransformMatrix;

        viewTransformMatrix.at(0, 0) = (float)(width / 2.0);
        viewTransformMatrix.at(1, 1) = (float)(height / 2.0) * -1;
        viewTransformMatrix.at(0, 3) = (float)(width / 2.0 + startX);
        viewTransformMatrix.at(1, 3) = (float)(height / 2.0 + startY);
        return viewTransformMatrix;
    }

    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera camera) {
        mat4 matrixUVW, matrixE;
        vec3 g, u, v, w;

        g = camera.cameraTarget - camera.cameraPosition;

        w = g.normalize() * -1;
        u = crossProduct(camera.cameraUp, w).normalize();
        v = crossProduct(w, u);

        matrixE.at(0, 3) = -1 * camera.cameraPosition.x;
        matrixE.at(1, 3) = -1 * camera.cameraPosition.y;
        matrixE.at(2, 3) = -1 * camera.cameraPosition.z;

        matrixUVW.at(0, 0) = u.x;
        matrixUVW.at(0, 1) = u.y;
        matrixUVW.at(0, 2) = u.z;

        matrixUVW.at(1, 0) = v.x;
        matrixUVW.at(1, 1) = v.y;
        matrixUVW.at(1, 2) = v.z;

        matrixUVW.at(2, 0) = w.x;
        matrixUVW.at(2, 1) = w.y;
        matrixUVW.at(2, 2) = w.z;

        return matrixUVW * matrixE;
    }

    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar) {
        mat4 perspProjectMatrix;
        auto tang = (float)tan(fov / 2.0);

        perspProjectMatrix.at(0, 0) = (float)(-1.0 / (aspect * tang));
        perspProjectMatrix.at(1, 1) = (float)(-1.0 / tang);
        perspProjectMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
        perspProjectMatrix.at(2, 3) = (float)((2.0 * zFar * zNear) / (zFar - zNear));
        perspProjectMatrix.at(3, 2) = 1.0;
        perspProjectMatrix.at(3, 3) = 0.0;

        return perspProjectMatrix;
    }


    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4& inputVertex) {
        inputVertex = inputVertex * (1.0f / inputVertex.w);
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4& vertex) {
        return -1 * vertex.w <= vertex.x && vertex.x <= vertex.w &&
            -1 * vertex.w <= vertex.y && vertex.y <= vertex.w &&
            -1 * vertex.w <= vertex.z && vertex.z <= vertex.w;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4>& triangle) {
        return clipPointInHomogeneousCoordinate(triangle.at(0)) ||
            clipPointInHomogeneousCoordinate(triangle.at(1)) ||
            clipPointInHomogeneousCoordinate(triangle.at(2));
    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4>& triangle) {
        egc::vec4 pA, pB, pC;

        pA = triangle.at(1);
        pB = triangle.at(0);
        pC = triangle.at(2);
        return crossProduct((pB - pA), (pC - pA)).normalize();
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4>& triangle) {
        egc::vec4 center;
        center.x = (triangle.at(0).x + triangle.at(1).x + triangle.at(2).x) / 3.0f;
        center.y = (triangle.at(0).y + triangle.at(1).y + triangle.at(2).y) / 3.0f;
        center.z = (triangle.at(0).z + triangle.at(1).z + triangle.at(2).z) / 3.0f;
        center.w = (triangle.at(0).w + triangle.at(1).w + triangle.at(2).w) / 3.0f;
        return center;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4>& triangle, const egc::vec3& normalVector) {
        return dotProduct(triangle.at(0), normalVector) > 0 ||
            dotProduct(triangle.at(1), normalVector) > 0 ||
            dotProduct(triangle.at(2), normalVector) > 0;
    }

    vec4 getCenterPoint(egc::vec4& triangleCenter, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix) {
        vec4 centerPoint = triangleCenter;
        centerPoint = perspectiveMatrix * centerPoint;
        perspectiveDivide(centerPoint);
        return viewTransformMatrix * centerPoint;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
    void displayNormalVectors(egc::vec3& normalVector, egc::vec4& triangleCenter, SDL_Renderer* renderer,
        egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix) {
        vec4 centerPoint = getCenterPoint(triangleCenter, viewTransformMatrix, perspectiveMatrix);

        vec4 secondPoint;
        secondPoint.x = centerPoint.x + (normalVector.x * 90.0f);
        secondPoint.y = centerPoint.y + (normalVector.y * 90.0f);
        SDL_RenderDrawLine(renderer, (int)centerPoint.x, (int)centerPoint.y, (int)secondPoint.x,
            (int)secondPoint.y);
    }
}