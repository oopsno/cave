#include <algorithm>

#include "objects.hpp"

namespace cave {

Box::Box(const json &array) {
  assert(array.is_array() and array.size() == 4);
  x = array[0];
  y = array[1];
  width = array[2];
  height = array[3];
}

RLE::RLE(const json &rle) {}

RLE::RLE() {}

Point::Point(float x, float y) : x{x}, y{y} {}

Polygon::Polygon(const json &polygon) {
  assert(polygon.is_array() and polygon.size() % 2 == 0);
  x_min = y_min = std::numeric_limits<float>::min();
  x_max = y_max = std::numeric_limits<float>::max();
  for (auto i = 0; i < polygon.size(); i += 2) {
    vertexs.emplace_back(polygon[i], polygon[i + 1]);
    x_min = std::min(x_min, polygon[i].get<float>());
    x_max = std::max(x_max, polygon[i].get<float>());
    y_min = std::min(y_min, polygon[i + 1].get<float>());
    y_max = std::max(y_max, polygon[i + 1].get<float>());
  }
}

Segmentation::Segmentation(const json &what) {
  if (what.is_object()) { // RLE
  } else if (what.is_array()) { // Polgons
    for (const auto &poly : what) {
      polygons.emplace_back(poly);
    }
  }
}

Annotation::Annotation(const json &annotation) :
    segmentation{annotation["segmentation"]},
    bbox{annotation["bbox"]} {
  assert(annotation.is_object());
#define assign(what) what = annotation[#what]
  assign(id);
  assign(image_id);
  assign(category_id);
  assign(area);
  assign(iscrowd);
#undef assign
}

Category::Category(const json &category) {
  assert(category.is_object());
#define assign(what) what = category[#what]
  assign(id);
  assign(name);
  assign(supercategory);
#undef assign
}

GroundTruth::GroundTruth(const json &ground_truth) {
  for (const auto &annotation : ground_truth["annotations"]) {
    annotations.emplace_back(annotation);
  }
  for (const auto &category : ground_truth["categories"]) {
    categories.emplace_back(category);
  }
}

}
