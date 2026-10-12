#include "darwin/Resources.h"
#include <random>
namespace darwin {
Resources::Resources(double w,int nw,int nf){std::mt19937 r(42);std::uniform_real_distribution<double>d(0,w);for(int i=0;i<nw;++i)water_.push_back({d(r),d(r)});for(int i=0;i<nf;++i)food_.push_back({{d(r),d(r)},8,0});}
bool Resources::nearWater(Position p,double rad,double w)const{for(auto q:water_)if(distance(p,q,w)<rad)return true;return false;}
FoodPatch* Resources::foodAt(Position p,double rad,double w){for(auto&f:food_)if(f.capacity>0&&distance(p,f.position,w)<rad)return &f;return nullptr;}
void Resources::regenerate(){for(auto&f:food_){if(f.capacity<=0&&++f.recovery>=40){f.capacity=8;f.recovery=0;}}}
}
