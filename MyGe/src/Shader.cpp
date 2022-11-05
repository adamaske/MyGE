#include "Shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Open files and check for errors
    vShaderFile.open(vertexPath);
    if (!vShaderFile)
        // mLogger->logText("ERROR SHADER FILE " + std::string(vertexPath) + " NOT SUCCESFULLY READ", LogType::REALERROR);
     //fShaderFile.open(fragmentPath);
     if (!fShaderFile) {
            // mLogger->logText("ERROR SHADER FILE " + std::string(fragmentPath) + " NOT SUCCESFULLY READ", LogType::REALERROR);
     }

    std::stringstream vShaderStream;
    std::stringstream fShaderStream;
    // Read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        //mLogger->logText("ERROR SHADER VERTEX " + std::string(vertexPath) +
         //   " COMPILATION_FAILED\n" + infoLog, LogType::REALERROR);
    }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
       // mLogger->logText("ERROR SHADER VERTEX " + std::string(fragmentPath) +
            //" COMPILATION_FAILED\n" + infoLog, LogType::REALERROR);
    }
    // Shader Program linking
    this->mProgram = glCreateProgram();
    glAttachShader(this->mProgram, vertex);
    glAttachShader(this->mProgram, fragment);
    glLinkProgram(this->mProgram);
    // Print linking errors if any
    glGetProgramiv(this->mProgram, GL_LINK_STATUS, &success);

    //making nice output name for printing:
    std::string shadername{ vertexPath };
    shadername.resize(shadername.size() - 5); //deleting ".vert"

    if (!success)
    {
        glGetProgramInfoLog(this->mProgram, 512, nullptr, infoLog);
       //mLogger->logText("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" +
            //shadername + "\n   " + infoLog, LogType::REALERROR);
    }
    else
    {
        //mLogger->logText("GLSL shader " + shadername + " was successfully compiled");
    }
    // Delete the shaders as they're linked into our program now and no longer needed
    // The shader program is now on the GPU and we reference it by using the mProgram variable
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(mProgram);
}

GLuint Shader::GetProgram() const
{
    return mProgram;
}


void Shader::SetUniformMatrix4fv(glm::mat4 matrix, std::string name) {
    //What matrix do we want to effect
    auto m = glGetUniformLocation(mProgram, name.c_str());
    //Sets the value from the matrix inserted
    glUniformMatrix4fv(m, 1, GL_FALSE, matrix.length);
}

void Shader::SetUniform3f(float v1, float v2, float v3, std::string name) {
    auto m = glGetUniformLocation(mProgram, name.c_str());
    glUniform3f(m, v1, v2, v3);
}

void Shader::SetUniformVec3(glm::vec3 v1, std::string name)
{
    auto m = glGetUniformLocation(mProgram, name.c_str());
    glUniform3f(m, v1.x, v1.x, v1.x);
}

void Shader::SetUniform1f(float v1, std::string name) {
    auto m = glGetUniformLocation(mProgram, name.c_str());
    glUniform1f(m, v1);
}
void Shader::SetUniform1i(int v1, std::string name) {
    auto m = glGetUniformLocation(mProgram, name.c_str());
    glUniform1i(m, v1);
}