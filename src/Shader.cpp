#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // -----------------------read shaders from disk----------------------------


    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    std::string vertexShaderBuffer;
     std::string fragmentShaderBuffer;

    // Ensure the file stream objects can throw errors.
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        // Read data from files.
        vertexShaderBuffer = std::string((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
        fragmentShaderBuffer = std::string((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    // Get shader source code as char arrays.
    const char *vertexShaderSource = vertexShaderBuffer.c_str();
    const char *fragmentShaderSource = fragmentShaderBuffer.c_str();



    // -------------------------------- Create and compile shaders and the shader program--------------------------

    // These are used for checking compilation errors.
    int success;
    char infoLog[512];

    // init vertex shader object.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // compile the shader.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compilation errors.
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        // TODO: Exit the program.
    }

    // set upt fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for compilation errors.
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) 
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        // TODO: Exit the program.
    }

    // Create shader program
    ID = glCreateProgram();

    // Link the shader together using the shader program.
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for compilation errors.
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {   
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        // TODO: Exit the program.
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(ID);
}

void Shader::deactivate()
{
    glUseProgram(0);
}

void Shader::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name), (int) value);
}

void Shader::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setMat4f(const char* name, glm::mat4 &trans) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(trans));
};

void Shader::setVec4f(const char* name, glm::vec4 &vec) const
{
    glUniform4f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z, vec.w);
};

void Shader::setVec3f(const char* name, glm::vec3 &vec) const
{
    glUniform3f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z);
};