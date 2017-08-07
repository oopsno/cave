#pragma once

#include <vector>
#include "json.hpp"

using json = nlohmann::json;

namespace cave {

struct RLE {
  RLE(const json &rle);
  explicit RLE();
};

struct Point {
  Point(float x = 0, float y = 0);
  float x = 0, y = 0;
};

struct Polygon {
  Polygon(const json &polygon);
  std::vector<Point> vertexs;
  float 
};

struct Box {
  Box(const json &array);
  float x, y, width, height;
};

struct Segmentation {
  Segmentation(const json &what);
  RLE rle;
  std::vector<Polygon> polygons;
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