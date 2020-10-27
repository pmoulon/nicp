#include "core/utils.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "catch2/catch.hpp"

#include "core/test/eigen_matrix_test_helper.h"

namespace nicp {
namespace core {
namespace test {

TEST_CASE("VectorToTransform") {
  double constexpr kMargin = 1e-6;

  SECTION("Identity case") {
    const Vector6d v = Vector6d::Zero();
    const Isometry3d T = VectorToTransform(v);
    REQUIRE(T.matrix() == Isometry3d::Identity().matrix());
  }

  SECTION("Non identity case") {
    const Vector6d v = (Vector6d() << 1.0, 2.0, 3.0, 0.0, 0.0, 0.707107).finished();

    const Isometry3d T = VectorToTransform(v);

    Isometry3d expected_T = Isometry3d::Identity();
    expected_T.linear() = Eigen::AngleAxisd(M_PI * 0.5, Vector3d::UnitZ()).toRotationMatrix();
    expected_T.translation() = Vector3d(1.0, 2.0, 3.0);
    REQUIRE_THAT(T.matrix(), ApproxEigenMatrix(expected_T.matrix()).margin(kMargin));
  }
}

TEST_CASE("TransformToVector") {
  double constexpr kMargin = 1e-6;

  SECTION("Identity case") {
    const Isometry3d T = Isometry3d::Identity();
    const Vector6d v = TransformToVector(T);
    REQUIRE(v == Vector6d::Zero());
  }

  SECTION("Non identity case") {
    Isometry3d T = Isometry3d::Identity();
    T.linear() = Eigen::AngleAxisd(M_PI * 0.5, Vector3d::UnitZ()).toRotationMatrix();
    T.translation() = Vector3d(1.0, 2.0, 3.0);

    const Vector6d v = TransformToVector(T);
    const Vector6d expected_v = (Vector6d() << 1.0, 2.0, 3.0, 0.0, 0.0, 0.707107).finished();
    REQUIRE_THAT(v, ApproxEigenMatrix(expected_v).margin(kMargin));
  }
}

}  // namespace test
}  // namespace core
}  // namespace nicp
