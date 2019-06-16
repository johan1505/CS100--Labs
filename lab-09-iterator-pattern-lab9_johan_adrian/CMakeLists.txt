CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)
SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

ADD_EXECUTABLE(test
   ${PROJECT_SOURCE_DIR}/unit_test.cpp
)

ADD_EXECUTABLE(test2
   ${PROJECT_SOURCE_DIR}/unit_test2.cpp
   ${PROJECT_SOURCE_DIR}/container.cpp
   ${PROJECT_SOURCE_DIR}/VectorContainer.cpp
   ${PROJECT_SOURCE_DIR}/SelectionSort.cpp
   ${PROJECT_SOURCE_DIR}/ListContainer.cpp
   ${PROJECT_SOURCE_DIR}/BubbleSort.cpp
)

ADD_EXECUTABLE(test3
   ${PROJECT_SOURCE_DIR}/unit_test3.cpp
)

ADD_EXECUTABLE(test4
   ${PROJECT_SOURCE_DIR}/unit_test4.cpp
)

ADD_EXECUTABLE(test5	
   ${PROJECT_SOURCE_DIR}/unit_test5.cpp
)

ADD_EXECUTABLE(test6
   ${PROJECT_SOURCE_DIR}/unit_test6.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(test2 gtest)
TARGET_LINK_LIBRARIES(test3 gtest)
TARGET_LINK_LIBRARIES(test4 gtest)
TARGET_LINK_LIBRARIES(test5 gtest)
TARGET_LINK_LIBRARIES(test6 gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test2 PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test3 PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test4 PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test5 PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test6 PRIVATE gtest_disable_pthreads=ON)

