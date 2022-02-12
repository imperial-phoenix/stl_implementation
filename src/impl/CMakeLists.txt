# Объявляем имя проекта
set(TARGET_NAME MyStl)

# Собираем заголовочные файлы
set(HEADER_LIST
   ${SHARED_INCLUDE_DIRS}/include/Vector.h)

# Собираем исходные файлы
set(SOURCE_LIST
   ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/Vector.cpp)

# Создаем статическую библиотеку
add_library(${TARGET_NAME} STATIC ${HEADER_LIST} ${SOURCE_LIST})

# Указываем общие include директории
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})

# Добавляем обработку сишной библиотеки
add_subdirectory(some_c)