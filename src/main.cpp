#include "darwin/Ecosystem.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
namespace {
void help(){std::cout<<"Darwin EES Phase 1\nOptions: --world-size N --water N --food N --herbivores N --predators N --ticks N --seed N --stats-interval N --output PATH --help\n";}
}
int main(int argc,char**argv){try{darwin::SimulationConfig c;for(int i=1;i<argc;++i){std::string a=argv[i];if(a=="--help"){help();return 0;}if(i+1>=argc)throw std::invalid_argument("Missing value for "+a);std::string v=argv[++i];if(a=="--world-size")c.worldSize=std::stod(v);else if(a=="--water")c.waterCount=std::stoi(v);else if(a=="--food")c.foodCount=std::stoi(v);else if(a=="--herbivores")c.initialHerbivores=std::stoi(v);else if(a=="--predators")c.initialPredators=std::stoi(v);else if(a=="--ticks")c.ticks=std::stoull(v);else if(a=="--seed")c.seed=std::stoull(v);else if(a=="--stats-interval")c.statsInterval=std::stoull(v);else if(a=="--output")c.outputPath=v;else throw std::invalid_argument("Unknown option: "+a);}darwin::Ecosystem world(c);world.run();return 0;}catch(const std::exception&e){std::cerr<<"Error: "<<e.what()<<"\n";return 1;}}
