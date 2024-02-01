#ifndef MENUBUTTON_H_INCLUDED
#define MENUBUTTON_H_INCLUDED
#include<SDLGameObject.h>
#include<GameObjectFactory.h>
enum button_state{
    Mouse_OUT = 1,
    Mouse_OVER = 2,
    CLICKED = 3
};
class MenuButton: public SDLGameObject{
public:
    void load(const LoaderParameters* loaderParameters)override;
    void update()override;
    void draw()override;
    void clean()override;

    void setCallback( void(*Callback)()){g_Callback = Callback;}
    unsigned getCallbackID(){return g_callbackID;}

private:
    void(*g_Callback)();
    bool g_beReleased = true;
    unsigned g_callbackID;
};
class MenuButtonCreator : public BaseCreator{
    MenuButton* createGameObject(){
        return new MenuButton();
    }
};


#endif // MENUBUTTON_H_INCLUDED
