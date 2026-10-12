#include "darwin/CsvExporter.h"
#include <filesystem>
#include <stdexcept>
namespace darwin {
CsvExporter::CsvExporter(const std::string& path) {
 const auto parent=std::filesystem::path(path).parent_path();
 if(!parent.empty()) std::filesystem::create_directories(parent);
 file_.open(path);
 if(!file_) throw std::runtime_error("Cannot open CSV output: "+path);
 file_<<"tick,herbivore_population,predator_population,herbivore_avg_attraction,herbivore_avg_vision,herbivore_avg_speed_trait,herbivore_avg_size,herbivore_avg_metabolism,predator_avg_attraction,predator_avg_vision,predator_avg_speed_trait,predator_avg_size,predator_avg_metabolism\n";
}
void CsvExporter::write(const Statistics& s) {
 file_<<s.tick<<','<<s.herbivores<<','<<s.predators<<','<<s.hAttraction<<','<<s.hVision<<','<<s.hSpeed<<','<<s.hSize<<','<<s.hMetabolism<<','<<s.pAttraction<<','<<s.pVision<<','<<s.pSpeed<<','<<s.pSize<<','<<s.pMetabolism<<'\n';
 file_.flush();
}
}