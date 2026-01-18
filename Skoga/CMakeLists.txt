file(GLOB_RECURSE SKOGA_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Skoga/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Skoga/*.c"
    "${NANOVG_INCLUDE_DIR}/*.c"
)

add_library(skoga STATIC ${SKOGA_SRC})

target_compile_definitions(skoga PUBLIC FMT_UNICODE=0)
target_include_directories(skoga PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link internal libraries
target_link_libraries(skoga PUBLIC glfw glad yogacore tinyxml2)
target_include_directories(skoga PUBLIC
    "${NANOVG_INCLUDE_DIR}"
)
target_compile_definitions(skoga PUBLIC
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:SKOGA_DEBUG>
)
