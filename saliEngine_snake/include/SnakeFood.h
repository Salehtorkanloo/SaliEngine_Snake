#ifndef SNAKEFOOD_H_INCLUDED
#define SNAKEFOOD_H_INCLUDED
#include<Grid2D.h>
class SnakeFood : public GameObject{
public:
    //singleton
    static SnakeFood* instance();

    ///inherited functions
    void update() override;
    void draw() override;
    void clean() override;

    ///function members
    void setFoodPositionFromGridPosition(const Vector2D& v2);
    Vector2D getPositionInGridPosition();

private:
    Grid2D::GridPoint g_position;
    int g_width, g_height;
    //singleton
    SnakeFood():g_position(Grid2D::GridPoint(TheGame::instance()->getGrid())){}
    static SnakeFood* pInstance;
    int render_alpha = 255;
    int animTime = 1;
};


#endif // SNAKEFOOD_H_INCLUDED
