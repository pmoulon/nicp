ADD_LIBRARY(nicp_core SHARED
  cloud.h
  common_types.h
  utils.h
)
SET_TARGET_PROPERTIES(nicp_core PROPERTIES OUTPUT_NAME ${LIB_PREFIX}_core)
SET_TARGET_PROPERTIES(nicp_core PROPERTIES LINKER_LANGUAGE CXX)

# Include the subdirectories
ADD_SUBDIRECTORY(test)
