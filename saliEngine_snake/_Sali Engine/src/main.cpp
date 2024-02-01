#include<iostream>
#include<Game.h>

//======frame per second=======
const int FPS = 60;
const int DelayTime = 1000 / FPS;
void func(){
    std::cout << "Oh my god it worked!\n";
}

int main(int argc, char** argv){

    int pos = SDL_WINDOWPOS_CENTERED;
    if(!TheGame::instance()->init("sali", pos, pos, 500, 480, false))
        return -1;
    while(TheGame::instance()->isGameRunning()){
        int startTime = SDL_GetTicks();

        TheGame::instance()->update();
        TheGame::instance()->handleEvents();
        TheGame::instance()->render();

        int diffTime = SDL_GetTicks() - startTime;
        if(diffTime < DelayTime){
            SDL_Delay(DelayTime - diffTime);
        }
    }
    //end of the game;
    std::cerr << "end of the game\n";
    TheGame::instance()->clean();
    return 0;
}
