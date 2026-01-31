#include <computeShader.h>

ComputeShader::ComputeShader(std::string src) :
   m_src(src) 
{
    m_id = glCreateProgram();
}


void ComputeShader::Use()
{
    glUseProgram(m_id);
}

void ComputeShader::Unuse()
{
    glUseProgram(0);
}

std::string ComputeShader::GetShaderSource(std::string src)
{
    std::ifstream file(src.c_str());
    std::string str;
    std::string fileContent;

    while(std::getline(file, str))
    {
        fileContent += str;
        fileContent += 'n';
    }
    return fileContent;
}

unsigned int ComputeShader::CreateShader(const char* shaderSource)
{
    unsigned int shaderId = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);
    int compileStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
    
    if(compileStatus == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderId, length, &length, message);
        std::cout << "EORROR WHILE COMPILING COMPUTE SHADER" << " : "  << message << std::endl;
    }

    return shaderId;
}