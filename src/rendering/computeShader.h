#pragma once
#include<glad/glad.h>
#include <texture.h> 
#include <string>
#include <fstream>
#include <iostream>

class ComputeShader
{
private:
    unsigned int m_id;
    unsigned int m_glShaderId;
    Texture m_texture;
    std::string m_src;

public:
    ComputeShader(std::string src);
    void Update();
    Texture& GetTexture();
    void Use();
    void Unuse();

private:
    std::string GetShaderSource(std::string src);
    unsigned int CreateShader(const char* shaderSource);
};
