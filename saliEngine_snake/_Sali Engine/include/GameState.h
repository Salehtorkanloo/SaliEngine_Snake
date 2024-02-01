#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include<iostream>
class GameState{
public:
    virtual ~GameState(){};
    virtual void update()const = 0;
    virtual void render()const = 0;

    virtual bool onEnter() = 0;
    virtual bool  onExit() = 0;

    virtual const std::string& getID() const = 0;
};


#endif // GAMESTATE_H_INCLUDED
