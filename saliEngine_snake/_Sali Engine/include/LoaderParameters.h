#ifndef LOADERPARAMETERS_H_INCLUDED
#define LOADERPARAMETERS_H_INCLUDED
#include<iostream>

class LoaderParameters{
public:
    LoaderParameters(int x, int y, int width, int height, std::string textureID, float speed = 0, int numFrames = 0, int callbackID = 0):
    g_x(x), g_y(y), g_width(width), g_height(height), g_textureID(textureID), g_callbackID(callbackID) , g_speed(speed), g_numFrames(numFrames)
    {

    }
    int getX()const{return g_x;}
    int getY()const{return g_y;}
    int getWidth()const{return g_width;}
    int getHeight()const{return g_height;}
    int getCallBackID()const {return g_callbackID;}
    std::string getTextureID()const{return g_textureID;}

private:
    int g_x;
    int g_y;
    int g_width;
    int g_height;
    int g_numFrames;
    float g_speed;
    int g_callbackID;
    std::string g_textureID;
};


#endif // LOADERPARAMETERS_H_INCLUDED
