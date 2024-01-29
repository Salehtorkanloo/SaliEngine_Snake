#ifndef ANIMATEDGRAPHIC_H_INCLUDED
#define ANIMATEDGRAPHIC_H_INCLUDED
#include<SDLGameObject.h>
#include<GameObjectFactory.h>
class AnimatedGraphic : public SDLGameObject{
public:
    AnimatedGraphic() = default;
    void load(const LoaderParameters* loaderParameters)override;
    void update() override;
    void draw() override;
    void clean() override;

private:
    float g_speed;
    int g_numFrames;
};
class AnimatedGraphicCreator : public BaseCreator{
    AnimatedGraphic* createGameObject(){
        return new AnimatedGraphic();
    }
};

#endif // ANIMATEDGRAPHIC_H_INCLUDED
