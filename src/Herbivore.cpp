#include "darwin/Herbivore.h"
#include <algorithm>
namespace darwin {
void Herbivore::act(double w,std::mt19937&r){hunger-=0.18+traits.metabolism*0.025;thirst-=0.20+traits.metabolism*0.02;randomMove(w,r);}
}
