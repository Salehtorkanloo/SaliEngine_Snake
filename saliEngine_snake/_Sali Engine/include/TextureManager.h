#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include<map>
#include<SDL.h>
class TextureManager{
public:
    static TextureManager* instance();

    bool load(const std::string& filName, const std::string& textureID);
    bool isLoaded(const std::string& textureID);
    void clearFromTextures(const std::string textureID);
    void draw(const std::string& textureID, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(const std::string & textureID, int currentRow, int currentFrame, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    TextureManager() = default;
    static TextureManager* pInstance;
    std::map<const std::string, SDL_Texture*> textures;
};
typedef TextureManager TheTexture;

#endif // TEXTUREMANAGER_H_INCLUDED
