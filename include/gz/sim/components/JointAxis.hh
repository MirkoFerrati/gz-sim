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
#ifndef GZ_GAZEBO_COMPONENTS_JOINTAXIS_HH_
#define GZ_GAZEBO_COMPONENTS_JOINTAXIS_HH_

#include <gz/msgs/axis.pb.h>
#include <sdf/JointAxis.hh>
#include <gz/sim/components/Factory.hh>
#include <gz/sim/components/Component.hh>
#include <gz/sim/components/Serialization.hh>
#include <gz/sim/config.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
namespace serializers
{
  using JointAxisSerializer =
      serializers::ComponentToMsgSerializer<sdf::JointAxis, msgs::Axis>;
}
namespace components
{
  /// \brief A component that contains the joint axis . This is a simple wrapper
  /// around sdf::JointAxis
  using JointAxis = Component<sdf::JointAxis, class JointAxisTag,
                              serializers::JointAxisSerializer>;
  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.JointAxis", JointAxis)

  /// \brief A component that contains the second joint axis for joints with two
  /// axes. This is a simple wrapper around sdf::JointAxis
  using JointAxis2 = Component<sdf::JointAxis, class JointAxis2Tag,
                               serializers::JointAxisSerializer>;
  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.JointAxis2", JointAxis2)
}
}
}
}

#endif
