add_library(ochre_3d SHARED
  cloud3d.h
  data_associator_nn_cloud3d_cloud3d_extended.h
  linearizer_point3d_se3.h
)
target_link_libraries(ochre_3d ochre_core)
set_target_properties(ochre_3d PROPERTIES OUTPUT_NAME ${LIB_PREFIX}_3d)
set_target_properties(ochre_3d PROPERTIES LINKER_LANGUAGE CXX)

add_executable(main_test
  main_test.cc)
target_link_libraries(main_test ochre_core ochre_3d)
set_target_properties(main_test PROPERTIES OUTPUT_NAME main_test)
set_target_properties(main_test PROPERTIES LINKER_LANGUAGE CXX)
