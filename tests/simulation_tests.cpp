#include "darwin/Ecosystem.h"
#include "darwin/Geometry.h"
#include <cassert>
#include <cmath>
int main(){using namespace darwin;assert(std::abs(distance({1,5},{99,5},100)-2.0)<1e-9);auto p=wrap({-1,101},100);assert(p.x>=0&&p.x<100&&p.y>=0&&p.y<100);SimulationConfig c;c.ticks=3;c.initialHerbivores=4;c.initialPredators=1;c.foodCount=2;c.waterCount=2;Ecosystem a(c),b(c);for(int i=0;i<3;++i){a.tick();b.tick();}auto x=a.statistics(),y=b.statistics();assert(x.tick==y.tick&&x.herbivores==y.herbivores&&x.predators==y.predators);return 0;}
