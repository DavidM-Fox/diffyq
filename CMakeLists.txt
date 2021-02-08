cmake_minimum_required(VERSION 3.0.0)
project(diffyq VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Boost REQUIRED COMPONENTS iostreams system filesystem)

add_executable(diffyq main.cpp src/diffyq.cpp)
target_link_libraries(diffyq Boost::iostreams Boost::system Boost::filesystem)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
