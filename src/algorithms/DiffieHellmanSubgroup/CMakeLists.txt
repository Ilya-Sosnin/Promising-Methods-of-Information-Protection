set(target_name DiffieHellmanSubgroup)

add_library(${target_name}
  DiffieHellmanSubgroup/DiffieHellmanSubgroup.cpp
  DiffieHellmanSubgroup/DiffieHellmanSubgroup.h
)

target_include_directories(
  ${target_name} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(
  ${target_name} PRIVATE
)

target_link_libraries(
  ${target_name} PUBLIC
  DiffieHellman
)