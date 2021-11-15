add_executable(oatpp_server main.cpp)
target_link_libraries(oatpp_server oatpp::oatpp project_options)

add_executable(oatpp_json_server main_json.cpp)
target_link_libraries(oatpp_json_server oatpp::oatpp project_options)
