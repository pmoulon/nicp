add_executable(core_test
  main_test.cc
  eigen_matrix_test_helper.h
  se3_utils_test.cc)
target_link_libraries(core_test ochre_core)
set_target_properties(core_test PROPERTIES OUTPUT_NAME ochre_core_test)
set_target_properties(core_test PROPERTIES LINKER_LANGUAGE CXX)
