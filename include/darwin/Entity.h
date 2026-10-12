#pragma once
#include "darwin/Geometry.h"
#include <random>
namespace darwin {
struct Traits { int attraction{5}; int vision{2}; int speed{2}; int size{2}; int metabolism{2}; };
class Entity {
public:
 Entity(Position p,int age,char sex,Traits t,double energy,int maxAge);
 virtual ~Entity()=default;
 virtual bool isPredator() const=0;
 virtual void act(double worldSize,std::mt19937& rng)=0;
 void ageOne(); bool alive() const;
 Position position; int age; char sex; Traits traits; double hunger, thirst; int maxAge, actionCooldown{0}, fertilityCooldown{0};
 double speed() const { return traits.speed*(isPredator()?0.6:0.5); }
protected:
 void randomMove(double worldSize,std::mt19937& rng);
};
int mutateTrait(double value,int low,int high,std::mt19937& rng);
Traits inheritTraits(const Traits&a,const Traits&b,int lowSize,int highSize,int lowVision,int highVision,std::mt19937&rng);
}
