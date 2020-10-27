#pragma once

#include "core/types.h"

namespace nicp {
namespace core {

template <class ReferenceMeasurements, class Measurements>
class DataAssociator {
 public:
  virtual Associations Compute(const ReferenceMeasurements& reference_measurements,
                               const Measurements& measurements) const = 0;
};

}  // namespace core
}  // namespace nicp
