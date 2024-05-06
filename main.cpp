#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Current compile command
//g++ main.cpp ./src/glad.c -I./include/ -I./include/glm-master -std=c++11 -o a.out -lSDL2 -ldl

// Globals
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const std::string vertexShaderFileName = "./shaders/vertex.glsl";
const std::string fragmentShaderFileName = "./shaders/frag.glsl";

SDL_Window* graphicsWindow = nullptr;
SDL_GLContext openGLContext = nullptr;
bool gQuit = false;
GLuint VBO = 0;
GLuint IBO = 0;
GLuint VAO = 0;
GLuint GraphicsPipeline = 0;
GLfloat u_offSet = 0;
static void GLClearErrors(){
    while(glGetError() != GL_NO_ERROR){
    }
}

static bool GLCheckErrorStatus(const char* function, int line){
    while(GLenum error = glGetError()){
        std::cout << "ERROR:" << error << "\nLINE:" << line << "\nFUNCTION:" << function <<std::endl;
        return true;
    }
    return false;
}
#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__ );
std::string getFileString(const std::string& fileName){
    try{
        std::string result = "";
        std::string line = "";
        std::ifstream myFile(fileName.c_str());
        if(myFile.is_open()){
            while(std::getline(myFile, line)){
                result += line + "\n";
            }
            myFile.close();
        }
        return result;
    }
    catch(std::exception& e){
        std::cout << "File -" + fileName + "- unable to be opened" << std::endl;
        exit(1);
    }
}

void getOpenGLVersionInfo(){
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl; 
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl; 
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl; 
    std::cout << "Shaidng Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 

}
void getInput(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            std::cout << "Terminating" << std::endl;
            gQuit = true;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP]){
        u_offSet += 0.01f;
    }
    if(state[SDL_SCANCODE_DOWN]){
        u_offSet -= 0.01f;
    }
}

void preDrawFunc(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
    glUseProgram(GraphicsPipeline);
    GLint perspectiveLoc= glGetUniformLocation(GraphicsPipeline, "u_perspectiveMat");
    GLint translateLoc= glGetUniformLocation(GraphicsPipeline, "u_modelMat");
    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 10.0f);
    glm::mat4 translationMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f,0.0f,u_offSet));
    if(perspectiveLoc >= 0){
        glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, &perspectiveMatrix[0][0]);
    }
    else{
        std::cout << "error in u_prespectiveMat" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(translateLoc >= 0){
        glUniformMatrix4fv(translateLoc, 1, GL_FALSE, &translationMatrix[0][0]);
    }
    else{
        std::cout << "error in u_modelMat" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void drawFunc(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glDrawArrays(GL_TRIANGLES,0,6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glUseProgram(0);
}

void InitializeProgram(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL2 could not initialize video system" 
            << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    graphicsWindow = SDL_CreateWindow("BirdbrainProgram", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(graphicsWindow == nullptr){
        std::cout << "SDL_Window could not be created" 
            << std::endl;
        exit(1);
    }
    openGLContext = SDL_GL_CreateContext(graphicsWindow);
    if(openGLContext == nullptr){
        std::cout << "Context not avaliable" 
            << std::endl;
        exit(1);
    }
    //Initialize Glad Libary
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Glad unable to be initialized" 
            << std::endl;
        exit(1);
    }
    getOpenGLVersionInfo();

}

GLuint CompileShader(GLuint type, const std::string& source){
    GLuint shaderObject;

    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);

    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS,  &success);
    if(!success){
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        if(type == GL_VERTEX_SHADER){
            std::cout << "ERROR OCCURED IN VERTEX SHADER"<< std::endl;
        }else if(type == GL_FRAGMENT_SHADER){
            std::cout << "ERROR OCCURED IN FRAGMENT SHADER"<< std::endl;
        }
        glDeleteShader(shaderObject);
        return 0;
    }
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource){
    GLuint programObject = glCreateProgram();
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);

    glDetachShader(programObject, vertexShader);
    glDetachShader(programObject, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}
void CreateGraphicsPipeline(){
    GraphicsPipeline = CreateShaderProgram(
        getFileString(vertexShaderFileName), 
        getFileString(fragmentShaderFileName));
}

void VertexSpecification(){

    const std::vector<GLfloat> verticeData{
        // Vertex 0
        -0.5f, -0.5f, 0.0f, // Vector
        1.0f, 0.0f, 0.0f, // Color
        // Vertex 1
        0.5f, -0.5f, 0.0f, // Vector
        0.0f, 1.0f, 0.0f, // Color
        // Vertex 2
        -0.5f, 0.5f, 0.0f, // Vector
        0.0f, 0.0f, 1.0f, //Color
        // Vertex 3
        0.5f, 0.5f, 0.0f, // Vector
        .0f, 0.0f, 1.0f, // Color
    };

    const std::vector<GLuint> indexBufferData{2,0,1, 3,2,1};
    // Generates VAO
    // Sets up on the GPU
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generates VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticeData.size() * sizeof(GLfloat), verticeData.data(), GL_STATIC_DRAW);

    // Generates IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferData.size()*sizeof(GLuint), indexBufferData.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*6, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*6, (void*)(sizeof(GL_FLOAT)*3));
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void MainLoop(){
    while (!gQuit){
        getInput();

        preDrawFunc();

        drawFunc();

        SDL_GL_SwapWindow(graphicsWindow);
    }
}
void CleanUp(){
    //Destroy window
    SDL_DestroyWindow(graphicsWindow);
    //Quit SDL subsystems
    SDL_Quit();
}
// Test
int main(){
    // Initializes SDL and OpenGL while opening window
    InitializeProgram();

    // Specifies VAO and VBO
    VertexSpecification();

    // Creates shaders, both fragment and vector
    CreateGraphicsPipeline();

    // Continually draws over file
    MainLoop();

    // Ends running subsystems
    CleanUp();

    return 0;
}
