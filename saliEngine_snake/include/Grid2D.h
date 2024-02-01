
#ifndef GRID2D_H_INCLUDED
#define GRID2D_H_INCLUDED
#include<GameObject.h>
#include<Vector2D.h>
#include<Game.h>
#include<bits/stdc++.h>
/***
 *** Grid position explaining:
 *** each grid position unit includes a whole cellSize
 ***/
class Grid2D{
public:
    Grid2D(int grid_width, int grid_height, int cell_size, int grid_xPos, int grid_yPos, bool debug = true):
        g_grid_width(grid_width), g_grid_height(grid_height), g_cell_size(cell_size),
        g_grid_xPos(grid_xPos), g_grid_yPos(grid_yPos)
        {
            if(debug)
                TheGame::instance()->AddGameObject(new GridDebugGameObject(this));
        }


    // position getters from grid coordinates into world-converted coordinates
    Vector2D getWorldPositionFromGridPosition(int x, int y){
        return Vector2D( x * g_cell_size + g_grid_xPos, y * g_cell_size + g_grid_yPos);
    }
    Vector2D getWorldPositionFromGridPosition(Vector2D v2){
        return getWorldPositionFromGridPosition(v2.getX(), v2.getY());
    }

    // position getters from world coordinates into grid-converted coordinates
    Vector2D getGridPositionFromWorldPosition(int x, int y){
        return Vector2D( (x - g_grid_xPos) / g_cell_size , (y - g_grid_yPos) / g_cell_size );
    }
    Vector2D getGridPositionFromWorldPosition(Vector2D& v2){
        return getGridPositionFromWorldPosition(v2.getX(), v2.getY());
    }

    // border position getters
    int getGridRightBorderInGridPosition(){return (g_grid_width - 1);}
    int getGridLeftBorderInGridPosition(){return g_grid_xPos;}
    int getGridUpBorderInGridPosition(){return g_grid_yPos;}
    int getGridDownBorderInGridPosition(){return (g_grid_height - 1);}

    ///Access functions
    int getGridWidth(){return g_grid_width;}
    int getGridHeight(){return g_grid_height;}
    int getGridCellSize(){return g_cell_size;}
    int getGridXPosition(){return g_grid_xPos;}
    int getGridYPosition(){return g_grid_yPos;}

    /***
     *** Grid Point save the coordinate in grid position
     *** and can return position in world position for stuff like drawing
    ***/
    class GridPoint{
    public:
        //initialize the gird point
        GridPoint(Grid2D* grid):
        g_grid(grid),
        grid_cellSize(grid->getGridCellSize()),
        grid_startX(grid->getGridXPosition()),
        grid_startY(grid->getGridYPosition()){}
        GridPoint(Grid2D* grid, int x, int y) : GridPoint(grid){
            g_gridPoint.setX(x);
            g_gridPoint.setY(y);
        }

        void movePositionFromGridPosition(const Vector2D& v2){
            g_gridPoint += v2;
        }
        /// position setters that inputs are grid coordinate
        void setXFromGridPosition(int x){
            //set the coordinates in grid position
            g_gridPoint.setX(x);
        }
        void setYFromGridPosition(int y){
            //set the coordinates in grid position
            g_gridPoint.setY(y);
        }
        void setPositionFromGridPosition(int x, int y){
            setXFromGridPosition(x);
            setYFromGridPosition(y);
        }
        void setPositionFromGridPosition(const Vector2D& v2){
            setPositionFromGridPosition(v2.getX(), v2.getY());
        }
        /// position setters that inputs are world coordinate
        //takes coordinate in world position and saves them in grid position
        void setXFromWorldPosition(int x){
            x = (x - grid_startX) / grid_cellSize;
            setXFromGridPosition(x);
        }
        void setYFromWorldPosition(int y){
            y = (y - grid_startY) / grid_cellSize;
            setYFromGridPosition(y);
        }
        void setPositionFromWorldPosition(int x, int y){
            setXFromWorldPosition(x);
            setYFromWorldPosition(y);
        }
        void setPositionFromWorldPosition(Vector2D v2){
            setPositionFromWorldPosition(v2.getX(), v2.getY());
        }
        /// position getters that return saved grid coordinate
        int getXInGridPosition()const{
            return getPositionInGridPosition().getX();
        }
        int getYInGridPosition()const{
            return getPositionInGridPosition().getY();
        }
        /// position getters that return world-converted grid position
        int getXInWorldPosition()const{
            return getPositionInWorldPosition().getX();
        }
        int getYInWorldPosition()const{
            return getPositionInWorldPosition().getY();
        }
        Vector2D getPositionInWorldPosition()const{
            //get the coordinate in world position
            return g_grid->getWorldPositionFromGridPosition(g_gridPoint);
        }
        Vector2D getPositionInGridPosition()const{
            return g_gridPoint;
        }
        bool offTheGridPosition(){
            //check for x coordinate
            int gridEndX = (g_grid->getGridWidth() - 1) * grid_cellSize;
            int gridEndY = (g_grid->getGridHeight() - 1) * grid_cellSize;
            if(getXInWorldPosition() < grid_startX || getXInWorldPosition() > gridEndX)
                return true;
            //check for y coordinate
            if(getYInWorldPosition() < grid_startY || getYInWorldPosition() > gridEndY)
                return true;

            //neither x nor y goes off the screen
            return false;
        }
    private:
        Vector2D g_gridPoint;
        Grid2D* g_grid;
        int grid_cellSize;
        int grid_startY;
        int grid_startX;
    };


private:

    class GridDebugGameObject : public GameObject{
        ///debug initializer
        public:
        GridDebugGameObject(Grid2D* grid):grid(grid){}
        Grid2D* grid;

        //draw line positions
        Vector2D startPos;
        Vector2D endPos;
        ///override functions
        void update() override{

        }
        void draw() override{
            for(int y = 0; y < grid->getGridHeight(); ++y){
                for(int x =0 ; x < grid->getGridWidth(); ++x){
                    //set the lines color
                    SDL_SetRenderDrawColor(TheGame::instance()->getRenderer(), 255,255,255,255);

                    startPos = grid->getWorldPositionFromGridPosition(x,y);
                    //draw line horizontally
                    endPos = grid->getWorldPositionFromGridPosition(x+1,y);
                    SDL_RenderDrawLine
                    (TheGame::instance()->getRenderer(), startPos.getX(), startPos.getY(), endPos.getX(), endPos.getY());
                    //draw line vertically
                    endPos = grid->getWorldPositionFromGridPosition(x,y+1);
                    SDL_RenderDrawLine
                    (TheGame::instance()->getRenderer(), startPos.getX(), startPos.getY(), endPos.getX(), endPos.getY());
                }
            }
            endPos = grid->getWorldPositionFromGridPosition( grid->getGridWidth(), grid->getGridHeight());
            //draw end line vertically
            startPos = grid->getWorldPositionFromGridPosition( grid->getGridWidth(), 0);
            SDL_RenderDrawLine
            (TheGame::instance()->getRenderer(), startPos.getX(), startPos.getY(), endPos.getX(), endPos.getY());
            //draw end line horizontally
            startPos = grid->getWorldPositionFromGridPosition( 0, grid->getGridHeight());
            SDL_RenderDrawLine
            (TheGame::instance()->getRenderer(), startPos.getX(), startPos.getY(), endPos.getX(), endPos.getY());
        }
        void clean()override{
        }
    };
    int g_grid_width, g_grid_height;
    int g_cell_size;
    int g_grid_xPos , g_grid_yPos;
};
#endif // GRID2D_H_INCLUDED
