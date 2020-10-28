#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace ochre {
namespace core {

// Common vector types.
using Vector3d = Eigen::Vector3d;
using Vector4d = Eigen::Vector4d;
using Vector6d = Eigen::Matrix<double, 6, 1>;

// Common matrix types.
using Matrix3d = Eigen::Matrix3d;
using Matrix4d = Eigen::Matrix4d;
using Matrix6d = Eigen::Matrix<double, 6, 6>;

// Common quaternion types.
using Quaterniond = Eigen::Quaterniond;

// Common isometry types.
using Isometry3d = Eigen::Isometry3d;

}  // namespace core
}  // namespace ochre
