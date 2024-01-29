#include<StateParser.h>
#include<SDLGameObject.h>
#include<TextureManager.h>
#include<GameObjectFactory.h>
void StateParser::parseState(const std::string& fileName, const std::string& stateID, std::vector<std::string> *pTextureIDs_list ,std::vector<SDLGameObject*>* pGameObjects_list){
    //create the xml document
    TiXmlDocument docu = TiXmlDocument();

    if(!docu.LoadFile(fileName.c_str())){
        std::cout << "XML Load failure - " << docu.ErrorDesc() << "\n";
        return;
    }

    //get the root(only top level) element
    TiXmlElement* pRootElement = docu.RootElement();

    //pre declare the state root node
    TiXmlElement* pStateRoot = 0;
    for(TiXmlElement* e = pRootElement->FirstChildElement(); e != NULL ;
    e = pRootElement->NextSiblingElement())
    {
        if(e->Value() == stateID){
            pStateRoot = e;
            break;
        }
    }
    //now the root state node is ready!

    //pre declare the texture root node
    TiXmlElement* pTextureElement = 0;
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL ;
    e = e->NextSiblingElement())
    {
        //texture
        if(e->Value() == std::string("TEXTURES")){
            pTextureElement = e;
            break;
        }
    }
    parseTextures(pTextureElement, pTextureIDs_list);

    //pre declare the gameObjects root node
    TiXmlElement* pGameObjectsElement = 0;
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
    e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("OBJECTS")){
            pGameObjectsElement = e;
            break;
        }
    }
    parseObj(pGameObjectsElement, pGameObjects_list);
}
void StateParser::parseObj(TiXmlElement* pElement, std::vector<SDLGameObject*>* gameObjects_list){
    for(TiXmlElement* e = pElement->FirstChildElement() ; e != NULL;
    e = pElement->NextSiblingElement())
    {
        //pre declare object's values
        int x = 0, y = 0, width = 0, height = 0, numFrames = 0
        , animSpeed = 0, callBackID = 0;
        std::string textuerID;
        //get the attributes
        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbackID", &callBackID);
        e->Attribute("animSpeed",&animSpeed);

        textuerID = e->Attribute("textureID");

        //create gameObjects
        SDLGameObject* gameObject = dynamic_cast<SDLGameObject*>
        ( GameObjectFactory::instance()->create(e->Attribute("type")) );
        gameObject->load(new LoaderParameters(x,y,width,height, textuerID, callBackID, animSpeed, numFrames ));
        gameObjects_list->push_back(gameObject);
        break;
    }
}
void StateParser::parseTextures(TiXmlElement* pElement, std::vector<std::string> *textures_list){
    for(TiXmlElement* e = pElement->FirstChildElement(); e != NULL; e = pElement->NextSiblingElement())
    {

        std::string fileName  = e->Attribute("filename");
        std::string textureID = e->Attribute("ID");

        //add the textureID to the list
        textures_list->push_back(textureID);
        //load the texture
        TheTexture::instance()->load(fileName, textureID);
        break;

    }
}
