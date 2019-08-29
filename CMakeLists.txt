cmake_minimum_required (VERSION 3.5)
if (UNIX)
  add_definitions(-Wno-sign-compare -Wno-enum-compare)
endif(UNIX)
project(restserver)
set (CMAKE_CXX_STANDARD 11)
option(DBMS "Dbms" OFF)
include_directories("${CMAKE_SOURCE_DIR}")

#include_directories("${CMAKE_SOURCE_DIR}"/libwebp-1.0.3-linux-x86-64)
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


add_executable(restserver
  main.cpp
  src/handler.cpp
  src/DownLoad.cpp
  )

set(Casablanca_LIBRARIES "-lboost_system -lcrypto -lssl -lcpprest")
if(DBMS)
	set(NEW_DB_SRC_DIR ${CMAKE_SOURCE_DIR}/dbms/src)
	add_library(dbms SHARED
		${NEW_DB_SRC_DIR}/Dbms.cpp
		)
	set(Dbms_dep_lib "-lpqxx -lpq")
	target_link_libraries(restserver dbms ${Casablanca_LIBRARIES} ${Dbms_dep_lib})
else(DBMS)

	target_link_libraries(restserver ${Casablanca_LIBRARIES})
endif(DBMS)


FIND_PACKAGE(CURL)
IF(CURL_FOUND)
INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(restserver ${CURL_LIBRARY})
ELSE(CURL_FOUND)
MESSAGE(FATAL_ERROR ”CURL library not found”)
ENDIF(CURL_FOUND)

set(CMAKE_REQUIRED_INCLUDES "/usr/local/include")
INCLUDE_DIRECTORIES(/usr/local/lib)
TARGET_LINK_LIBRARIES(restserver /usr/local/lib/libwebp.so)

# FIND_PACKAGE(webp)
# IF(webp_FOUND)
# INCLUDE_DIRECTORIES(${webp_INCLUDE_DIR})
# TARGET_LINK_LIBRARIES(restserver ${webp_LIBRARY})
# ELSE(webp_FOUND)
# MESSAGE(FATAL_ERROR webp library not found”)
# ENDIF(webp_FOUND)
#target_include_directories(restserver PRIVATE ${CMAKE_SOURCE_DIR}/libwebp-1.0.3-linux-x86-64/include)
#ADD_LIBRARY(restserver STATIC ${CMAKE_SOURCE_DIR}/libwebp-1.0.3-linux-x86-64/lib/)
#TARGET_LINK_LIBRARIES(restserver ${CMAKE_SOURCE_DIR}/libwebp-1.0.3-linux-x86-64/lib/libwebp.a)
#TARGET_LINK_LIBRARIES(restserver ${CMAKE_SOURCE_DIR}/libwebp-1.0.3-linux-x86-64/lib/libwebp.a)

