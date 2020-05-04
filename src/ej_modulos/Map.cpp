#include "Map.h"

Map::Map(){
    widthMap = 0;
    heightMap = 0;
    numLayers = 0;
    widthTile = 0;
    heightTile = 0;
}

void Map::mapMatrix(int level){
 
    tinyxml2::XMLDocument doc;

    if(level == 1){
        doc.LoadFile("resources/Mapas/Mazmorra1.tmx");
    }else if(level == 2){
        doc.LoadFile("resources/Mapas/Boss1.tmx");
    }else if(level == 3){
        doc.LoadFile("resources/Mapas/Mazmorra2.tmx");
    }else if(level == 4){
        doc.LoadFile("resources/Mapas/Boss2.tmx");
    }else if(level == 5){
        doc.LoadFile("resources/Mapas/Mazmorra3.tmx");
    }else if(level == 6){
        doc.LoadFile("resources/Mapas/Boss3.tmx");
    }

    //Dimensiones del mapa y tiles
    tinyxml2::XMLElement *map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &widthMap);
    map->QueryIntAttribute("height", &heightMap);
    map->QueryIntAttribute("tilewidth", &widthTile);
    map->QueryIntAttribute("tileheight", &heightTile);

    //Carga de tileset y background
    tinyxml2::XMLElement *img = map->FirstChildElement("tileset")->FirstChildElement("image");
    const char *filename = img->Attribute("source");

    /*tinyxml2::XMLElement* imgBackground = map->FirstChildElement("imagelayer")->FirstChildElement("image");
    const char* filenameback=imgBackground->Attribute("source");*/

    //Numero de capas 
    tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
    while(layer){
        numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    //std::cout << "Numero de capas: " << numLayers << std::endl;

    //Reserva de memoria de los GIDs de las capas
    tilemap = new int **[numLayers];
    for(unsigned int l = 0; l < numLayers; l++){
        tilemap[l] = new int *[heightMap]; 
    }
    for(unsigned int l = 0; l < numLayers; l++){
        for(unsigned int y = 0; y < heightMap; y++){
            tilemap[l][y] = new int[widthMap];
        }
    }
    this->data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

    //Asignacion de cada gids a la matriz de 3x3 (layer-height-width)

    for(unsigned int l = 0; l < numLayers; l++){    
        if(l==1){
            this->data = map->FirstChildElement("layer")->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        }
        for(unsigned int y = 0; y < heightMap; y++) {
            for(unsigned int x = 0; x < widthMap; x++){
                data->QueryIntAttribute("gid", &tilemap[l][y][x]);
                //Pasamos al siguiente tile
                this->data = data->NextSiblingElement("tile");
            }
        }
        //this->data = data->PreviousSiblingElement("data")->PreviousSiblingElement("layer");
        //this->data = data->NextSiblingElement("layer");
    }


}

bool Map::load(const std::string& path, sf::Vector2u tileSize, int*** level, unsigned int witdh, unsigned int heigth, int numLayer){
        //std::cout << "Layers: " << numLayer << std::endl;
        //std::cout << "Height: " << heigth << std::endl;
        //std::cout << "Width: " << witdh << std::endl;
        int gid;
        int u;
        int v;
        if(!tile.loadFromFile(path)){
           return false;
        }
        vertex.setPrimitiveType(sf::Quads);
        vertex.resize(widthMap * heightMap * 4); //Se multiplica por 4 bc el tiled es de 16x16

        for(unsigned int l = 0; l < numLayers; l++){
            for(unsigned int y = 0; y < heightMap; y++){
                for(unsigned int x = 0; x < widthMap; x++){
                    gid = level[l][y][x];
                    if(gid > 0){
                        gid-=1;
                    }

                    if(gid!=0){
                        //Posicion del tileset para partirlo
                        u = gid % (tile.getSize().x / tileSize.x); 
                        v = gid / (tile.getSize().x / tileSize.x);
                        //Puntero para apuntar al quad actual
                        sf::Vertex *quad = &vertex[(x+y*widthMap)* 4]; 

                        //Definicion de las esquinas del quad
                        quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
                        quad[1].position = sf::Vector2f((x+1) * tileSize.x, y * tileSize.y);
                        quad[2].position = sf::Vector2f((x+1) * tileSize.x, (y+1) * tileSize.y);
                        quad[3].position = sf::Vector2f(x * tileSize.x, (y+1) * tileSize.y);

                        //Definicion de las texturas de las coordenadas
                        quad[0].texCoords = sf::Vector2f(u*tileSize.x, v*tileSize.y);
                        quad[1].texCoords = sf::Vector2f((u+1)*tileSize.x, v*tileSize.y);
                        quad[2].texCoords = sf::Vector2f((u+1)*tileSize.x, (v+1)*tileSize.y);
                        quad[3].texCoords = sf::Vector2f(u*tileSize.x,(v+1)*tileSize.y);
                    }
                }
            }
        }
    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    states.texture = &tile;
    target.draw(vertex,states);
}

Map::~Map(){
    vertex.clear();
    widthMap = 0;
    heightMap = 0;
    numLayers = 0;
    widthTile = 0;
    heightTile = 0;
    delete tilemap;
}