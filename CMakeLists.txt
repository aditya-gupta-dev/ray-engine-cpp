cmake_minimum_required(VERSION 3.12)
project(GameRaylib CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Release build type for maximum performance if none is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Gather all source files from the lib and include directories.
# CONFIGURE_DEPENDS ensures CMake automatically reconfigures when you add or remove files.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "lib/*.cpp" "lib/*.c")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.hpp" "include/*.h")

add_executable(${PROJECT_NAME} Main.cpp ${SOURCES} ${HEADERS})

# Add the include directory so headers can be found
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Apply extreme performance optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -O3             # Highest level of optimization
        -march=native   # Optimize specifically for the current CPU architecture
        -ffast-math     # Allow aggressive floating point optimizations
    )
    
    # Enable Link-Time Optimization (LTO) for maximum speed if supported
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported)
    if(ipo_supported)
        set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        /O2     # Maximize speed
        /Ob2    # Aggressive inline expansion
        /Oi     # Enable intrinsic functions
        /Ot     # Favor fast code
        /fp:fast # Fast floating point model
    )
    # Enable Link-Time Code Generation (LTO) in MSVC
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Find and link raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    # Fallback to pkg-config if find_package fails (common on Linux)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(raylib REQUIRED raylib)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})
    target_link_options(${PROJECT_NAME} PRIVATE ${raylib_LDFLAGS})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()

# ==============================================================================
# Static Build Target
# ==============================================================================
# Create a secondary executable target for the static build
add_executable(${PROJECT_NAME}_static EXCLUDE_FROM_ALL Main.cpp ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}_static PRIVATE include)

# Apply the same optimization flags to the static target
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME}_static PRIVATE -O3 -march=native -ffast-math)
    if(ipo_supported)
        set_property(TARGET ${PROJECT_NAME}_static PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
    
    # Statically link the C++ runtime libraries to increase portability
    # (Note: Fully static `-static` would require a static version of raylib and X11 to be installed)
    target_link_options(${PROJECT_NAME}_static PRIVATE -static-libgcc -static-libstdc++)
elseif(MSVC)
    target_compile_options(${PROJECT_NAME}_static PRIVATE /O2 /Ob2 /Oi /Ot /fp:fast)
    set_property(TARGET ${PROJECT_NAME}_static PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Link raylib to the static target
if (NOT raylib_FOUND)
    target_link_libraries(${PROJECT_NAME}_static PRIVATE ${raylib_LIBRARIES})
    target_include_directories(${PROJECT_NAME}_static PRIVATE ${raylib_INCLUDE_DIRS})
    target_link_options(${PROJECT_NAME}_static PRIVATE ${raylib_LDFLAGS})
else()
    target_link_libraries(${PROJECT_NAME}_static PRIVATE raylib)
endif()

# Bind the 'make static' command to build the GameRaylib_static target
add_custom_target(static
    DEPENDS ${PROJECT_NAME}_static
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Built static executable: ${PROJECT_NAME}_static"
)
