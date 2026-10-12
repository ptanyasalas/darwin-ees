#include "darwin/Entity.h"
#include <algorithm>
namespace darwin {
Entity::Entity(Position p,int a,char s,Traits t,double e,int m):position(p),age(a),sex(s),traits(t),hunger(e),thirst(e),maxAge(m){}
void Entity::ageOne(){++age;if(actionCooldown>0)--actionCooldown;if(fertilityCooldown>0)--fertilityCooldown;}
bool Entity::alive()const{return hunger>0&&thirst>0&&age<=maxAge;}
void Entity::randomMove(double w,std::mt19937&r){std::uniform_real_distribution<double>d(0,6.283185307179586);double a=d(r);position=wrap({position.x+std::cos(a)*speed(),position.y+std::sin(a)*speed()},w);}
int mutateTrait(double v,int lo,int hi,std::mt19937&r){std::bernoulli_distribution change(.25);std::uniform_int_distribution<int>step(0,1);int n=static_cast<int>(v);if(change(r))n+=step(r)?1:-1;return std::clamp(n,lo,hi);}
Traits inheritTraits(const Traits&a,const Traits&b,int ls,int hs,int lv,int hv,std::mt19937&r){auto avg=[](int x,int y){return (x+y)/2.0;};return {mutateTrait(avg(a.attraction,b.attraction),1,10,r),mutateTrait(avg(a.vision,b.vision),lv,hv),mutateTrait(avg(a.speed,b.speed),1,5,r),mutateTrait(avg(a.size,b.size),ls,hs,r),mutateTrait(avg(a.metabolism,b.metabolism),1,5,r)};}
}
