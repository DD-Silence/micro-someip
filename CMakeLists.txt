CMAKE_MINIMUM_REQUIRED (VERSION 3.8)
PROJECT("micro-someip" C)
ADD_LIBRARY("micro-someip" STATIC SomeIp.c SomeIpXf.c)

add_subdirectory(test)

enable_testing()

ADD_TEST(NAME test1 COMMAND head_test)
ADD_TEST(NAME test2 COMMAND tail_test)
