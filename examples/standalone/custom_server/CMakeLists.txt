cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(ign-gazebo-custom-server)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  find_package(ignition-gazebo6 REQUIRED)
  set(IGN_GAZEBO_VER ${ignition-gazebo6_VERSION_MAJOR})

  add_executable(custom_server custom_server.cc)
  target_link_libraries(custom_server
    ignition-gazebo${IGN_GAZEBO_VER}::ignition-gazebo${IGN_GAZEBO_VER}
    )
endif()
