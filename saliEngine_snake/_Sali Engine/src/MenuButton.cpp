#include<MenuButton.h>
#include<Vector2D.h>
#include<Game.h>
#include<InputHandler.h>
void MenuButton::load(const LoaderParameters* loaderParameters){
    g_callbackID = loaderParameters->getCallBackID();
    SDLGameObject::load(loaderParameters);

}
void MenuButton::update(){
    //check for mouse over
    Vector2D mousePos = TheInput::instance()->getMousePosition();

    if(mousePos.getX() < g_position.getX() + g_width
    && mousePos.getX() > g_position.getX()
    && mousePos.getY() < g_position.getY() + g_height
    && mousePos.getY() > g_position.getY() )
    {
        g_currentFrame = Mouse_OVER;
        //check for click
        if(TheInput::instance()->isMouseButtonDown(LeftClick) && g_beReleased){
            g_currentFrame = CLICKED;
            g_beReleased = false;
            //callback:
            g_Callback();
        }

    }
    else{
        g_currentFrame = Mouse_OUT;
    }

    //check for released
    if( !(TheInput::instance()->isMouseButtonDown(LeftClick)) && !(g_beReleased)){
        g_beReleased = true;
    }
}
void MenuButton::draw(){
    SDLGameObject::draw();
}
void MenuButton::clean(){
    SDLGameObject::clean();
}
