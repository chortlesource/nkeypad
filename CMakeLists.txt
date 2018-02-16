#### NKEYPAD CMAKE FILE
cmake_minimum_required(VERSION 3.0)
project(nkeypad)

## NKEYPAD C++11 SUPPORT
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

## NKEYPAD HEADER FILES
set(NKEYPAD_SRC "${CMAKE_SOURCE_DIR}/src")
set(NKEYPAD_INC "${CMAKE_SOURCE_DIR}/include")
include_directories(${NKEYPAD_INC})
add_subdirectory(${NKEYPAD_SRC})

## NKEYPAD EXECUTABLE
add_executable(nkeypad ${NKEYPAD_SRC})

## NKEYPAD DEPENDENCIES
list(APPEND NKEYPAD_LIBS_LIST ncurses)

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  message(STATUS "Finding Packages...")
  pkg_check_modules(PKG_NKEYPAD_LIBS REQUIRED QUIET ${NKEYPAD_LIBS_LIST})
  if(PKG_NKEYPAD_LIBS_FOUND)
    foreach(LIST_ITEM ${PKG_NKEYPAD_LIBS})
      message(STATUS "DEPENDENCY: ${LIST_ITEM} [FOUND]")
    endforeach(LIST_ITEM)
    target_include_directories(nkeypad PUBLIC ${PKG_NKEYPAD_INCLUDE_DIRS} ${PKG_NKEYPAD_MAIN_INCLUDE_DIRS} ${PKG_NKEYPAD_INCLUDE_INCLUDE_DIRS})
    target_link_libraries(nkeypad ${PKG_NKEYPAD_LIBRARIES} ${PKG_NKEYPAD_MAIN_LIBRARIES})
    target_compile_options(nkeypad PUBLIC ${PKG_NKEYPAD_LIBS_CFLAGS} ${PKG_NKEYPAD_LIBS_CFLAGS_OTHER})
  else()
    message(STATUS "[ERROR]: Relevant libraries do not appear to be installed on this system. Please ensure the following libraries are installed:")
    foreach(LIST_ITEM ${NKEYPAD_LIBS_LIST})
      message(STATUS "DEPENDENCY: ${LIST_ITEM} [REQUIRED]")
    endforeach(LIST_ITEM)
  endif()
else()
  message(STATUS "[ERROR]: pkg-config is not installed on this system.")
endif()

## NKEYPAD FLAGS
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -DDEBUG_BUILD")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lncurses")
