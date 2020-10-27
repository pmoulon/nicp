#pragma once

#include "core/cloud.h"
#include "core/types.h"

namespace nicp {
namespace core {

class DataAssociator {
 public:
  virtual Associations Compute(const Cloud& reference_cloud, const Cloud& cloud) const = 0;
};

}  // namespace core
}  // namespace nicp
