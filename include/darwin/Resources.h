#pragma once
#include "darwin/Geometry.h"
#include <vector>
namespace darwin {
struct FoodPatch{Position position;int capacity{8};int recovery{0};};
class Resources{
public:
 Resources(double worldSize,int waterCount,int foodCount);
 const std::vector<Position>& water()const{return water_;}
 std::vector<FoodPatch>& food(){return food_;}
 bool nearWater(Position p,double radius,double world)const;
 FoodPatch* foodAt(Position p,double radius,double world);
 void regenerate();
private:std::vector<Position>water_;std::vector<FoodPatch>food_;
};
}
