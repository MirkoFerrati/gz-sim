add_subdirectory(rendering)
add_subdirectory(gui)
add_subdirectory(systems)
add_subdirectory(msgs)

set_source_files_properties(
  ${PROTO_PRIVATE_SRC}
  ${PROTO_PRIVATE_HEADERS}
  PROPERTIES GENERATED TRUE
)

# Suppress compiler warnings in generated protobuf C++ code.
if(NOT MSVC)
  set_source_files_properties(
    ${PROTO_PRIVATE_SRC}
    COMPILE_FLAGS -Wno-unused-parameter
  )
endif()

set(network_sources
  network/NetworkConfig.cc
  network/NetworkManager.cc
  network/NetworkManagerPrimary.cc
  network/NetworkManagerSecondary.cc
  network/PeerInfo.cc
  network/PeerTracker.cc
)

set(comms_sources
  comms/Broker.cc
  comms/ICommsModel.cc
  comms/MsgManager.cc
)

set(gui_sources
  ${gui_sources}
  PARENT_SCOPE
)

set(cli_sources
  gz.cc
  cmd/ModelCommandAPI.cc
)

set (sources
  Actor.cc
  Barrier.cc
  BaseView.cc
  Conversions.cc
  ComponentFactory.cc
  EntityComponentManager.cc
  Joint.cc
  LevelManager.cc
  Light.cc
  Link.cc
  Model.cc
  Primitives.cc
  SdfEntityCreator.cc
  SdfGenerator.cc
  Sensor.cc
  Server.cc
  ServerConfig.cc
  ServerPrivate.cc
  SimulationRunner.cc
  SystemLoader.cc
  SystemManager.cc
  TestFixture.cc
  Util.cc
  View.cc
  World.cc
  cmd/ModelCommandAPI.cc
  ${PROTO_PRIVATE_SRC}
  ${network_sources}
  ${comms_sources}
)

set (gtest_sources
  ${gtest_sources}
  Actor_TEST.cc
  Barrier_TEST.cc
  BaseView_TEST.cc
  ComponentFactory_TEST.cc
  Component_TEST.cc
  Conversions_TEST.cc
  EntityComponentManager_TEST.cc
  EventManager_TEST.cc
  Joint_TEST.cc
  Light_TEST.cc
  Link_TEST.cc
  Model_TEST.cc
  Primitives_TEST.cc
  SdfEntityCreator_TEST.cc
  SdfGenerator_TEST.cc
  Sensor_TEST.cc
  ServerConfig_TEST.cc
  Server_TEST.cc
  SimulationRunner_TEST.cc
  SystemLoader_TEST.cc
  SystemManager_TEST.cc
  System_TEST.cc
  TestFixture_TEST.cc
  Util_TEST.cc
  World_TEST.cc
  comms/Broker_TEST.cc
  comms/MsgManager_TEST.cc
  network/NetworkConfig_TEST.cc
  network/PeerTracker_TEST.cc
  network/NetworkManager_TEST.cc
)

# gz_TEST and ModelCommandAPI_TEST are not supported with multi config
# CMake generators, see also cmd/CMakeLists.txt
get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT GENERATOR_IS_MULTI_CONFIG)
  list(APPEND gtest_sources gz_TEST.cc)
endif()


# Tests that require a valid display
set(tests_needing_display
)

if(NOT GENERATOR_IS_MULTI_CONFIG)
  list(APPEND tests_needing_display ModelCommandAPI_TEST.cc)
endif()

# Add systems that need a valid display here.
# \todo(anyone) Find a way to run these tests with a virtual display such Xvfb
# or Xdummy instead of skipping them
if(VALID_DISPLAY AND VALID_DRI_DISPLAY)
  list(APPEND gtest_sources ${tests_needing_display})
else()
  message(STATUS
    "Skipping these UNIT tests because a valid display was not found:")
  foreach(test ${tests_needing_display})
    message(STATUS " ${test}")
  endforeach(test)
endif()

if (MSVC)
  # Warning #4251 is the "dll-interface" warning that tells you when types used
  # by a class are not being exported. These generated source files have private
  # members that don't get exported, so they trigger this warning. However, the
  # warning is not important since those members do not need to be interfaced
  # with.
  set_source_files_properties(${sources} ${gtest_sources} ${cli_sources} COMPILE_FLAGS "/wd4251 /wd4146")
endif()

# CLI
ign_add_component(ign
  SOURCES
    ${cli_sources}
  GET_TARGET_NAME ign_lib_target)
