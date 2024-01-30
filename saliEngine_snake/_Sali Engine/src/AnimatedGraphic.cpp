#include<AnimatedGraphic.h>
#include<SDL.h>
void AnimatedGraphic::load(const LoaderParameters* loaderParameters){
    SDLGameObject::load(loaderParameters);
}
void AnimatedGraphic::update(){
    g_currentFrame = (int)(SDL_GetTicks() / (1000.0f / g_speed)) % g_numFrames;
    SDLGameObject::update();
}
void AnimatedGraphic::draw(){
    SDLGameObject::draw();
}
void AnimatedGraphic::clean(){
    SDLGameObject::clean();
}
