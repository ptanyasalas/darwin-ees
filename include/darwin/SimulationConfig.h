#pragma once
#include <cstdint>
#include <string>
namespace darwin {
struct SimulationConfig{double worldSize{100};int waterCount{15},foodCount{35},initialHerbivores{50},initialPredators{8};std::uint64_t ticks{10000},seed{42};std::uint64_t statsInterval{20};std::string outputPath{"ecosystem_stats.csv"};};
}
