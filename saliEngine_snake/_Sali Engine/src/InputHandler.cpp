#include<InputHandler.h>
#include<SDL.h>
#include<Game.h>
#include<iostream>
#include<Vector2D.h>
InputHandler* InputHandler::pInstance = 0;
bool InputHandler::isKeyDown(key_buttons key){
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    if(keyStates != 0){//if any key is pressed
        if(keyStates[key] == 1){
            //the key is pressed
            return true;
        }
        else{
            //the key isn't pressed or the key is released before processing the event
            return false;
        }
    }
}
bool InputHandler::isNonArrowKeyPressed(){
    return (!isKeyDown(RightArrow) && !isKeyDown(LeftArrow) && !isKeyDown(UpArrow) && !isKeyDown(DownArrow)) == true;
}
const Vector2D& TheInput::getArrowAxis(){
    return g_arrow_axis;
}
const Vector2D& TheInput::getArrowAxisNonDiagonal(){
    return g_arrow_axis_non_diagonal;
}
bool InputHandler::isMouseButtonDown(mouse_buttons button){
   if(g_mouseButtonStates[button] == true){
      return true;
   }
   return false;
}
void InputHandler::OnMouseDown(SDL_Event* event){
   if(event->button.button == 1){
      g_mouseButtonStates[LeftClick] = true;
   }
   if(event->button.button == 2){
      g_mouseButtonStates[MiddleClick] = true;
   }
   if(event->button.button == 3){
      g_mouseButtonStates[RightClick] = true;
   }
}
void InputHandler::OnMouseUp(SDL_Event* event){
   if(event->button.button == 1){
      g_mouseButtonStates[LeftClick] = false;
   }
   if(event->button.button == 2){
      g_mouseButtonStates[MiddleClick] = false;
   }
   if(event->button.button == 3){
      g_mouseButtonStates[RightClick] = false;
   }
}
void InputHandler::OnMouseMotion(SDL_Event* event){
   g_mousePosition.setX(event->motion.x);
   g_mousePosition.setY(event->motion.y);
}

void InputHandler::update(){
   //set arrow axis
   int x = 0, y = 0;
   if(isKeyDown(RightArrow))
        x = 1;
   else if(!isKeyDown(LeftArrow))
        x = 0;
   if(isKeyDown(LeftArrow))
        x = -1;
   else if(!isKeyDown(RightArrow))
        x = 0;
   //vertical arrow
   if(isKeyDown(UpArrow))
        y = -1;
   else if(!isKeyDown(DownArrow))
        y = 0;
   if(isKeyDown(DownArrow))
        y = 1;
   else if(!isKeyDown(UpArrow))
        y = 0;
   g_arrow_axis = Vector2D(x,y);

   ///set the arrow axis keys for non diagonal
   int x_non_diagonal = 0, y_non_diagonal = 0;
   if(isKeyDown(RightArrow)){
        x_non_diagonal = 1;
        y_non_diagonal = 0;
    }
   else if(!isKeyDown(LeftArrow))
        x_non_diagonal = 0;
   if(isKeyDown(LeftArrow)){
        x_non_diagonal= -1;
        y_non_diagonal = 0;
    }
   else if(!isKeyDown(RightArrow))
        x_non_diagonal = 0;
   //vertical arrow
   if(isKeyDown(UpArrow)){
        y_non_diagonal = -1;
        x_non_diagonal = 0;
   }
   else if(!isKeyDown(DownArrow))
        y_non_diagonal = 0;
   if(isKeyDown(DownArrow)){
        y_non_diagonal= 1;
        x_non_diagonal = 0;
    }
   else if(!isKeyDown(UpArrow))
        y_non_diagonal = 0;
   g_arrow_axis_non_diagonal = Vector2D(x_non_diagonal,y_non_diagonal);

   //update keyboard input states
   SDL_Event event;
   if(SDL_PollEvent(&event)){
   //QUIT
   switch(event.type){
   case SDL_QUIT:
      TheGame::instance()->clean();
   break;
   case SDL_MOUSEMOTION:
      OnMouseMotion(&event);
   break;
   case SDL_MOUSEBUTTONDOWN:
      OnMouseDown(&event);
   break;

   case SDL_MOUSEBUTTONUP:
      OnMouseUp(&event);
   break;

   }

   }
}
