/*
 * Copyright (C) 2018 Open Source Robotics Foundation
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
#ifndef GZ_GAZEBO_COMPONENTS_POSE_HH_
#define GZ_GAZEBO_COMPONENTS_POSE_HH_

#include <gz/math/Pose3.hh>
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
  /// \brief A component type that contains pose, gz::math::Pose3d,
  /// information.
  using Pose = Component<gz::math::Pose3d, class PoseTag>;
  IGN_GAZEBO_REGISTER_COMPONENT("ign_gazebo_components.Pose", Pose)

  /// \brief A component type that contains pose, gz::math::Pose3d,
  /// information in world frame.
  using WorldPose = Component<gz::math::Pose3d, class WorldPoseTag>;
  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.WorldPose", WorldPose)

  /// \brief A component type that contains pose, ignition::math::Pose3d,
  /// information within a trajectory.
  using TrajectoryPose =
      Component<gz::math::Pose3d, class TrajectoryPoseTag>;
  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.TrajectoryPose", TrajectoryPose)
}
}
}
}

#endif
