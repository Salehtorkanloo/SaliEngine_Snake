#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
class GameObject{
public:
    GameObject() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;
};


#endif // GAMEOBJECT_H_INCLUDED
