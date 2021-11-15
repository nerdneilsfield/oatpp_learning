add_executable(structured_oatpp_server src/App.cpp)
target_include_directories(structured_oatpp_server PUBLIC src/)
target_link_libraries(structured_oatpp_server PRIVATE oatpp::oatpp)
