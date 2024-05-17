#ifndef RENDERERBASE
#define RENDERERBASE

// Standard C
#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <fstream>

// Including SDL
#include <SDL2/SDL.h>

// Including C++
#include <glad/glad.h>

// Including GLM (math libay)
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

// External Classes
#include "Camera.hpp"
#include "stb_image.h"

// >>>>>>FUNCTION OF CLASS<<<<<<
// Stores vertex models, textures, and shaders.
// Stores instances of each vertex model with the same shader together as meshes.
// Each mesh will have seperate transforms and texture  

// Tasks
// 1st: render out individual meshes + transforms
// 2nd: render out different shaders
// 3rd: render out different textures
class RendererBase{
    private:
        class meshObject{
            public: 
                // Base vertice specifications
                GLuint VBO;
                GLuint IBO;

                // Uses preloaded specification
                GLint VAOIndex;

                // Transformation
                glm::vec3 scale;
                glm::quat orientation;
                glm::vec3 positition;

                meshObject();
        };
        // Dimensions of Window
        int windowWidth;
        int windowHeight;

        // Instances of rendering base
        SDL_Window* graphicsWindow;
        SDL_GLContext* openGLContext;
        
        // Vertex specificiations
        std::deque<GLuint> listVAO;
        std::deque<meshObject> meshes;
        
        // List of created textures
        // std::deque<GLuint> listTextures;
        // std::deque<GLuint> listShaders;
        bool gQuit = false;

        // Camera orientation
        Camera viewCam;

    public:
        // Creates a new VAO and binds it into the list
        void drawAllObjects();
        GLuint generateVAO();
        void insertConstElementMesh(const std::vector<GLfloat> Vertices, const std::vector<GLuint> Indices);
        RendererBase();
};
#endif