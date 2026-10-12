#pragma once
#include "darwin/Statistics.h"
#include <fstream>
#include <string>
namespace darwin {
class CsvExporter { public: explicit CsvExporter(const std::string& path); void write(const Statistics& stats); private: std::ofstream file_; };
}
