#include <texture.h>

Texture::Texture() :
    m_width(6), m_height(10)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    glTexParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTextureStorage2D(m_id, 1, GL_RGBA32F, m_width, m_height); orignal im tutorial, aber funktioniert nicht
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, m_width, m_height);  //weicht vom Tutorial ab
    glBindImageTexture(0, m_id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
}