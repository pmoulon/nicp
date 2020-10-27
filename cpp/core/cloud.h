#pragma once

#include <optional>
#include <vector>

#include "core/common_types.h"

namespace nicp {
namespace core {

struct Measurement {
  Vector3d point = Vector3d::Zero();
  std::optional<Vector3d> normal = std::nullopt;
  std::optional<double> intensity = std::nullopt;
  std::optional<Vector3d> rgb = std::nullopt;
};

using Cloud = std::vector<Measurement>;

}  // namespace core
}  // namespace nicp
