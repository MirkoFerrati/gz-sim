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
#ifndef GZ_GAZEBO_COMPONENTS_GEOMETRY_HH_
#define GZ_GAZEBO_COMPONENTS_GEOMETRY_HH_

#include <gz/msgs/geometry.pb.h>

#include <sdf/Geometry.hh>

#include <gz/sim/components/Factory.hh>
#include <gz/sim/components/Component.hh>
#include <gz/sim/components/Serialization.hh>
#include <gz/sim/config.hh>
#include <gz/sim/Conversions.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
namespace serializers
{
  using GeometrySerializer =
      serializers::ComponentToMsgSerializer<sdf::Geometry, msgs::Geometry>;
}

namespace components
{
  /// \brief This component holds an entity's geometry.
  using Geometry = Component<sdf::Geometry, class GeometryTag,
                             serializers::GeometrySerializer>;

  IGN_GAZEBO_REGISTER_COMPONENT("ign_gazebo_components.Geometry", Geometry)

}
}
}
}

#endif
