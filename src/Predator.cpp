#include "darwin/Predator.h"
namespace darwin {
void Predator::act(double w,std::mt19937&r){hunger-=0.12+traits.metabolism*0.02;thirst-=0.12+traits.metabolism*0.015;randomMove(w,r);}
}
