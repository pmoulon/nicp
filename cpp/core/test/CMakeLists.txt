add_executable(core_test
  main_test.cc
  eigen_matrix_test_helper.h
  utils_test.cc)
set_target_properties(core_test PROPERTIES OUTPUT_NAME nicp_core_test)
set_target_properties(core_test PROPERTIES LINKER_LANGUAGE CXX)
