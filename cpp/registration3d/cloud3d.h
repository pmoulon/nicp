#pragma once

#include <optional>
#include <vector>

#include "core/common_types.h"

namespace nicp {
namespace registration3d {

using Point3d = core::Vector3d;
using Normal3d = core::Vector3d;

struct Point3dExtended {
  Point3d point = core::Vector3d::Zero();
  std::optional<Normal3d> normal = std::nullopt;
  std::optional<double> intensity = std::nullopt;
  std::optional<core::Vector3d> rgb = std::nullopt;
};

using Cloud3d = std::vector<Point3d>;
using Cloud3dExtended = std::vector<Point3dExtended>;

}  // namespace registration3d
}  // namespace nicp
