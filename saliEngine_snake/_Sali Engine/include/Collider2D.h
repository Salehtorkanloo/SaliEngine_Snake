#ifndef COLLIDER2D_H_INCLUDED
#define COLLIDER2D_H_INCLUDED
class Collider2D{
public:
    Collider2D(const int& width, const int& height,const float& xPos,const float& yPos):g_width(width), g_height(height), object_x(xPos), object_y(yPos){}

    bool checkCollide(const Collider2D* collider){
        if(object_x + g_width >= collider->getX() &&
           object_x <= collider->getX() + collider->getWidth()&&
           object_y + g_height >= collider->getY() &&
           object_y <= collider->getY() + collider->getHeight())
        {
            return true;
        }

        return false;
    }

    const float& getX()const{return object_x;}
    const float& getY()const{return object_y;}

    const int& getWidth()const{return g_width;}
    const int& getHeight()const{return g_height;}
private:
    const int& g_width;
    const int& g_height;
    const float& object_x;
    const float& object_y;
};


#endif // COLLIDER2D_H_INCLUDED
