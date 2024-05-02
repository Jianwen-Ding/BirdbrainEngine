#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

// Current compile command
//g++ main.cpp ./src/glad.c -I./include/ -std=c++11 -o a.out -lSDL2 -ldl

// Globals
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

SDL_Window* graphicsWindow = nullptr;
SDL_GLContext openGLContext = nullptr;
bool gQuit = false;
GLuint VBO = 0;
GLuint VAO = 0;
GLuint GraphicsPipeline = 0;

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
}

void preDrawFunc(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
    glUseProgram(GraphicsPipeline);
}

void drawFunc(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES,0,3);
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
        std::cout << "Context not avaliable" << std::endl;
        exit(1);
    }
    //Initialize Glad Libary
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Glad unable to be initialized" << std::endl;
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
    GraphicsPipeline = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void VertexSpecification(){

    const std::vector<GLfloat> vertices{-0.8f, -0.8f, 0.0f, 0.8f, -0.8f, 0.0f, 0.0f, 0.8f, 0.0f};
    // Generates VAO
    // Sets up on the GPU
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generates VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
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

    VertexSpecification();

    // Creates shaders
    CreateGraphicsPipeline();

    // Continually draws over file
    MainLoop();

    // Ends running subsystems
    CleanUp();
}
