cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(ign-gazebo-entity-creation)

find_package(ignition-transport11 QUIET REQUIRED OPTIONAL_COMPONENTS log)
set(IGN_TRANSPORT_VER ${ignition-transport11_VERSION_MAJOR})

add_executable(entity_creation entity_creation.cc)
target_link_libraries(entity_creation
  ignition-transport${IGN_TRANSPORT_VER}::core)
