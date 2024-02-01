#include<GameStateMachine.h>
#include<string>
void GameStateMachine::update() const{
    if(!g_gameStates.empty()){
        g_gameStates.back()->update();
    }
}
void GameStateMachine::render() const{
    if(!g_gameStates.empty()){
        g_gameStates.back()->render();
    }
}
void GameStateMachine::changeState(game_states state){
    GameState* pState = createStateFromEnum(state);
    //check there is no match checks for any existing state if any removes that
    if(!g_gameStates.empty()){
        if(g_gameStates.back()->getID() == pState->getID())
            return;//don't change the same states
        for(std::vector<GameState*>::size_type i = 0 ;i < g_gameStates.size() ; ++i){
            if(g_gameStates[i]->onExit()){
                delete g_gameStates[i];
            }
        }
    }
    std::cout << "the size: " << g_gameStates.size() << "\n";
    std::cout << "state: " << state << "\n";
    g_gameStates.clear();

    //adds the new state

    g_gameStates.push_back(pState);
    g_gameStates.back()->onEnter();

}
void GameStateMachine::pushState(game_states state){
    GameState* pState = createStateFromEnum(state);
    if(g_gameStates.back()->getID() == pState->getID())
        return;//don't repeat the state
    //adds the new state
    g_gameStates.push_back(pState);
    g_gameStates.back()->onEnter();

}
void GameStateMachine::popState(){
    if(g_gameStates.empty())
        return;//there is no existing state to remove
    //remove the current state
    delete g_gameStates.back();
    g_gameStates.pop_back();
}
GameState* GameStateMachine::createStateFromEnum(game_states state){
    switch(state){
    default:
    case Menu:
    case Play:
    case Pause:
    case GameOver:
        //add your states object here
    break;
    }
}
