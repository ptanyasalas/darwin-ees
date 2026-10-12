#pragma once
#include <cstddef>
#include <cstdint>
namespace darwin {
struct Statistics {
 std::uint64_t tick{0};
 std::size_t herbivores{0}, predators{0};
 double hAttraction{0}, hVision{0}, hSpeed{0}, hSize{0}, hMetabolism{0};
 double pAttraction{0}, pVision{0}, pSpeed{0}, pSize{0}, pMetabolism{0};
};
}
