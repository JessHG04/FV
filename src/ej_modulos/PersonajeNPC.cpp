#include "PersonajeNPC.h"

PersonajeNPC::PersonajeNPC(int cantidadX1E, int cantidadY1E , sf::Vector2i frm_actE){
    archivoEne = "resources/Sprites/NPC/NPCMago.png";
    cambiarSpriteNPC(txNPC,cantidadX1E, cantidadY1E, frm_actE);
    velDesplazamientoEne = 2.0f;
}