find_package(fmt)
find_package(spdlog)
find_package(docopt)
find_package(oatpp)

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog)


add_subdirectory(tutorial_01_simple_project)
