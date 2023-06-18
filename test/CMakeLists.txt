include_directories(../)
ADD_EXECUTABLE(head_test head_test.c)
target_link_libraries(head_test micro-someip)

ADD_EXECUTABLE(tail_test tail_test.c)
target_link_libraries(tail_test micro-someip)