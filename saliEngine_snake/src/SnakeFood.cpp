#include<SnakeFood.h>
#include<Game.h>
#include<SnakePlayer.h>
SnakeFood* SnakeFood::pInstance = NULL;
SnakeFood* SnakeFood::instance(){
    if(pInstance == NULL){
        pInstance = new SnakeFood();
    }
    return pInstance;
}
int animTimer = 0;
int caputredSDLTime;
void SnakeFood::update(){
    if(SnakePlayer::instance()->isDeath())
        return;
    //food alpha animation
    if(SDL_GetTicks() > animTimer){
        animTimer = SDL_GetTicks() + animTime * 1000;
        caputredSDLTime = SDL_GetTicks();
    }
    else{
        float coefficient = (float)( SDL_GetTicks() - caputredSDLTime ) / (animTimer - caputredSDLTime);
        render_alpha = 255 * ( cos(6*coefficient)* 0.5f + 0.5f );
    }
}
void SnakeFood::draw(){
    SDL_Rect block;
    block.x = g_position.getXInWorldPosition();
    block.y = g_position.getYInWorldPosition();
    block.w = block.h = TheGame::instance()->getGrid()->getGridCellSize();
    if(!SnakePlayer::instance()->isDeath())
        SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(),194, 106, 74,render_alpha);
    else{
        SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(), 0,0,0, 255);

    }
    SDL_RenderFillRect(TheGame::instance()->getRenderer(), &block);
}
void SnakeFood::clean(){
    //clean
}

void SnakeFood::setFoodPositionFromGridPosition(const Vector2D& v2){
    g_position.setPositionFromGridPosition(v2);
}
Vector2D SnakeFood::getPositionInGridPosition(){
    return g_position.getPositionInGridPosition();
}

