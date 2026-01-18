# Add subdirectories
add_subdirectory(Glad)
add_subdirectory(Glfw)
add_subdirectory(tinyxml2)
add_subdirectory(yoga/yoga)

set(NANOVG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src" PARENT_SCOPE)