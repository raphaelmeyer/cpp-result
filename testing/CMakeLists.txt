# Testing Library
add_library(testing testing.cc)
target_include_directories(testing PUBLIC include)
target_link_libraries(testing PRIVATE settings)

