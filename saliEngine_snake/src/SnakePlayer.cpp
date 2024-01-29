#include<SnakePlayer.h>
#include<InputHandler.h>
#include<cmath>
#include<SnakeFood.h>
#include<Game.h>
void SnakePlayer::load(int x, int y){
    g_head_position.setXFromWorldPosition(x);
    g_head_position.setYFromWorldPosition(y);
    //set the g_width and g_height to grid cellSize
    g_width = g_height = TheGame::instance()->getGrid()->getGridCellSize();

    //set body to 4
    grow(initSnakeSize);

}
void SnakePlayer::update(){
    if(isDeath())
        return;
    //moving the snake body
    Vector2D prevPos  = g_head_position.getPositionInGridPosition();
    Vector2D prevPos2 = Vector2D();

    for(int i = 0 ; i < g_body_positions.size(); ++i){
        prevPos2 = g_body_positions[i].getPositionInGridPosition();
        g_body_positions[i].setPositionFromGridPosition(prevPos);
        prevPos = prevPos2;
    }
    //moving the snake head
    const Vector2D& arrowAxis = TheInput::instance()->getArrowAxisNonDiagonal();
    if(arrowAxis != Vector2D::zero())
        if(moveDir.getX() != -arrowAxis.getX() || moveDir.getY() != -arrowAxis.getY())
            moveDir = arrowAxis;

    g_head_position.movePositionFromGridPosition(moveDir * g_snake_move_speed);

    //rest position when the snake when goes off the screen
    if(g_head_position.offTheGridPosition()){
        Grid2D* grid = TheGame::instance()->getGrid();
        if(moveDir == Vector2D::right())
            g_head_position.setXFromGridPosition(grid->getGridLeftBorderInGridPosition());
        if(moveDir == Vector2D::left())
            g_head_position.setXFromGridPosition(grid->getGridRightBorderInGridPosition());
        if(moveDir == Vector2D::down())
            g_head_position.setYFromGridPosition(grid->getGridUpBorderInGridPosition());
        if(moveDir == Vector2D::up())
            g_head_position.setYFromGridPosition(grid->getGridDownBorderInGridPosition());
    }

    //check collision for snake food
    const int& xPos = g_head_position.getXInGridPosition();
    const int& yPos = g_head_position.getYInGridPosition();
    const Vector2D& foodPos = SnakeFood::instance()->getPositionInGridPosition();

    if(xPos == foodPos.getX() && yPos == foodPos.getY()){
        TheGame::instance()->putFoodInRandomPosition();
        grow();
        TheGame::instance()->increaseScore();
    }

    //check for snake die
    for(const Grid2D::GridPoint& point : g_body_positions){
        if(xPos == point.getXInGridPosition() && yPos == point.getYInGridPosition()){
            g_die= true;
        }
    }
}
void SnakePlayer::draw(){

    SDL_Rect block;
    block.w = g_width;
    block.h = g_height;
    //draw the snake body
    int index = 0;
    for(Grid2D::GridPoint& point : g_body_positions){

        float coefficient = ( ((float)index + 1) / g_body_positions.size() );
        g_alpha = 255 * ( cos(6*coefficient)* 0.5f + 0.5f );

        if(g_alpha < 20)
            g_alpha = 20;

        if(!isDeath())
            SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(), 150,75,0, g_alpha);
        else
            SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(), 0,0,0, 255);

        block.x = point.getXInWorldPosition();
        block.y = point.getYInWorldPosition();
        SDL_RenderFillRect(TheGame::instance()->getRenderer(), &block);
        ++index;
    }
    //draw the snake head
    block.x = g_head_position.getXInWorldPosition();
    block.y = g_head_position.getYInWorldPosition();
    if(!isDeath())
        SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(), 150,75,0,g_alpha);
    else
        SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(), 0,0,0,g_alpha);
    //SDL_RenderFillRect(TheGame::instance()->getRenderer(), &block);
}
void SnakePlayer::clean(){

}
SnakePlayer* SnakePlayer::pInstance = 0;
SnakePlayer* SnakePlayer::instance(){
    if(pInstance == NULL){
        pInstance = new SnakePlayer();
    }
    return pInstance;
}

Vector2D SnakePlayer::getPositionInGridPosition()const{
    return g_head_position.getPositionInGridPosition();
}

void SnakePlayer::grow(int amount){
    for(int i = amount; i > 0; --i)
        g_body_positions.push_back(Grid2D::GridPoint(TheGame::instance()->getGrid(), -1, -1));
}
void SnakePlayer::restSnakeBodySize(){
    g_body_positions.clear();
    grow(initSnakeSize);
}
bool SnakePlayer::doesOverlapSnakeBodyFromGridPosition(const Vector2D& v2){
    //checks for head overlapping with v2
    if(g_head_position.getPositionInGridPosition() == v2)
        return true;
    //checks for whole body
    for(Grid2D::GridPoint point : g_body_positions){
        if(v2 == point.getPositionInGridPosition())
            return true;
    }
    //doesn't overlap the snake body
    return false;
}
bool SnakePlayer::isDeath(){
    return g_die;
}
void SnakePlayer::makeAlive(){
    restSnakeBodySize();
    g_die = false;
    g_head_position.setXFromGridPosition( TheGame::instance()->getGrid()->getGridWidth() / 2);
    g_head_position.setYFromGridPosition( TheGame::instance()->getGrid()->getGridHeight() / 2);
    TheGame::instance()->putFoodInRandomPosition();
}
