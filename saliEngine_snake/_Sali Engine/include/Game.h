#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include<iostream>
#include<SDL.h>
#include<GameObject.h>
#include<vector>
#include<GameObjectFactory.h>
class Grid2D;
class Game{
public:
    static Game* instance(){
        if(pInstance == NULL){
            pInstance = new Game();
        }
        return pInstance;
    }

    bool init(const char* title,int s_x, int s_y, int s_width, int s_height, bool fScreen);
    void update();
    void handleEvents();
    void render();
    void clean();

    void increaseScore();
    int getScore();

    int getScreenWidth(){return scr_width;}
    int getScreenHeight(){return scr_height;}

    GameObject* AddGameObject(std::string id);
    GameObject* AddGameObject(GameObject* GameObject);
    GameObject* RegisterAndAddGameObject(std::string id, BaseCreator* creator);
    bool isRegistered(std::string id);
    ///need to change functions

    Grid2D* getGrid()const;
    void putFoodInRandomPosition();

    ///
    const bool& isGameRunning()const;
    SDL_Renderer* getRenderer()const;
    SDL_Window* getWindow()const;
private:
    int g_score = 0;
    int scr_width;
    int scr_height;
    static Game* pInstance;
    bool g_beRunning;
    SDL_Window* g_pWindow;
    SDL_Renderer* g_pRenderer;

    Grid2D* g_grid;

    std::vector<GameObject*> g_gameObjects;
};
typedef Game TheGame;

#endif // GAME_H_INCLUDED
