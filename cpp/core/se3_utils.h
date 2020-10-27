#pragma once

#include <assert.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "core/common_types.h"

namespace nicp {
namespace core {

Isometry3d VectorToTransform(const Vector6d& v) {
  Isometry3d T = Isometry3d::Identity();

  // Retrieve the quaternion's w component.
  const double qw_squared = v.tail<3>().squaredNorm();
  assert(qw_squared < 1.0 && "[Err] Encountered a non unit quaternion");
  const double qw = std::sqrt(1.0 - qw_squared);

  // Set the transform's rotational part.
  const Quaterniond q(qw, v[3], v[4], v[5]);
  T.linear() = q.toRotationMatrix();

  // Set the transform's translational part.
  T.translation() = v.head<3>();
  return T;
}

Vector6d TransformToVector(const Isometry3d& T) {
  Vector6d v;

  Quaterniond q(T.linear());
  v.tail<3>() = Vector3d(q.x(), q.y(), q.z());

  // Set the vector translational components.
  v.head<3>() = T.translation();

  return v;
}

}  // namespace core
}  // namespace nicp
