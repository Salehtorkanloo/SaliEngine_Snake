#include<Game.h>
const unsigned int FPS = 20;
const unsigned int DELAY_TIME_BETWEEN_FRAMES = 1000 / FPS;
int main(int argc, char** argv){
    int pos = SDL_WINDOWPOS_CENTERED;
    TheGame::instance()->init("saliEngine_snake", pos,pos, 600,650, false);

    while(TheGame::instance()->isGameRunning()){
        int timer = SDL_GetTicks();

        TheGame::instance()->update();
        TheGame::instance()->handleEvents();
        TheGame::instance()->render();
        int elapsedRunTime = SDL_GetTicks() - timer;
        if( elapsedRunTime < DELAY_TIME_BETWEEN_FRAMES){
            SDL_Delay(DELAY_TIME_BETWEEN_FRAMES - elapsedRunTime);
        }
    }

    //out of the game
    TheGame::instance()->clean();

    return 0;
}
