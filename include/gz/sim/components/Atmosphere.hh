/*
 * Copyright (C) 2020 Open Source Robotics Foundation
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
#ifndef GZ_GAZEBO_COMPONENTS_ATMOSPHERE_HH_
#define GZ_GAZEBO_COMPONENTS_ATMOSPHERE_HH_

#include <sdf/Atmosphere.hh>
#include <gz/sim/components/Factory.hh>
#include <gz/sim/components/Component.hh>
#include <gz/sim/components/Serialization.hh>
#include <gz/sim/Conversions.hh>
#include <gz/sim/config.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
namespace serializers
{
  using AtmosphereSerializer =
      serializers::ComponentToMsgSerializer<sdf::Atmosphere, msgs::Atmosphere>;
}

namespace components
{
  /// \brief This component holds atmosphere properties of the world.
  using Atmosphere =
      Component<sdf::Atmosphere, class AtmosphereTag,
      serializers::AtmosphereSerializer>;
  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.Atmosphere", Atmosphere)
}
}
}
}

#endif
