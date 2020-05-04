#include "PersonajeBoss.h"

PersonajeBoss::PersonajeBoss(int cantidadX1B, int cantidadY1B , sf::Vector2i frm_actB){
    archivoBoss = "resources/Sprites/NPC/NPCMago.png";
    cambiarSpriteBoss(txBoss,cantidadX1B, cantidadY1B, frm_actB);
    velDesplazamientoBoss = 2.0f;
}
