#pragma once

#include <optional>
#include <vector>

#include "core/common_types.h"

namespace nicp {
namespace core {

template <typename R>
struct Measurement {
  Vector3<R> point = Vector3<R>::Zero();
  std::optional<Vector3<R>> normal = std::nullopt;
  std::optional<R> intensity = std::nullopt;
  std::optional<Vector3<R>> rgb = std::nullopt;
};

template <typename R>
using Cloud = std::vector<Measurement<R>>;

}  // namespace core
}  // namespace nicp
