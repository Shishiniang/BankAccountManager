cmake_minimum_required(VERSION 3.10)

project (BankAccountManager)

add_executable(main
    src/main.cpp
    src/account.cpp
    src/date.cpp
    src/Array.cpp
)

target_include_directories(main PRIVATE include)