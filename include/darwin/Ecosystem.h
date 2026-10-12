#pragma once
#include "darwin/Herbivore.h"
#include "darwin/Predator.h"
#include "darwin/Resources.h"
#include "darwin/SimulationConfig.h"
#include "darwin/Statistics.h"
#include <memory>
#include <random>
#include <vector>
namespace darwin {
class Ecosystem{
public:explicit Ecosystem(SimulationConfig config);void tick();Statistics statistics()const;void run();
 const SimulationConfig& config()const{return config_;}
private:SimulationConfig config_;std::mt19937_64 rng_;Resources resources_;std::vector<std::unique_ptr<Herbivore>>herbivores_;std::vector<std::unique_ptr<Predator>>predators_;std::uint64_t tick_{0};
 void initialize();void reproduce();double random(double low,double high);int integer(int low,int high);char sex();
};
}
