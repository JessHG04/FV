#include "PoderTrueno.h"
using namespace std;


PoderTrueno::PoderTrueno(){
}

//actualiza al enemigo
void PoderTrueno::updateEne(){ 
    setTraEne(velEne);
    cajaColisionesNPC.setPosition(getPosicionEne().x - tamFrameNPC.x/2, getPosicionEne().y - tamFrameNPC.y/2);
}
