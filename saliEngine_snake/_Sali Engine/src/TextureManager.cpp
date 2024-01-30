#include<Game.h>
#include<TextureManager.h>
#include<SDL_image.h>
#include<iostream>
TextureManager* TheTexture::pInstance = 0;
TextureManager* TheTexture::instance(){
    if(pInstance == NULL){
        pInstance = new TextureManager;
    }
    return pInstance;
}
bool TheTexture::load(const std::string& fileName, const std::string& textureID){
    if(isLoaded(textureID) == true){
        std::cout << "SDL load file warning - the texture is already loaded\n";
        return true;
    }
    SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());

    if(tmpSurface == NULL){
        std::cout << "SDL load file failure - " << SDL_GetError() << "\n";
        return false;
    }
    //SDL load file success
    textures[textureID] = SDL_CreateTextureFromSurface(TheGame::instance()->getRenderer(), tmpSurface);

    SDL_FreeSurface(tmpSurface);
    return true;
}
bool TheTexture::isLoaded(const std::string& textureID){
    return textures[textureID] != nullptr;
}
void TheTexture::clearFromTextures(const std::string textureID){
    textures.erase(textureID);
}
void TheTexture::draw(const std::string& textureID, int x, int y, int w, int h, SDL_RendererFlip flip){
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;

    sourceRect.w = destinationRect.w = w;
    sourceRect.h = destinationRect.h = h;

    sourceRect.x = 0;
    sourceRect.y = 0;

    destinationRect.x = x;
    destinationRect.y = y;

    SDL_RenderCopyEx(TheGame::instance()->getRenderer(), textures[textureID], &sourceRect, &destinationRect, 0, 0, flip);
}
void TheTexture::drawFrame(const std::string& textureID, int currentRow, int currentFrame,int x, int y, int w, int h, SDL_RendererFlip flip){
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;


    //the frame starts at 1 and the first frame of the animate should multiply by zero;

    sourceRect.w = destinationRect.w = w;
    sourceRect.h = destinationRect.h = h;

    destinationRect.w /= 1.5f;
    destinationRect.h /= 1.5f;

    sourceRect.x = w * (currentFrame - 1);
    sourceRect.y = h * (currentRow - 1);

    destinationRect.x = x;
    destinationRect.y = y;

    SDL_RenderCopyEx(TheGame::instance()->getRenderer(), textures[textureID], &sourceRect, &destinationRect, 0, 0, flip);
}

