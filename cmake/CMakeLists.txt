cmake_minimum_required (VERSION 3.0.2)

set(TRIANGLE_LIBRARY_TYPE "STATIC")
set(3D_GRAPHICS_API "DIRECT3D" CACHE STRING "")

add_compile_options(-std=c++11)

project(triangle)

function(setSourceGroup strSourceGroup strDir)
    file(GLOB listFiles "${strDir}/*")
    foreach(it ${listFiles})
        get_filename_component(nameFile ${it} NAME)
        get_filename_component(extFile ${it} EXT)
        if(IS_DIRECTORY ${it})  
            setSourceGroup("${strSourceGroup}\\${nameFile}"
                "${strDir}/${nameFile}")
        else()
            source_group(${strSourceGroup} FILES ${it})
        endif()
    endforeach()
endfunction(setSourceGroup)

function(filterFilenameList inList outList strExcludeRegex)
    foreach(it ${inList})
        get_filename_component(nameFile ${it} NAME)
        if (NOT ${it} MATCHES ${strExcludeRegex})
            list(APPEND l ${it})
        endif()
    endforeach()
    set(${outList} ${l} PARENT_SCOPE)
endfunction(filterFilenameList)

include_directories (${PROJECT_SOURCE_DIR}/../include)

file(GLOB_RECURSE TRIANGLE_INCLUDE_FILES "${PROJECT_SOURCE_DIR}/../include/*")

file(GLOB_RECURSE TRIANGLE_SRC_FILES "${PROJECT_SOURCE_DIR}/../src/*")

add_library("triangle" 
    ${TRIANGLE_LIBRARY_TYPE}
    ${TRIANGLE_INCLUDE_FILES}
    ${TRIANGLE_SRC_FILES})

setSourceGroup("Header Files" "${PROJECT_SOURCE_DIR}/../include")
setSourceGroup("Source Files" "${PROJECT_SOURCE_DIR}/../src")

if (WIN32)

if (MSVC)

add_executable("Main" WIN32 ${PROJECT_SOURCE_DIR}/../win/main_msvc.cpp)

string(TOLOWER ${3D_GRAPHICS_API} 3D_GRAPHICS_API_LOWER)

if (3D_GRAPHICS_API_LOWER STREQUAL "direct3d")

add_definitions(-DUSING_DIRECT3D)
target_link_libraries("Main" "triangle" d3d11 d3dcompiler)

elseif(3D_GRAPHICS_API_LOWER STREQUAL "opengl")

add_subdirectory(third_party/Microsoft/angle)

include_directories (${PROJECT_SOURCE_DIR}/../third_party/Microsoft/angle/include)

add_definitions(-DUSING_OPENGL)

target_compile_definitions(triangle PUBLIC
    -DLIBANGLE_IMPLEMENTATION
    -DGL_GLEXT_PROTOTYPES
    -DGL_APICALL=
    -DEGLAPI=)

target_link_libraries("triangle")
target_link_libraries("Main" triangle libEGL d3d11 d3dcompiler)

endif()

elseif (CYGWIN)

endif()

elseif(ANDROID)

endif()