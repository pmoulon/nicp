#pragma once

#include <iostream>

#include "core/data_associator.h"
#include "core/types.h"
#include "registration3d/cloud3d.h"

namespace nicp {
namespace registration3d {

class DataAssociatorNNCloud3dCloud3dExtended : public core::DataAssociator<Cloud3d, Cloud3dExtended> {
 public:
  virtual core::Associations Compute(const Cloud3d& /*reference_measurements*/,
                                     const Cloud3dExtended& /*measurements*/) const override {
    std::cout << "Computing NN associations" << std::endl;
    return {};
  }
};

}  // namespace registration3d
}  // namespace nicp
