set(target_name BigNumGenerator)

add_library(${target_name}
  generator/BigNumGenerator.cpp
  generator/BigNumGenerator.h
)

target_include_directories(
  ${target_name} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  C:/msys64/ucrt64/include
)

target_link_directories(
  ${target_name} PRIVATE
  C:/msys64/ucrt64/lib
)

target_link_libraries(
  ${target_name} PRIVATE
  gmp
)
