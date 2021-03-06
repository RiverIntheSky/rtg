cmake_minimum_required(VERSION 3.1)
project(Assimp)

file(GLOB_RECURSE SOURCE_FILES "*.c" "*.cpp" "*.cc")
file(GLOB_RECURSE HEADER_FILES "*.hh" "*.h" "*.hpp" "*.inl")

add_subdirectory(contrib/zlib)

if(MSVC)
    set(ASSIMP_LINK_TYPE STATIC)
else()
    set(ASSIMP_LINK_TYPE SHARED)
endif()

add_library(assimp ${ASSIMP_LINK_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

if(MSVC)
    target_include_directories(assimp PUBLIC
        code/BoostWorkaround
    )
endif()

target_include_directories(assimp PUBLIC
    include/
    contrib/openddlparser/include
)

if(NOT MSVC)
	target_compile_options(assimp PUBLIC
		$<$<COMPILE_LANGUAGE:CXX>:-std=c++11>
	)
else()
    target_compile_options(assimp PUBLIC
        /MP # multi processor compilation
        )
endif()

target_compile_definitions(assimp PUBLIC
    ASSIMP_BUILD_NO_C4D_IMPORTER
)

target_compile_definitions(assimp PRIVATE
	OPENDDLPARSER_BUILD
)

target_link_libraries(assimp PRIVATE zlibstatic)
