file(GLOB_RECURSE SKOGA_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Skoga/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Skoga/*.c"
)

add_library(skoga STATIC ${SKOGA_SRC})

target_compile_definitions(skoga PUBLIC FMT_UNICODE=0)
target_include_directories(skoga PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link internal libraries
target_link_libraries(skoga PRIVATE glfw glad imgui glm)
target_compile_definitions(skoga PUBLIC GLM_ENABLE_EXPERIMENTAL)