project(jam)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
cmake_minimum_required(VERSION 3.17)

# install threads lib
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Install raylib
if(NOT raylib_FOUND)
  INCLUDE(FetchContent)

  FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz)
  FetchContent_GetProperties(raylib)

  if(NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    set(raylib_FOUND TRUE)
  endif()
endif()

# target_link_librairies
if(UNIX)
  add_compile_options(-Wall -lstdc++fs -std=c++20 -lraylib -lglfw3 -lGL -lopenal -lm -lthread -ldl -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -g3)
endif(UNIX)

if (WIN32)
  add_compile_options(-D_WIN32_WINNT=0x0601)
endif()
# Compile with CFLAG
# add_compile_options(-Wall -lstdc++fs -std=c++20 -lraylib -lglfw3 -lGL -lopenal -lm -lpthread -ldl -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -g3)
set(server_files ${PROJECT_SOURCE_DIR}/src/Network/server.cpp)

# Set Include Directory
# include_directories(${lib_asio} ${PROJECT_SOURCE_DIR}/Network)

# Set Cmake Wildcard
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB ALL_SRCS
  "main.cpp"

  # "Builders/*.cpp"
  "src/Factory/*.cpp"
  "src/Components/*.cpp"
  "src/Entity/*.cpp"
  "src/System/*.cpp"
  "src/State/*.cpp"
  # "src/Network/client.cpp"
)

# Set Sources Files & Link Libraries for client
SET(boost_required_libs ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
add_executable(${PROJECT_NAME} ${ALL_SRCS})
target_link_libraries(${PROJECT_NAME} Threads::Threads "raylib" ${boost_required_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_PATH}/boost ${PROJECT_SOURCE_DIR}/Network)
