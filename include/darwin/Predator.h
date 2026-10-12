#pragma once
#include "darwin/Entity.h"
namespace darwin {
class Predator final:public Entity{
public: Predator(Position p,int age,char sex,Traits t,double energy,int maxAge=90):Entity(p,age,sex,t,energy,maxAge){}
 bool isPredator()const override{return true;}
 void act(double worldSize,std::mt19937&rng)override;
};
}
