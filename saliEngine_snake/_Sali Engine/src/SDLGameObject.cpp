#include<SDLGameObject.h>
#include<LoaderParameters.h>
#include<Game.h>
#include<TextureManager.h>
void SDLGameObject::load(const LoaderParameters* loaderParameters){
    g_position = Vector2D(loaderParameters->getX(), loaderParameters->getY());
    g_width = loaderParameters->getWidth();
    g_height = loaderParameters->getHeight();
    g_textureID = loaderParameters->getTextureID();
/*
    if(g_currentFrame == 0)
        g_currentFrame = 1;
    if(g_currentRow == 0)
        g_currentRow = 1;
*/
}
void SDLGameObject::draw(){
    //GameObject::draw();
    TheTexture::instance()->drawFrame(g_textureID, g_currentRow, g_currentFrame, int(g_position.getX()), int(g_position.getY()), g_width, g_height);

}
void SDLGameObject::update(){
    //GameObject::update();
    g_velocity += g_acceleration;
    g_position += g_velocity;
}
void SDLGameObject::clean(){
    //GameObject::clean();
    delete this;
}
void SDLGameObject::Move(Vector2D dir){
    g_position += dir;
}

