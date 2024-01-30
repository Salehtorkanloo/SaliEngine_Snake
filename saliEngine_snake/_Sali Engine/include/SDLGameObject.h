#ifndef SDLGAMEOBJECT_H_INCLUDED
#define SDLGAMEOBJECT_H_INCLUDED
#include<Vector2D.h>
#include<LoaderParameters.h>
#include<GameObject.h>
class SDLGameObject : public GameObject{
public:
     virtual void draw() = 0;
     virtual void update() = 0;
     virtual void clean() = 0;

     virtual void load(const LoaderParameters* laoderParameters) = 0;

     virtual void Move(Vector2D dir);

    const Vector2D& getPosition()const {return g_position;}
    const int& getWidth() {return g_width;}
    const int& getHeight() {return g_height;}
protected:
    Vector2D g_position = Vector2D(0,0);
    Vector2D g_velocity = Vector2D(0,0);
    Vector2D g_acceleration = Vector2D(0,0);
    int g_width;
    int g_height;
    int g_currentFrame = 1;
    int g_currentRow = 1;
    std::string g_textureID;
};


#endif // SDLGAMEOBJECT_H_INCLUDED
