#ifndef SNAKEPLAYER_H_INCLUDED
#define SNAKEPLAYER_H_INCLUDED
#include<GameObject.h>
#include<Grid2D.h>
class SnakePlayer : public GameObject{
public:
    static SnakePlayer* instance();
    void update() override;
    void draw() override;
    void clean() override;

    void load(int x, int y);

    //function members
    Vector2D getPositionInGridPosition()const;
    void grow(int amount = 1);
    void restSnakeBodySize();
    bool doesOverlapSnakeBodyFromGridPosition(const Vector2D& v2);
    bool isDeath();
    void makeAlive();
private:
    Grid2D::GridPoint g_head_position;
    std::vector<Grid2D::GridPoint> g_body_positions;
    int g_width, g_height;
    Vector2D moveDir = Vector2D::right();
    int g_snake_move_speed = 1;
    int initSnakeSize = 15;
    int g_alpha = 255;
    bool g_die = false;
    //singleton
    SnakePlayer():g_head_position(TheGame::instance()->getGrid())
    {}
    static SnakePlayer* pInstance;
};

#endif // SNAKEPLAYER_H_INCLUDED
