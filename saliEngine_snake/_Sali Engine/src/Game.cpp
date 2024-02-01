#include<Game.h>
#include<iostream>
#include<SDL.h>
#include<TextureManager.h>
#include<InputHandler.h>
#include<GameObjectFactory.h>
#include<SnakePlayer.h>
#include<SnakeFood.h>
#include<cstdlib>
//=====static pointer to instance======
Game* Game::pInstance = NULL;
bool Game::init(const char* title ,int s_x, int s_y, int s_width, int s_height, bool fScreen){
    ///initialize rand
    srand(time(0));

    scr_width = s_width;
    scr_height = s_height;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cerr << "SDL initialization failure - " << SDL_GetError() << "\n";
        return false;
    }
    int flags = fScreen? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
    g_pWindow = SDL_CreateWindow(title,s_x, s_y, s_width, s_height,flags);
    if(g_pWindow == NULL){
        std::cerr << "SDL window creation failure - " << SDL_GetError() << "\n";
        return false;
    }
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    if(g_pRenderer == NULL){
        std::cerr << "SDL renderer creation failure - " << SDL_GetError() << "\n";
        return false;
    }
    std::cout << "SDl int success \n";

    //Creating the grid
    int cellSize = 7;
    bool gridDebug = false;
    g_grid =
    new Grid2D(s_width / cellSize, s_height / cellSize , cellSize, 0,0, gridDebug);

    if(g_grid == NULL){
        std::cout << "Grid creation failure - couldn't create the grid2D\n";
        return false;
    }
    std::cout << "grid creation success\n";

    ///Adding GameObjects
    //player
    SnakePlayer* player = dynamic_cast<SnakePlayer*>
    ( AddGameObject(SnakePlayer::instance()) );
    player->load(s_width/2, s_height/2);
    //food
    AddGameObject(SnakeFood::instance());
    putFoodInRandomPosition();
    g_beRunning = true;
    return true;

}
int restartTimer = 0;
void Game::update(){
    if(SnakePlayer::instance()->isDeath()){
        if(restartTimer == 0){
            restartTimer = SDL_GetTicks();
        }
        else if(SDL_GetTicks() - restartTimer > 3000){
            SnakePlayer::instance()->makeAlive();
            restartTimer = 0;
        }
        return;
    }
    //The Input Update
    TheInput::instance()->update();
    //The gameObjects update
    for(GameObject* gameObject : g_gameObjects){
        gameObject->update();
    }

    //update the window title
    std::string title = "saliEngine_snake, max score: " + std::to_string(g_score);
    SDL_SetWindowTitle(g_pWindow,  title.c_str());
}
void Game::handleEvents(){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            g_beRunning = false;
        }
    }
}
void Game::render(){

    if(!SnakePlayer::instance()->isDeath())
        SDL_SetRenderDrawColor(g_pRenderer, 0,0,0,0);
    else
        SDL_SetRenderDrawColor(g_pRenderer, 255,255,255,0);

    SDL_RenderClear(g_pRenderer);

    for(GameObject* gameObject : g_gameObjects){
        gameObject->draw();

    }
    //render all entities in black color

    SDL_SetRenderDrawBlendMode(g_pRenderer, SDL_BLENDMODE_BLEND);
    SDL_RenderPresent(g_pRenderer);
}
void Game::clean(){
    g_beRunning = false;
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
    SDL_Quit();
}

void Game::increaseScore(){
    g_score += 10;
}
int Game::getScore(){
    return g_score;
}
GameObject* Game::AddGameObject(std::string id){
    //the problem starts from here
    GameObject* gameObject =
    GameObjectFactory::instance()->create(id);;
    if(gameObject == NULL){
        std::cerr << "please register the gameObject first \n";
        return NULL;
    }
    g_gameObjects.push_back(gameObject);
    return gameObject;
}
GameObject* Game::AddGameObject(GameObject* gameObject){
    g_gameObjects.push_back(gameObject);
    return gameObject;
}
GameObject* Game::RegisterAndAddGameObject(std::string id, BaseCreator* creator){
    GameObjectFactory::instance()->registerType(id, creator);
    return AddGameObject(id);
}
bool Game::isRegistered(std::string id){
    return GameObjectFactory::instance()->isRegistered(id);
}
const bool& Game::isGameRunning()const{
    return g_beRunning;
}
SDL_Renderer* Game::getRenderer()const{
    if(g_pRenderer == NULL){
        std::cout << "The Renderer access error - The renderer has not been created or not assigned\n";
        return NULL;
    }
    return g_pRenderer;
}
SDL_Window* Game::getWindow()const{
    if(g_pWindow == NULL){
        std::cout << "The Window access error - The window has not been created or not assigned \n";
        return NULL;
    }
    return g_pWindow;
}
Grid2D* Game::getGrid()const{
    if(g_grid == NULL){
        std::cout << "The Grid access error - The grid has not been created or not assigned \n";
        return NULL;
    }
    return g_grid;
}
void Game::putFoodInRandomPosition(){

    //get a random position where the snake body isn't in it
    Vector2D randomCoordinate = SnakePlayer::instance()->getPositionInGridPosition();
    while(SnakePlayer::instance()->doesOverlapSnakeBodyFromGridPosition(randomCoordinate)){
        //generate random pos in grid postion
        randomCoordinate.setX( rand() % getGrid()->getGridWidth() );
        randomCoordinate.setY( rand() % getGrid()->getGridHeight() );
    }
    SnakeFood::instance()->setFoodPositionFromGridPosition(randomCoordinate);

}
