#include "core/utils.h"

#include <sstream>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "catch2/catch.hpp"

namespace nicp {
namespace core {
namespace test {

template <typename T>
struct ApproxEigenMatrixMatcher : Catch::Matchers::Impl::MatcherBase<Eigen::MatrixBase<T>> {
  ApproxEigenMatrixMatcher(Eigen::MatrixBase<T> const& matrix_in) : matrix(matrix_in) {}

  bool match(Eigen::MatrixBase<T> const& other_matrix) const {
    // If the size of the two matrices mismatches return false.
    if (matrix.rows() != other_matrix.rows() || matrix.cols() != other_matrix.cols()) {
      return false;
    }

    // If one element of the two matrices mismatches return false.
    for (int r = 0; r < matrix.rows(); ++r) {
      for (int c = 0; c < matrix.cols(); ++c) {
        if (matrix(r, c) != approx(other_matrix(r, c))) {
          return false;
        }
      }
    }
    return true;
  }

  std::string describe() const override {
    std::ostringstream oss;
    oss << std::endl << "~=" << std::endl;
    for (int r = 0; r < matrix.rows(); ++r) {
      for (int c = 0; c < matrix.cols(); ++c) {
        oss << matrix(r, c) << " ";
      }
      oss << std::endl;
    }
    return oss.str();
  }

  ApproxEigenMatrixMatcher& epsilon(long double const& new_epsilon) {
    approx.epsilon(new_epsilon);
    return *this;
  }

  ApproxEigenMatrixMatcher& margin(long double const& new_margin) {
    approx.margin(new_margin);
    return *this;
  }

  ApproxEigenMatrixMatcher& scale(long double const& new_scale) {
    approx.scale(new_scale);
    return *this;
  }

  Eigen::MatrixBase<T> const& matrix;
  mutable Catch::Detail::Approx approx = Catch::Detail::Approx::custom();
};

template <typename T>
auto ApproxEigenMatrix(const Eigen::MatrixBase<T>& matrix) -> ApproxEigenMatrixMatcher<T> {
  return ApproxEigenMatrixMatcher<T>{matrix};
}

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
