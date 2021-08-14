#include "Step.h"

Step::Step(){

}

Step::Step(int _sequence, int _leg_id, int _x, int _y, int _z){
    setSequence(_sequence);
    setLegId(_leg_id);
    setX(_x);
    setY(_y);
    setZ(_z);
}

void Step::setSequence(int _sequence){
    this->sequence = _sequence;
}

int Step::getSequence(){
    return this->sequence;
}

void Step::setLegId(int _leg_id){
    this->leg_id = _leg_id;
}

int Step::getLegId(){
    return this->leg_id;
}

void Step::setX(int _x){
    this->x = _x;
}

int Step::getX(){
    return this->x;
}

void Step::setY(int _y){
    this->y = _y;
}

int Step::getY(){
    return this->y;
}

void Step::setZ(int _z){
    this->z = _z;
}

int Step::getZ(){
    return this->z;
}
