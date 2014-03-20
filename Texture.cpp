#include "Texture.h"
#include "Image.h"
#include <GL/glu.h>

Texture &Texture::operator=(const Texture &tex)
{
    if (isHandle)
        textureManager.release(name);
    id = tex.id;
    name = tex.name;
    isHandle = true;
    textureManager.addRef(name);
    return *this;
}

Texture TextureManager::load(const Image &img, bool repeat)
{
    Texture tex;
    tex.name = img.getName();
    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, img.bpp, img.width, img.height,
                      img.bpp == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, img.pixels);
    textures[tex.name].set(tex, 0);
    return tex;
}
