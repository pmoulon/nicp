#include <sstream>

#include <Eigen/Core>

#include "catch2/catch.hpp"

namespace ochre {
namespace core {
namespace test {

namespace detail {

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

}  // namespace detail

template <typename T>
auto ApproxEigenMatrix(const Eigen::MatrixBase<T>& matrix) -> detail::ApproxEigenMatrixMatcher<T> {
  return detail::ApproxEigenMatrixMatcher<T>{matrix};
}

}  // namespace test
}  // namespace core
}  // namespace ochre
