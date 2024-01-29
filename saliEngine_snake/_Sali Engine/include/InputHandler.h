#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED
#include<iostream>
#include<vector>
#include<Vector2D.h>
#include<SDL.h>
enum mouse_buttons{
    LeftClick   = 0,
    MiddleClick = 1,
    RightClick  = 2
};
enum key_buttons{
    RightArrow = SDL_SCANCODE_RIGHT,
    LeftArrow  = SDL_SCANCODE_LEFT,
    UpArrow    = SDL_SCANCODE_UP,
    DownArrow  = SDL_SCANCODE_DOWN,
    EnterKey   = SDL_SCANCODE_RETURN,
    EscKey     = SDL_SCANCODE_ESCAPE,
    SpaceKey   = SDL_SCANCODE_SPACE,
};
class InputHandler{
public:
    //singleton
    static InputHandler* instance(){
        if(pInstance == NULL){
            pInstance = new InputHandler();
        }
        return pInstance;
    }

   InputHandler(){
        g_mouseButtonStates.push_back(false);
        g_mouseButtonStates.push_back(false);
        g_mouseButtonStates.push_back(false);

    }

    //return type of reference to const ensures that data member won't be changed
    //by calling the function
   const Vector2D& getMousePosition(){
        return g_mousePosition;
    }

   //MOUSE EVENTS
   //returns true if the button is down
   bool isMouseButtonDown(mouse_buttons button);
   //sets the position of the mouse
   void OnMouseMotion(SDL_Event* event);
   //if the mouse buttons is released set the g_MouseButtonStates true
   void OnMouseDown(SDL_Event* event);
   //if the mouse buttons is released set the g_MouseButtonStates false
   void OnMouseUp(SDL_Event* event);

   //KEY EVENTS
   //if the key buttons is pressed returns true otherwise returns false
   bool isKeyDown(key_buttons key);
   bool isNonArrowKeyPressed();
   const Vector2D& getArrowAxis();
   const Vector2D& getArrowAxisNonDiagonal();

   void update();

private:
    std::vector<bool> g_mouseButtonStates;
    Vector2D g_arrow_axis = Vector2D();
    Vector2D g_arrow_axis_non_diagonal = Vector2D();
    Vector2D g_mousePosition = Vector2D(0,0);
    bool isMouseMotion = false;
    static InputHandler* pInstance;

};
typedef InputHandler TheInput;


#endif // INPUTHANDLER_H_INCLUDED
