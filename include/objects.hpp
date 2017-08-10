#pragma once

#include <vector>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;

namespace cave {

struct RLE {
  RLE(const json &rle);
  uint64_t height, width, m;
  std::unique_ptr<uint32_t> counts;
};

struct Mask {
  Mask(size_t height, size_t width);
  size_t height, width;
  std::unique_ptr<uint8_t> mask;
};

struct Point {
  Point(float x = 0, float y = 0);
  float x = 0, y = 0;
};

struct Polygon {
  Polygon(const json &polygon);
  std::vector<Point> vertexs;
  float x_min, x_max, y_min, y_max;
};

using Polygons = std::vector<Polygon>;

struct Box {
  Box(const json &array);
  float x, y, width, height;
};

struct Segmentation {
  Segmentation(const json &what);
  std::unique_ptr<RLE> rle;
  std::unique_ptr<Polygons> polygons;
};

struct Annotation {
  Annotation(const json &annotation);
  int id, image_id, category_id, iscrowd;
  float area;
  Box bbox;
  Segmentation segmentation;
};

struct Category {
  Category(const json &category);
  int id;
  std::string name, supercategory;
};

struct GroundTruth {
  GroundTruth(const json &ground_truth);
  std::vector<Annotation> annotations;
  std::vector<Category> categories;
};

}
