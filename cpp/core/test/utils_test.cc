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
    const Vector6<double> v = Vector6<double>::Zero();
    const Isometry3<double> T = VectorToTransform(v);
    REQUIRE(T.matrix() == Isometry3<double>::Identity().matrix());
  }

  SECTION("Non identity case") {
    const Vector6<double> v = (Vector6<double>() << 1.0, 2.0, 3.0, 0.0, 0.0, 0.707107).finished();

    const Isometry3<double> T = VectorToTransform(v);

    Isometry3<double> expected_T = Isometry3<double>::Identity();
    expected_T.linear() = Eigen::AngleAxisd(M_PI * 0.5, Vector3<double>::UnitZ()).toRotationMatrix();
    expected_T.translation() = Vector3<double>(1.0, 2.0, 3.0);
    REQUIRE_THAT(T.matrix(), ApproxEigenMatrix(expected_T.matrix()).margin(kMargin));
  }
}

TEST_CASE("TransformToVector") {
  double constexpr kMargin = 1e-6;

  SECTION("Identity case") {
    const Isometry3<double> T = Isometry3<double>::Identity();
    const Vector6<double> v = TransformToVector(T);
    REQUIRE(v == Vector6<double>::Zero());
  }

  SECTION("Non identity case") {
    Isometry3<double> T = Isometry3<double>::Identity();
    T.linear() = Eigen::AngleAxisd(M_PI * 0.5, Vector3<double>::UnitZ()).toRotationMatrix();
    T.translation() = Vector3<double>(1.0, 2.0, 3.0);

    const Vector6<double> v = TransformToVector(T);
    const Vector6<double> expected_v = (Vector6<double>() << 1.0, 2.0, 3.0, 0.0, 0.0, 0.707107).finished();
    REQUIRE_THAT(v, ApproxEigenMatrix(expected_v).margin(kMargin));
  }
}

}  // namespace test
}  // namespace core
}  // namespace nicp
