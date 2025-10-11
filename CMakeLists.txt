cmake_minimum_required(VERSION 3.10.0)
project(OOP_lab2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Сначала загружаем зависимости
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(googletest)

# Затем добавляем поддиректорию
add_subdirectory(lab2)