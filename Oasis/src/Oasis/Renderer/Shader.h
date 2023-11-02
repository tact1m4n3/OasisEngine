#pragma once

#include <string>

#include <Oasis/Resources/Resource.h>

namespace Oasis {

    class Shader : public Resource
    {
    private:
        uint32_t m_RendererId;
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        std::string GetShaderSource(const std::string& fileName);
        void Bind() const;
        void Unbind() const;

        template <class T>
        void SetUniform(const std::string& name, T value);
    private:
        uint32_t GetUniformLocation(const std::string& name);
    };
    
}