#include "darwin/Ecosystem.h"
#include "darwin/CsvExporter.h"
#include "darwin/Geometry.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
namespace darwin {
Ecosystem::Ecosystem(SimulationConfig c):config_(std::move(c)),rng_(config_.seed),resources_(config_.worldSize,config_.waterCount,config_.foodCount){if(config_.worldSize<=0||config_.statsInterval==0)throw std::invalid_argument("World size and stats interval must be positive");initialize();}
double Ecosystem::random(double a,double b){return std::uniform_real_distribution<double>(a,b)(rng_);}
int Ecosystem::integer(int a,int b){return std::uniform_int_distribution<int>(a,b)(rng_);}
char Ecosystem::sex(){return integer(0,1)==0?'F':'M';}
void Ecosystem::initialize(){for(int i=0;i<config_.initialHerbivores;++i){int size=integer(1,5);double energy=100+size*40;Traits t{integer(1,10),integer(1,3),integer(1,3),size,integer(1,5)};herbivores_.push_back(std::make_unique<Herbivore>(Position{random(0,config_.worldSize),random(0,config_.worldSize)},integer(0,20),sex(),t,energy,integer(90,130)));}for(int i=0;i<config_.initialPredators;++i){int size=integer(3,5);double energy=200+size*30;Traits t{integer(1,10),integer(2,4),integer(2,4),size,integer(2,4)};predators_.push_back(std::make_unique<Predator>(Position{random(0,config_.worldSize),random(0,config_.worldSize)},integer(0,10),sex(),t,energy,integer(70,100)));}}
void Ecosystem::tick(){
 ++tick_;
 for(auto&h:herbivores_)h->ageOne();for(auto&p:predators_)p->ageOne();
 for(auto&p:predators_){p->thirst-=0.12+p->traits.metabolism*.015;p->hunger-=0.10+p->traits.metabolism*.018;if(p->actionCooldown>0){--p->actionCooldown;continue;}
  Herbivore* target=nullptr;double best=1e100;
  for(auto&h:herbivores_){double d=distance(p->position,h->position,config_.worldSize);if(d<p->traits.vision*15.0&&d<best){best=d;target=h.get();}}
  if(target&&best<2.5){double hunt=std::clamp(.45+.08*(p->traits.speed-target->traits.speed)+.04*(p->traits.vision-target->traits.vision),.10,.90);if(random(0,1)<hunt){p->hunger+=150+target->traits.size*20;target->hunger=-1;}else{double dx=wrappedDelta(p->position.x,target->position.x,config_.worldSize),dy=wrappedDelta(p->position.y,target->position.y,config_.worldSize),d=std::hypot(dx,dy);if(d>0)p->position=wrap({p->position.x-dx/d*target->speed(),p->position.y-dy/d*target->speed()},config_.worldSize);}}
  else if(target){double dx=wrappedDelta(p->position.x,target->position.x,config_.worldSize),dy=wrappedDelta(p->position.y,target->position.y,config_.worldSize),d=std::hypot(dx,dy);if(d>0)p->position=wrap({p->position.x+dx/d*p->speed(),p->position.y+dy/d*p->speed()},config_.worldSize);}
  else if(resources_.nearWater(p->position,2.5,config_.worldSize))p->thirst=std::min(p->thirst,200.0);else p->act(config_.worldSize,rng_);
  p->hunger=std::min(p->hunger,350.0);p->thirst=std::min(p->thirst,350.0);p->actionCooldown=std::max(1,5-p->traits.speed);
 }
 herbivores_.erase(std::remove_if(herbivores_.begin(),herbivores_.end(),[](auto&h){return !h->alive();}),herbivores_.end());
 for(auto&h:herbivores_){if(h->actionCooldown>0){--h->actionCooldown;continue;}if(resources_.nearWater(h->position,2.0,config_.worldSize))h->thirst=std::min(300.0,h->thirst+35+h->traits.size*8);else if(auto*f=resources_.foodAt(h->position,2.0,config_.worldSize)){h->hunger=std::min(300.0,h->hunger+30+h->traits.size*10);if(--f->capacity<=0)f->recovery=0;}else h->act(config_.worldSize,rng_);h->actionCooldown=std::max(1,4-h->traits.speed);}
 herbivores_.erase(std::remove_if(herbivores_.begin(),herbivores_.end(),[](auto&h){return !h->alive();}),herbivores_.end());
 predators_.erase(std::remove_if(predators_.begin(),predators_.end(),[](auto&p){return !p->alive();}),predators_.end());
 resources_.regenerate();if(tick_%10==0)reproduce();
}
void Ecosystem::reproduce(){
 auto hLimit=std::max(10,config_.foodCount*4);if(static_cast<int>(herbivores_.size())<hLimit){for(auto&f:herbivores_){if(static_cast<int>(herbivores_.size())>=hLimit)break;if(f->sex!='F'||f->age<13||f->hunger<80||f->thirst<80||f->fertilityCooldown>0)continue;for(auto&m:herbivores_){if(m->sex!='M'||m->age<13||m->fertilityCooldown>0||m->hunger<80||m->thirst<80||distance(f->position,m->position,config_.worldSize)>4)continue;if(random(0,1)>.25)continue;Traits t=inheritTraits(f->traits,m->traits,1,5,1,5,rng_);double e=100+t.size*20;herbivores_.push_back(std::make_unique<Herbivore>(f->position,0,sex(),t,e,integer(90,130)));f->hunger-=15;m->hunger-=15;f->fertilityCooldown=40;m->fertilityCooldown=40;break;}}}
 auto pLimit=std::max(1,static_cast<int>(herbivores_.size()/8));if(static_cast<int>(predators_.size())<pLimit){for(auto&f:predators_){if(static_cast<int>(predators_.size())>=pLimit)break;if(f->sex!='F'||f->age<16||f->hunger<130||f->thirst<80||f->fertilityCooldown>0)continue;for(auto&m:predators_){if(m->sex!='M'||m->age<16||m->fertilityCooldown>0||m->hunger<130||m->thirst<80||distance(f->position,m->position,config_.worldSize)>5)continue;if(random(0,1)>.2)continue;Traits t=inheritTraits(f->traits,m->traits,3,5,2,5,rng_);predators_.push_back(std::make_unique<Predator>(f->position,0,sex(),t,220,integer(70,100)));f->hunger-=40;m->hunger-=40;f->fertilityCooldown=50;m->fertilityCooldown=50;break;}}}
}
Statistics Ecosystem::statistics()const{Statistics s;s.tick=tick_;s.herbivores=herbivores_.size();s.predators=predators_.size();auto add=[](auto&v,double&at,double&vi,double&sp,double&sz,double&me){for(auto&e:v){at+=e->traits.attraction;vi+=e->traits.vision;sp+=e->traits.speed;sz+=e->traits.size;me+=e->traits.metabolism;}if(!v.empty()){double n=static_cast<double>(v.size());at/=n;vi/=n;sp/=n;sz/=n;me/=n;}};add(herbivores_,s.hAttraction,s.hVision,s.hSpeed,s.hSize,s.hMetabolism);add(predators_,s.pAttraction,s.pVision,s.pSpeed,s.pSize,s.pMetabolism);return s;}
void Ecosystem::run(){CsvExporter csv(config_.outputPath);csv.write(statistics());for(;tick_<config_.ticks&&(!herbivores_.empty()||!predators_.empty());){tick();if(tick_%config_.statsInterval==0)csv.write(statistics());}if(tick_%config_.statsInterval!=0)csv.write(statistics());auto s=statistics();std::cout<<"Finished at tick "<<s.tick<<". Herbivores: "<<s.herbivores<<", predators: "<<s.predators<<"\nCSV: "<<config_.outputPath<<"\n";}
}
