#include "core/solver.h"
#include "registration3d/cloud3d.h"
#include "registration3d/data_associator_nn_cloud3d_cloud3d_extended.h"
#include "registration3d/linearizer_point3d_se3.h"

using ochre::core::DataAssociator;
using ochre::core::Linearizer;
using ochre::registration3d::Cloud3d;
using ochre::registration3d::Cloud3dExtended;
using ochre::registration3d::DataAssociatorNNCloud3dCloud3dExtended;
using ochre::registration3d::LinearizerPoint3dSE3;

int main() {
  std::unique_ptr<DataAssociatorNNCloud3dCloud3dExtended> data_associator_nn =
      std::make_unique<DataAssociatorNNCloud3dCloud3dExtended>();
  std::unique_ptr<LinearizerPoint3dSE3> linearizer_point3d_se3 = std::make_unique<LinearizerPoint3dSE3>();
  const ochre::core::Solver<Cloud3d, Cloud3dExtended, 3, 6> icp_solver();
  DataAssociator<Cloud3d, Cloud3dExtended>* data_associator =
      dynamic_cast<DataAssociator<Cloud3d, Cloud3dExtended>*>(data_associator_nn.get());
  Linearizer<3, 6>* linearizer = dynamic_cast<Linearizer<3, 6>*>(linearizer_point3d_se3.get());
  data_associator->Compute({}, {});
  linearizer->Linearize({}, nullptr, nullptr);
  return 0;
}
