add_library(nicp_core SHARED
  cloud.h
  common_types.h
  utils.h
)
set_target_properties(nicp_core PROPERTIES OUTPUT_NAME ${LIB_PREFIX}_core)
set_target_properties(nicp_core PROPERTIES LINKER_LANGUAGE CXX)

# Include the subdirectories
add_subdirectory(test)
