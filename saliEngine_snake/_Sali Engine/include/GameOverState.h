#ifndef GAMEOVERSTATE_H_INCLUDED
#define GAMEOVERSTATE_H_INCLUDED
#include<GameState.h>
#include<SDLGameObject.h>
#include<vector>
class GameOverState : public GameState{
    void update()const override;
    void render()const override;

    bool onEnter() override;
    bool onExit() override;

    const std::string& getID() const override{return g_stateID;}
private:
    static void on_backToMain_clicked();
    static void on_restartPlay_clicked();
    std::vector<SDLGameObject*> g_gameObjects;
    static const std::string g_stateID;
};


#endif // GAMEOVERSTATE_H_INCLUDED
