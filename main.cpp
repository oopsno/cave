#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>

#include "json.hpp"
#include "objects.hpp"

using json = nlohmann::json;

int main() {
  const std::string path = "D:\\COCO\\instances_val2014.json";
  json instances;
  auto t0 = std::chrono::high_resolution_clock::now();
  std::ifstream fs(path);
  instances << fs;
  auto t1 = std::chrono::high_resolution_clock::now();
  auto gt = std::make_unique<cave::GroundTruth>(instances);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double>(t1 - t0).count() << "s used to parse json" << std::endl;
  std::cout << std::chrono::duration<double>(t2 - t1).count() << "s used to build GT" << std::endl;
  std::cout << gt->annotations.size() << " annotations, " << gt->categories.size() << " categories parsed." << std::endl;
  return 0;
}
