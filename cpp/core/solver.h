#pragma once

#include <assert.h>
#include <memory>

#include <Eigen/Geometry>

#include "core/cloud.h"
#include "core/common_types.h"
#include "core/data_associator.h"
#include "core/linearizer.h"

namespace nicp {
namespace core {

template <int Z, int S>
class Solver {
 public:
  struct Result {
    Isometry3d T = Isometry3d::Identity();
  };

  Solver() {
    assert(Z > 0 && "[Err] Solver's measurement dimension must be positive");
    assert(S > 0 && "[Err] Solver's state dimension must be positive");
  }

  Result Solve(const Cloud& reference_cloud, const Cloud& cloud) const { return Result(); }

 private:
  std::unique_ptr<DataAssociator> data_associator_;
  std::unique_ptr<Linearizer<Z, S>> linearizer_;
};

}  // namespace core
}  // namespace nicp