target_link_libraries(${ign_lib_target}
  PRIVATE
    ${PROJECT_LIBRARY_TARGET_NAME}
    ignition-common${IGN_COMMON_VER}::ignition-common${IGN_COMMON_VER}
    ignition-gazebo${PROJECT_VERSION_MAJOR}
    ignition-gazebo${PROJECT_VERSION_MAJOR}-gui
)

# Create the library target
ign_create_core_library(SOURCES ${sources} CXX_STANDARD 17)
target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
  ignition-math${IGN_MATH_VER}
  ignition-plugin${IGN_PLUGIN_VER}::core
  ignition-common${IGN_COMMON_VER}::ignition-common${IGN_COMMON_VER}
  ignition-common${IGN_COMMON_VER}::profiler
  ignition-fuel_tools${IGN_FUEL_TOOLS_VER}::ignition-fuel_tools${IGN_FUEL_TOOLS_VER}
  ignition-gui${IGN_GUI_VER}::ignition-gui${IGN_GUI_VER}
  ignition-physics${IGN_PHYSICS_VER}::core
  ignition-rendering${IGN_RENDERING_VER}::core
  ignition-transport${IGN_TRANSPORT_VER}::ignition-transport${IGN_TRANSPORT_VER}
  sdformat${SDF_VER}::sdformat${SDF_VER}
  protobuf::libprotobuf
  PRIVATE
  ignition-plugin${IGN_PLUGIN_VER}::loader
)
if (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
    PRIVATE stdc++fs)
endif()

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

add_dependencies(${PROJECT_LIBRARY_TARGET_NAME}
  ignition-gazebo_private_msgs
)

set(IGNITION_GAZEBO_PLUGIN_INSTALL_DIR
  ${CMAKE_INSTALL_PREFIX}/${IGN_LIB_INSTALL_DIR}/ign-${IGN_DESIGNATION}-${PROJECT_VERSION_MAJOR}/plugins
)

include_directories(${PROJECT_SOURCE_DIR}/test)

# Build the unit tests
ign_build_tests(TYPE UNIT
  SOURCES
    ${gtest_sources}
  LIB_DEPS
    ${PROJECT_LIBRARY_TARGET_NAME}
    ${EXTRA_TEST_LIB_DEPS}
    ignition-gazebo${PROJECT_VERSION_MAJOR}
)

# Command line tests need extra settings
foreach(CMD_TEST
  UNIT_gz_TEST
  UNIT_ModelCommandAPI_TEST)

  if(NOT TARGET ${CMD_TEST})
    continue()
  endif()

  # Running `ign gazebo` on macOS has problems when run with /usr/bin/ruby
  # due to System Integrity Protection (SIP). Try to find ruby from
  # homebrew as a workaround.
  if (APPLE)
    find_program(BREW_RUBY ruby HINTS /usr/local/opt/ruby/bin)
  endif()

  add_dependencies(${CMD_TEST}
    ${ign_lib_target}
    TestModelSystem
    TestSensorSystem
    TestWorldSystem
  )

  target_compile_definitions(${CMD_TEST} PRIVATE
      "BREW_RUBY=\"${BREW_RUBY} \"")

  target_compile_definitions(${CMD_TEST} PRIVATE
      "IGN_PATH=\"${IGNITION-TOOLS_BINARY_DIRS}\"")

  set(_env_vars)
  list(APPEND _env_vars "IGN_CONFIG_PATH=${CMAKE_BINARY_DIR}/test/conf")
  list(APPEND _env_vars "IGN_GAZEBO_SYSTEM_PLUGIN_PATH=$<TARGET_FILE_DIR:TestModelSystem>")

  set_tests_properties(${CMD_TEST} PROPERTIES
    ENVIRONMENT "${_env_vars}")

  # On Windows there is no RPATH, so an alternative way for tests for finding .dll libraries
  # in build directory in necessary. For regular tests, the trick is to place all libraries
  # and executables in a common CMAKE_RUNTIME_OUTPUT_DIRECTORY, so that the .dll are found
  # as they are in the same directory where the executable is loaded. For tests that are
  # launched via Ruby, this does not work, so we need to manually add CMAKE_RUNTIME_OUTPUT_DIRECTORY
  # to the PATH. This is done via the ENVIRONMENT_MODIFICATION that is only available
  # since CMake 3.22. However, if an older CMake is used another trick to install the libraries
  # beforehand
  if (WIN32 AND CMAKE_VERSION STRGREATER "3.22")
    set_tests_properties(${CMD_TEST} PROPERTIES
      ENVIRONMENT_MODIFICATION "PATH=path_list_prepend:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  endif()

endforeach()

add_subdirectory(cmd)
