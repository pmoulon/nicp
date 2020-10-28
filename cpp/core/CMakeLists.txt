add_library(ochre_core SHARED
  common_types.h
  data_associator.h
  linearizer.h
  se3_utils.h
  solver.h
  types.h
)
set_target_properties(ochre_core PROPERTIES OUTPUT_NAME ${LIB_PREFIX}_core)
set_target_properties(ochre_core PROPERTIES LINKER_LANGUAGE CXX)

# Include the subdirectories.
add_subdirectory(test)
