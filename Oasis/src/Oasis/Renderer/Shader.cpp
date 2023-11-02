#include <Oasis/Renderer/Shader.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

namespace Oasis {
    
    // TODO: Set failed flag

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        char log[512];
        std::string vertexSourceObject = GetShaderSource(vertexPath);
        std::string fragmentSourceObject = GetShaderSource(fragmentPath);
        const char* vertexSource = vertexSourceObject.c_str();
        const char* fragmentSource = fragmentSourceObject.c_str();

        uint32_t vertex, fragment;
        int success;

        vertex = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, log);
            std::cout << "Vertex shader compilation failed\n" << log << std::endl;
        };

        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment, 1, &fragmentSource, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, log);
            std::cout << "Fragment shader compilation failed\n" << log << std::endl;
        };

        m_RendererId = glCreateProgram();
        glAttachShader(m_RendererId, vertex);
        glAttachShader(m_RendererId, fragment);
        glLinkProgram(m_RendererId);

        glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(m_RendererId, 512, NULL, log);
            std::cout << "Link error\n" << log << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererId);
    }

    std::string Shader::GetShaderSource(const std::string& fileName)
    {
        std::ifstream file(fileName);
        std::stringstream stream;

        stream << file.rdbuf();
        
        file.close();

        return stream.str();
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererId);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    template <>
    void Shader::SetUniform<int>(const std::string& name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    template <>
    void Shader::SetUniform<float>(const std::string& name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    template <>
    void Shader::SetUniform<glm::vec2>(const std::string& name, glm::vec2 value)
    {
        glUniform2f(GetUniformLocation(name), value.x, value.y);
    }

    template <>
    void Shader::SetUniform<glm::vec3>(const std::string& name, glm::vec3 value)
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    template <>
    void Shader::SetUniform<glm::vec4>(const std::string& name, glm::vec4 value)
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    template <>
    void Shader::SetUniform<glm::mat4>(const std::string& name, glm::mat4 value)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    uint32_t Shader::GetUniformLocation(const std::string& name)
    {
        int location = glGetUniformLocation(m_RendererId, name.c_str());
        // if (location == -1)
        //     std::cout << "Warning: uniform '" << name << "'" << " does not exist\n";

        return location;
    }

}
