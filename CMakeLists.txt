cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0.22621.0 CACHE STRING "" FORCE)

project(Astroworks CXX)

set (CMAKE_CXX_STANDARD 20)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME ALL_BUILD)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "CMakeLists.txt"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
)




























set(PROJECT_NAME Astroworks)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "CMakeLists.txt"
)
source_group("" FILES ${no_group_source_files})

set(___Actor
    "Source/Actor/Actor.cpp"
    "Source/Actor/Actor.h"
)
source_group("ソース ファイル\\Actor" FILES ${___Actor})

set(___Actor__Components
    "Source/Actor/Components/Component.h"
    "Source/Actor/Components/Movement.cpp"
    "Source/Actor/Components/Movement.h"
    "Source/Actor/Components/Transform.cpp"
    "Source/Actor/Components/Transform.h"
)
source_group("ソース ファイル\\Actor\\Components" FILES ${___Actor__Components})

set(___Actor__Virtual_ActorsType
    "Source/Actor/ActorTypes.h"
    "Source/Actor/Alien.cpp"
    "Source/Actor/Alien.h"
    "Source/Actor/Building.cpp"
    "Source/Actor/Building.h"
    "Source/Actor/Marine.cpp"
    "Source/Actor/Marine.h"
    "Source/Actor/Tank.cpp"
    "Source/Actor/Tank.h"
    "Source/Actor/Unit.cpp"
    "Source/Actor/Unit.h"
    "Source/Actor/Worker.cpp"
    "Source/Actor/Worker.h"
)
source_group("ソース ファイル\\Actor\\Virtual_ActorsType" FILES ${___Actor__Virtual_ActorsType})

set(___Camera
    "Source/Camera/Camera.cpp"
    "Source/Camera/Camera.h"
    "Source/Camera/FreeCameraController.cpp"
    "Source/Camera/FreeCameraController.h"
    "Source/Camera/LockCameraController.cpp"
    "Source/Camera/LockCameraController.h"
)
source_group("ソース ファイル\\Camera" FILES ${___Camera})

set(___Framework
    "Source/Framework/Framework.cpp"
    "Source/Framework/Framework.h"
    "Source/Framework/main.cpp"
    "Source/Framework/ResourceManager.cpp"
    "Source/Framework/ResourceManager.h"
)
source_group("ソース ファイル\\Framework" FILES ${___Framework})

set(___Graphics
    "Source/Graphics/Bitmap.cpp"
    "Source/Graphics/Bitmap.h"
    "Source/Graphics/Graphics.cpp"
    "Source/Graphics/Graphics.h"
    "Source/Graphics/Light.h"
    "Source/Graphics/Macros.h"
    "Source/Graphics/Texture.cpp"
    "Source/Graphics/Texture.h"
    "Source/Graphics/Utilities.h"
)
source_group("ソース ファイル\\Graphics" FILES ${___Graphics})

set(___Graphics__Virtual_Containers
    "Source/Graphics/GLTFStaticModel.cpp"
    "Source/Graphics/GLTFStaticModel.h"
    "Source/Graphics/Sprite.cpp"
    "Source/Graphics/Sprite.h"
)
source_group("ソース ファイル\\Graphics\\Virtual_Containers" FILES ${___Graphics__Virtual_Containers})

set(___Input
    "Source/Input/Input.cpp"
    "Source/Input/Input.h"
)
source_group("ソース ファイル\\Input" FILES ${___Input})

set(___Misc
    "Source/Misc/HighResolutionTimer.h"
)
source_group("ソース ファイル\\Misc" FILES ${___Misc})

set(___Player
    "Source/Player/Enemy.cpp"
    "Source/Player/Enemy.h"
    "Source/Player/Player.cpp"
    "Source/Player/Player.h"
)
source_group("ソース ファイル\\Player" FILES ${___Player})

set(___UI
    "Source/UI/Overlay.h"
    "Source/UI/OverlayComplete.cpp"
    "Source/UI/OverlayComplete.h"
    "Source/UI/OverlayGame.cpp"
    "Source/UI/OverlayGame.h"
    "Source/UI/OverlayTitle.cpp"
    "Source/UI/OverlayTitle.h"
    "Source/UI/UI.cpp"
    "Source/UI/UI.h"
    "Source/UI/UIUtilities.h"
)
source_group("ソース ファイル\\UI" FILES ${___UI})

set(___UI__Virtual_Elements
    "Source/UI/Button.cpp"
    "Source/UI/Button.h"
    "Source/UI/Counter.cpp"
    "Source/UI/Counter.h"
    "Source/UI/Image.cpp"
    "Source/UI/Image.h"
    "Source/UI/Timer.cpp"
    "Source/UI/Timer.h"
    "Source/UI/Widget.h"
)
source_group("ソース ファイル\\UI\\Virtual_Elements" FILES ${___UI__Virtual_Elements})

set(ALL_FILES
    ${no_group_source_files}
    ${___Actor}
    ${___Actor__Components}
    ${___Actor__Virtual_ActorsType}
    ${___Camera}
    ${___Framework}
    ${___Graphics}
    ${___Graphics__Virtual_Containers}
    ${___Input}
    ${___Misc}
    ${___Player}
    ${___UI}
    ${___UI__Virtual_Elements}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "Astroworks"
    TARGET_NAME_RELEASE "Astroworks"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/x64/Debug/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/x64/Release/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/x64/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/x64/Release"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DEBUG   "Astroworks"
    ARCHIVE_OUTPUT_NAME_RELEASE "Astroworks"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/External/VulkanSDK/1.3.243.0/Include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/External/glm;"
    "${CMAKE_CURRENT_SOURCE_DIR}/External/glfw-3.3.8.bin.WIN64/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/External/loaders"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "CMAKE_INTDIR=\"Debug\""
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"Release\""
    ">"
    "_CONSOLE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >
        /permissive-;
        /MP;
        /sdl;
        /W3;
        /Zi;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /MANIFEST;
        /DEBUG;
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "vulkan-1;"
    "glfw3;"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/./External/VulkanSDK/1.3.243.0/Lib;"
    "${CMAKE_CURRENT_SOURCE_DIR}/./External/VulkanSDK/1.3.243.0/Lib/$<CONFIG>;"
    "${CMAKE_CURRENT_SOURCE_DIR}/./External/glfw-3.3.8.bin.WIN64/lib-vc2022;"
    "${CMAKE_CURRENT_SOURCE_DIR}/./External/glfw-3.3.8.bin.WIN64/lib-vc2022/$<CONFIG>"
)



























set(PROJECT_NAME ZERO_CHECK)

################################################################################
# Source groups
################################################################################
set(CMake_Rules
    "CMakeFiles/cd1557cb5e2aa8d2909b9ccf605c8039/generate.stamp.rule"
)
source_group("CMake Rules" FILES ${CMake_Rules})

set(ALL_FILES
    ${CMake_Rules}
)

