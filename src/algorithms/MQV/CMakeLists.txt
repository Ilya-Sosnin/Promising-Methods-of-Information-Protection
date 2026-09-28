set(target_name MQV)

add_library(${target_name}
  MQV/MQV.cpp
  MQV/MQV.h
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