#ifndef GAMESTATEMACHINE_H_INCLUDED
#define GAMESTATEMACHINE_H_INCLUDED
#include<vector>
#include<GameState.h>
enum game_states{/*it is also needed alter the createStateFromEnum Function*/
    Menu = 0,
    Play = 1,
    Pause = 2,
    GameOver = 3,
};
class GameStateMachine{
public:
    void changeState(game_states state);//removes one state and adds another
    void pushState(game_states state);//adds one state without removing the previous state
    void popState();//removes previous state without adding new state

    void update()const;
    void render()const;

    GameState* getCurrentState(){
        return g_gameStates.back();
    };
    std::vector<GameState*> getGameStates(){
        return g_gameStates;
    }
private:
    GameState* createStateFromEnum(game_states state);
    std::vector<GameState*> g_gameStates;
};


#endif // GAMESTATEMACHINE_H_INCLUDED
