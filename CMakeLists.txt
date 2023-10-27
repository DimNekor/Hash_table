cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(5_laba_hash_table)

add_executable(5_laba_hash_table
               src/main.cpp
               include/hash_table.h
               src/rhash_table.cpp
               src/vector.cpp
               include/vector.h
               )

