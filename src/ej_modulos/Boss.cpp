#include "Boss.h"
using namespace std;


Boss::Boss(){
}

//actualiza al enemigo
void Boss::updateBoss(){ 
    setTraBoss(velBoss);
    cajaColisionesBoss.setPosition(getPosicionBoss().x - tamFrameBoss.x/2, getPosicionBoss().y - tamFrameBoss.y/2);
}
