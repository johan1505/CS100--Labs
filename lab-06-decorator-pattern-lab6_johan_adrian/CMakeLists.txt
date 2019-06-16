CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(lab
    main.cpp
)

ADD_EXECUTABLE(test
    unit_test.cpp
)

ADD_EXECUTABLE(test2
    unit_test2.cpp
    container.cpp
    VectorContainer.cpp
    SelectionSort.cpp
    ListContainer.cpp
    BubbleSort.cpp
)

ADD_EXECUTABLE(test3
    unit_test3.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(test2 gtest)
TARGET_LINK_LIBRARIES(test3 gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test2 PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test3 PRIVATE gtest_disable_pthreads=ON)



