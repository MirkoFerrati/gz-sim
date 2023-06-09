/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef GZ_GAZEBO_COMPONENTS_JOINTFORCECMD_HH_
#define GZ_GAZEBO_COMPONENTS_JOINTFORCECMD_HH_

#include <vector>

#include <gz/sim/components/Factory.hh>
#include <gz/sim/components/Component.hh>
#include <gz/sim/config.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
namespace components
{
  /// \brief Commanded joint forces (or torques) to be applied to a joint
  /// in SI units (Nm for revolute, N for prismatic). The component wraps a
  /// std::vector and systems that set this component need to ensure that the
  /// vector has the same size as the degrees of freedom of the joint.
  using JointForceCmd = Component<std::vector<double>, class JointForceCmdTag>;
  IGN_GAZEBO_REGISTER_COMPONENT("ign_gazebo_components.JointForceCmd",
                                JointForceCmd)
}
}
}
}

#endif
