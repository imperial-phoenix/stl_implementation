# Требование CMake указывать минимально поддерживаемую версию
cmake_minimum_required(VERSION 3.5)

# Объявление проекта STL_IMPLEMENTATION
project("STL_IMPLEMENTATION" C CXX)

# Определение текущей архитектуры компьютера

# EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
# message(STATUS "Architecture: ${ARCHITECTURE}" )

# set(ARCHITECTURE_x64 "x64")
# set(TARGET_ARCHITECTURE "Not set" CACHE STRING "Specify target architecture")
# set(TARGET_ARC_LIST ${ARCHITECTURE_x64})
# set_property(CACHE TARGET_ARCHITECTURE PROPERTY STRINGS ${TARGET_ARC_LIST})

if (WIN32)
   set(TARGET_OS "Windows")
elseif(UNIX)
   set(TARGET_OS "Linux")
endif()

# Отладочная информация о конфигурации сборки
message(STATUS "*===================*")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
   message(STATUS "| Building : DEBUG ")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
   message(STATUS "| Building: RELEASE")
else()
   message(FATAL_ERROR "Unknown CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
endif()
message(STATUS "| TargetOS : ${TARGET_OS}")
message(STATUS "*===================*")

# Выходные директории
set(STL_IMPLEMENTATION_PATH "${CMAKE_CURRENT_LIST_DIR}")
set(OUTPUT_DIR "${CMAKE_CURRENT_LIST_DIR}/output")

set(OUTPUT_DEBUG_DIR "${OUTPUT_DIR}/Debug")
set(OUTPUT_RELEASE_DIR "${OUTPUT_DIR}/Release")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DEBUG_DIR}/Lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_RELEASE_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DEBUG_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_RELEASE_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DEBUG_DIR}/Bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_RELEASE_DIR}/Bin)

# Подключаемые проекты
add_subdirectory(src)