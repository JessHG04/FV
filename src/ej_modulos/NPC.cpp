#include "NPC.h"
using namespace std;


NPC::NPC(){
}

//actualiza al enemigo
void NPC::updateEne(){ 
    setTraEne(velEne);
    cajaColisionesNPC.setPosition(getPosicionEne().x - tamFrameNPC.x/2, getPosicionEne().y - tamFrameNPC.y/2);
}
