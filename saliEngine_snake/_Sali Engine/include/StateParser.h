#ifndef STATEPARSER_H_INCLUDED
#define STATEPARSER_H_INCLUDED
#include<tinyxml.h>
#include<string>
#include<vector>
#include<SDLGameObject.h>
class StateParser{
public:
    void parseState(const std::string& fileName, const std::string& stateID , std::vector<std::string> *pTextureIDs_list,std::vector<SDLGameObject*> *gameObjects_list);
private:
    void parseObj(TiXmlElement* pElement, std::vector<SDLGameObject*>* pGameObjects_list);
    void parseTextures(TiXmlElement* pElement, std::vector<std::string> *pTextures_list);

};


#endif // STATEPARSER_H_INCLUDED
