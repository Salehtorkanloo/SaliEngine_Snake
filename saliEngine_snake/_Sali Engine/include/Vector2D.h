#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED
#include<math.h>
#include<ostream>
class Vector2D{
public:
    Vector2D(float x, float y): g_x(x), g_y(y){};
    Vector2D():g_x(0),g_y(0){};

    const float& getX()const {return g_x;}
    const float& getY()const {return g_y;}

    void setX(float x) {g_x = x;}
    void setY(float y) {g_y = y;}

    static const Vector2D one(){
        return Vector2D(1,1);
    }
    static const Vector2D zero(){
        return Vector2D(0,0);
    }
    static const Vector2D right(){
        return Vector2D(1,0);
    }
    static const Vector2D left(){
        return Vector2D(-1,0);
    }
    static const Vector2D up(){
        return Vector2D(0,-1);
    }
    static const Vector2D down(){
        return Vector2D(0,1);
    }
    //====operators======
    //addition
    Vector2D operator+(Vector2D v2)const{
        return Vector2D(g_x + v2.g_x, g_y + g_y + v2.g_y);
    }
    Vector2D& operator+=(const Vector2D& v2){
        g_x += v2.g_x;
        g_y += v2.g_y;

        return *this;
    }
    //minus
    Vector2D operator-(const Vector2D& v2)const{
        return Vector2D(g_x - v2.g_x, g_y - v2.g_y);
    }
    //unary minus
    Vector2D operator-(){
        Vector2D v2;
        v2.setX(-g_x);
        v2.setY(-g_y);
        return v2;
    }
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2){
        v1.g_x -= v2.g_x;
        v1.g_y -= v2.g_y;
        return v1;
    }
    //division
    Vector2D operator/(float scaler){
        return Vector2D(g_x / scaler, g_y / scaler);
    }
    friend Vector2D& operator/=(Vector2D& v1 ,float scaler){
        v1.g_x /= scaler;
        v1.g_y /= scaler;

        return v1;
    }
    //multiplication
    Vector2D operator*(float scaler)const{
        return Vector2D(g_x * scaler, g_y * scaler);
    }
    friend Vector2D& operator*=(Vector2D& v1, float scaler){
        v1.g_x *= scaler;
        v1.g_y *= scaler;

        return v1;
    }
    //ASSIGNMENT
    Vector2D& operator=(const Vector2D& v2){
        g_x = v2.g_x;
        g_y = v2.g_y;
        return *this;
    }
    //relational operators
    bool operator!=(const Vector2D& v2) const{
        return (g_x != v2.getX() || g_y != v2.getY());
    }
    bool operator ==(const Vector2D& v2) const{
        return (g_x == v2.getX()) && (g_y == v2.getY());
    }
    //OUTPUT
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v2){
        os << "(" << v2.g_x << ", " << v2.g_y << ")";
        return os;
    }
    float length(){
        return sqrt(g_x * g_x + g_y * g_y);
    }
    Vector2D& normalize(){
        float l = length();
        if(l != 1 && l != 0){//never attempt to divide by zero
            *this /= l;
        }
        return *this;
    }
private:
    float g_x;
    float g_y;
};


#endif // VECTOR2D_H_INCLUDED
