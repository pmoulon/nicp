#pragma once

#include <Eigen/Core>

#include "core/types.h"

namespace nicp {
namespace core {

template <int Z, int S>
class Linearizer {
 public:
  using Vectorbd = Eigen::Matrix<double, Z, 1>;
  using MatrixHd = Eigen::Matrix<double, Z, S>;

  virtual void Linearize(const Associations& associations, MatrixHd* H, Vectorbd* b) const = 0;
};

}  // namespace core
}  // namespace nicp
