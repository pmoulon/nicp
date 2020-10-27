#pragma once

#include <iostream>

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "core/linearizer.h"
#include "core/types.h"

namespace nicp {
namespace registration3d {

class LinearizerPoint3dSE3 : public core::Linearizer<3, 6> {
 public:
  virtual void Linearize(const core::Associations& /*associations*/, MatrixHd* /*H*/, Vectorbd* /*b*/) const override {
    std::cout << "Linearizing point SE3" << std::endl;
  }
};

}  // namespace registration3d
}  // namespace nicp
