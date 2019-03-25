
include_directories (${PROJECT_SOURCE_DIR}/../third_party/Microsoft/angle/include)

include_directories ("${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/common/third_party/base")

add_definitions(-DNOMINMAX
    -D_CRT_SECURE_NO_DEPRECATE
    -D_SCL_SECURE_NO_WARNINGS
    -DLIBANGLE_IMPLEMENTATION
    -DANGLE_STANDALONE_BUILD
    -DGL_GLEXT_PROTOTYPES
    -DANGLE_ENABLE_ESSL
    -DANGLE_ENABLE_GLSL
    -DANGLE_ENABLE_HLSL
    -DANGLE_ENABLE_D3D11
    -DANGLE_ENABLE_D3D9
    -DANGLE_ENABLE_OPENGL
    -DANGLE_ENABLE_NULL
    -DANGLE_X86_CPU
    -DANGLE_ENABLE_DEBUG_ANNOTATIONS
    -DGL_APICALL=
    -DEGLAPI=)

set(THIRD_PARTY_MICROSOFT_ANGLE_DIR 
    "${PROJECT_SOURCE_DIR}/../third_party/Microsoft/angle")

file(GLOB_RECURSE ANGLE_COMMON_HEADER_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/common/*.h")

file(GLOB_RECURSE ANGLE_COMMON_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/common/*.cc"
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/common/*.cpp")

filterFilenameList("${ANGLE_COMMON_SOURCE_FILES}" 
    FILTER_ANGLE_COMMON_SOURCE_FILES 
    ".*((_unittest)|(_linux)|(_mac)).*")

add_library("angle-common" STATIC ${FILTER_ANGLE_COMMON_SOURCE_FILES}
    ${ANGLE_COMMON_HEADER_FILES})

file(GLOB_RECURSE ANGLE_IMAGE_UTIL_HEADER_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/image_util/*.h")

file(GLOB_RECURSE ANGLE_IMAGE_UTIL_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/image_util/*.cpp") 

add_library("angle-image_util" STATIC ${ANGLE_IMAGE_UTIL_HEADER_FILES}
    ${ANGLE_IMAGE_UTIL_SOURCE_FILES})

file(GLOB_RECURSE ANGLE_COMPILER_PREPROCESSOR_HEADER_FILES 
"${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/compiler/preprocessor/*.h")

file(GLOB_RECURSE ANGLE_COMPILER_PREPROCESSOR_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/compiler/preprocessor/*.cpp")

add_library("angle-compiler-preprocessor" STATIC 
    ${ANGLE_COMPILER_PREPROCESSOR_HEADER_FILES}
    ${ANGLE_COMPILER_PREPROCESSOR_SOURCE_FILES})

file(GLOB_RECURSE ANGLE_COMPILER_TRANSLATOR_HEADER_FILES 
"${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/compiler/translator/*.h")

file(GLOB_RECURSE ANGLE_COMPILER_TRANSLATOR_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/compiler/translator/*.cpp")

add_library("angle-compiler-translator" STATIC 
    ${ANGLE_COMPILER_TRANSLATOR_HEADER_FILES}
    ${ANGLE_COMPILER_TRANSLATOR_SOURCE_FILES})

file(GLOB_RECURSE SYSTEMINFO_HEADER_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/third_party/systeminfo/*.h")

file(GLOB_RECURSE SYSTEMINFO_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/third_party/systeminfo/*.cpp")

add_library("systeminfo" STATIC ${SYSTEMINFO_HEADER_FILES}
    ${SYSTEMINFO_SOURCE_FILES})
    
file(GLOB_RECURSE COMPILER_HEADER_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/third_party/compiler/*.h")

file(GLOB_RECURSE COMPILER_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/third_party/compiler/*.cpp")

add_library("compiler" STATIC ${COMPILER_HEADER_FILES}
    ${COMPILER_SOURCE_FILES})

file(GLOB_RECURSE ANGLE_INCLUDE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/include/*.h")
    
file(GLOB_RECURSE ANGLE_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/libANGLE/*.h"
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/libANGLE/*.cpp")

filterFilenameList("${ANGLE_SOURCE_FILES}" FILTER_ANGLE_SOURCE_FILES 
    ".*((_unittest)|(_linux)|(_mac)|(vulkan)|(android)|(GLX)|(Vk)|(Ozone)).*")

filterFilenameList("${FILTER_ANGLE_SOURCE_FILES}" FILTER_ANGLE_SOURCE_FILES 
    ".*((winrt)|(EGLDL)).*")

string(REGEX REPLACE "/" "\\\\"
    BINARY_WIN_DIR "${CMAKE_BINARY_DIR}")

string(REGEX REPLACE "/" "\\\\"
THIRD_PARTY_MICROSOFT_ANGLE_WIN_DIR "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}")

add_custom_target(gen-commit_id 
    COMMAND if not exist ${BINARY_WIN_DIR}\\gen\\libAngle\\include\\id\\ mkdir 
        ${BINARY_WIN_DIR}\\gen\\libAngle\\include\\id\\
    COMMAND ${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/commit_id.py gen 
        ${THIRD_PARTY_MICROSOFT_ANGLE_WIN_DIR}\\
        ${BINARY_WIN_DIR}\\gen\\libAngle\\include\\id\\commit.h)

include_directories (
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src"
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/common/third_party/base"
    "${BINARY_WIN_DIR}/gen/libAngle/include"
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/third_party/khronos")

add_library("libAngle" STATIC ${ANGLE_INCLUDE_FILES} 
    ${FILTER_ANGLE_SOURCE_FILES})

add_dependencies("libAngle" "gen-commit_id")
target_link_libraries("libAngle" "angle-common" 
    "angle-image_util"
    "angle-compiler-preprocessor"
    "angle-compiler-translator"
    "systeminfo"
    "compiler")

file(GLOB_RECURSE GLESv2_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/libGLESv2/*.h"
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/libGLESv2/*.cpp")

add_library("libGLESv2" STATIC ${GLESv2_SOURCE_FILES})

target_link_libraries("libGLESv2" "libAngle")

file(GLOB_RECURSE EGL_SOURCE_FILES 
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/libEGL/*.h"
    "${THIRD_PARTY_MICROSOFT_ANGLE_DIR}/src/libEGL/*.cpp")

add_library("libEGL" STATIC ${EGL_SOURCE_FILES})
    
target_link_libraries("libEGL" "libGLESv2")
