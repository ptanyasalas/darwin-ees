#pragma once
#include "darwin/Entity.h"
namespace darwin {
class Herbivore final:public Entity{
public: Herbivore(Position p,int age,char sex,Traits t,double energy,int maxAge=110):Entity(p,age,sex,t,energy,maxAge){}
 bool isPredator()const override{return false;}
 void act(double worldSize,std::mt19937&rng)override;
};
}
