set(target_name DiffieHellman)

add_library(${target_name}
  DiffieHellman/DiffieHellman.cpp
  DiffieHellman/DiffieHellman.h
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
  BigNumGenerator
)