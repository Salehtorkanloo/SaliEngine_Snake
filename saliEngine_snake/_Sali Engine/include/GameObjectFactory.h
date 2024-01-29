#ifndef GAMEOBJECTFACTORY_H_INCLUDED
#define GAMEOBJECTFACTORY_H_INCLUDED
#include<map>
#include<GameObject.h>
#include<iostream>

class BaseCreator{
public:
    virtual GameObject* createGameObject() = 0;
};
class GameObjectFactory{
public:
    static GameObjectFactory* instance(){
        if(pInstance == NULL){
            pInstance = new GameObjectFactory();
        }
        return pInstance;
    }

    bool registerType(std::string ID, BaseCreator* pCreator){
        //check for existence of the Creator
        std::map<std::string, BaseCreator*>::iterator it =
        g_creators.find(ID);

        if(it != g_creators.end()){
            //the creator does already exists
            delete pCreator;
            return false;
        }
        //the creator is new!
        g_creators[ID] = pCreator;

        return true;
    }
    GameObject* create(std::string ID){
        //check for existence of the creator
        std::map<std::string, BaseCreator*>::iterator it =
        g_creators.find(ID);

        if(it == g_creators.end()){
            std::cout << "GameObject creation failure - the creator " << ID << " doesn't exists in the map! \n";
            return NULL;
        }

        //the creator does exist in the map!
        //creates the gameObject and returns it...
        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }

    bool isRegistered(std::string id){
        std::map<std::string, BaseCreator*>::iterator it =
        g_creators.find(id);

        if(it != g_creators.end()){
            return true;
        }

        return false;
    }
private:
    //ensure that the object will only construct by the singleton
    GameObjectFactory() = default;
    static GameObjectFactory* pInstance;
    std::map<std::string, BaseCreator*> g_creators;
};



#endif // GAMEOBJECTFACTORY_H_INCLUDED
