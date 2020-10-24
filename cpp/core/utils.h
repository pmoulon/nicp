#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "core/common_types.h"

namespace nicp {
namespace core {

template <typename R>
Isometry3<R> VectorToTransform(const Vector6<R>& v) {
  Isometry3<R> T = Isometry3<R>::Identity();

  // Retrieve the quaternion's w component.
  const double qw_squared = v.template tail<3>().squaredNorm();
  assert(qw_squared < 1.0 && "[Err] Encountered a non unit quaternion");
  const double qw = std::sqrt(1.0 - qw_squared);

  // Set the transform's rotational part.
  const Quaternion<R> q(qw, v[3], v[4], v[5]);
  T.template linear() = q.toRotationMatrix();

  // Set the transform's translational part.
  T.template translation() = v.template head<3>();
  return T;
}

template <typename R>
Vector6<R> TransformToVector(const Isometry3<R>& T) {
  Vector6<R> v;

  Quaternion<R> q(T.linear());
  v.template tail<3>() = Vector3<R>(q.x(), q.y(), q.z());

  // Set the vector translational components.
  v.template head<3>() = T.translation();

  return v;
}

}  // namespace core
}  // namespace nicp
