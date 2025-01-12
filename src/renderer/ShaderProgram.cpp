#include "ShaderProgram.h"
namespace renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
        GLuint v_shader;
        if (!this->createShader(vertexShader, GL_VERTEX_SHADER, v_shader))
        {
            std::cerr << "VERTEX SHADER compile time error" << std::endl;
            return;
        }
        GLuint f_shader;
        if (!this->createShader(fragmentShader, GL_FRAGMENT_SHADER, f_shader))
        {
            std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
            glDeleteShader(v_shader);
            return;

        }
        this->m_programId = glCreateProgram();
        glAttachShader(this->m_programId, v_shader);
        glAttachShader(this->m_programId, f_shader);
        glLinkProgram(this->m_programId);
        
        GLint success;
        glGetProgramiv(this->m_programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(this->m_programId, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER PROGRAM: Link time error\n" << infoLog << std::endl;
            return;
        }
        else
        {
            m_isCompiled = true;
        }
        glDeleteShader(v_shader);
        glDeleteShader(f_shader);
	}
	ShaderProgram::~ShaderProgram()
	{
        glDeleteProgram(m_programId);
	}
    void ShaderProgram::use() const
	{
        glUseProgram(m_programId);
	}
    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_programId);
        m_programId = shaderProgram.m_programId;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_programId = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }
    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        m_programId = shaderProgram.m_programId;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_programId = 0;
        shaderProgram.m_isCompiled = false;
    }
    bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderId)
    {
        shaderId = glCreateShader(shaderType);
        const char* source_str = source.c_str();
        glShaderSource(shaderId, 1, &source_str, nullptr);
        glCompileShader(shaderId);

        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile time error\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }
}