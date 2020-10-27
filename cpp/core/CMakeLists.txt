add_library(nicp_core SHARED
  cloud.h
  common_types.h
  data_associator.h
  linearizer.h
  solver.h
  types.h
  utils.h
)
set_target_properties(nicp_core PROPERTIES OUTPUT_NAME ${LIB_PREFIX}_core)
set_target_properties(nicp_core PROPERTIES LINKER_LANGUAGE CXX)

# Include the subdirectories
add_subdirectory(test)

add_executable(main_test
  main_test.cc)
target_link_libraries(main_test nicp_core)
set_target_properties(main_test PROPERTIES OUTPUT_NAME main_test)
set_target_properties(main_test PROPERTIES LINKER_LANGUAGE CXX)
