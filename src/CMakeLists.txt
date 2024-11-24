# Указываем директорию
add_library(${MAIN_EXECUTABLE}_core
        main.cpp
)

# Указываем пути к заголовочным файлам
target_include_directories(${MAIN_EXECUTABLE}_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${CMAKE_CURRENT_SOURCE_DIR}/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/gui
        ${CMAKE_CURRENT_SOURCE_DIR}/voice
)