# Объявляем имя проекта
set(TARGET_NAME some_C)

# Собираем исходные файлы
set(SOURCE_LIST
   ${CMAKE_CURRENT_LIST_DIR}/CDynArray.c)

# Создаем статическую библиотеку
add_executable(${TARGET_NAME} ${SOURCE_LIST})

# Указываем общие include директории
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})