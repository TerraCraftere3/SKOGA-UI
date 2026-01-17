# Add subdirectories
add_subdirectory(Glad)
add_subdirectory(Glfw)

set(NANOVG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src" PARENT_SCOPE)