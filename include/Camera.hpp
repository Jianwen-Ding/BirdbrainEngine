#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

// Deals with creating view matrix
// Repersenents virtual camera
class Camera{
    private:
        // Creates View Matrix
        glm::vec3 eye;
        glm::quat viewOrientation;
        glm::vec3 upVector;
        glm::vec2 oldMousePosition;

        // Handles Perspective Matrix
        float fov;
        float viewCloseCutoff;
        float viewFarCutoff;
    public:
        // Constructor
        Camera();

        glm::mat4 getViewMat() const;
        glm::vec3 getViewLocation() const;
        glm::vec3 getFowardVec();
        void mouseLook(float mouseX, float mouseY);
        void moveFoward(float speed);
        void moveBackwards(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);
        void moveUp(float speed);
        void moveDown(float speed);
    
};
#endif
