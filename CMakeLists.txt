cmake_minimum_required(VERSION 3.8)
project(os_lab2)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Указываем путь к исходным файлам для библиотеки
add_library(ArrayProcessor STATIC src/array_processor.cpp)

# Указываем путь к тестам
add_executable(test_array_processor tests/test_array_processor.cpp)

# Добавляем исполнимый файл Main
add_executable(Main src/main.cpp)

# Подключаем Google Test с помощью FetchContent
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Указываем пути для заголовочных файлов
target_include_directories(ArrayProcessor PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_array_processor PRIVATE ${gtest_source_dir}/googletest/include ${gtest_source_dir}/googlemock/include)

# Подключаем Google Test для тестов
target_link_libraries(test_array_processor gtest gtest_main ArrayProcessor)

# Подключаем библиотеку ArrayProcessor для Main
target_link_libraries(Main ArrayProcessor)
