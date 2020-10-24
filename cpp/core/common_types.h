#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace nicp {
namespace core {

// Common vector types.
template <typename T>
using Vector3 = Eigen::Matrix<T, 3, 1>;

template <typename T>
using Vector4 = Eigen::Matrix<T, 4, 1>;

template <typename T>
using Vector6 = Eigen::Matrix<T, 6, 1>;

// Common matrix types.
template <typename T>
using Matrix3 = Eigen::Matrix<T, 3, 3>;

template <typename T>
using Matrix4 = Eigen::Matrix<T, 4, 4>;

template <typename T>
using Matrix6 = Eigen::Matrix<T, 6, 6>;

// Common quaternion types.
template <typename R>
using Quaternion = Eigen::Quaternion<R>;

// Common isometry types.
template <typename R>
using Isometry3 = Eigen::Transform<R, 3, 1>;

}  // namespace core
}  // namespace nicp
