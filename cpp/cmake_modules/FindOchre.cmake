# Find the header files

MESSAGE(STATUS "OCHRE_ROOT: " $ENV{OCHRE_ROOT})

FIND_PATH(OCHRE_INCLUDE_DIR ochre/aligner.h
  $ENV{OCHRE_ROOT}/ochre
  /usr/local/include
  /usr/include
  /opt/local/include
  /sw/local/include
  /sw/include
  NO_DEFAULT_PATH
 )

# Macro to unify finding both the debug and release versions of the
# libraries; this is adapted from the OpenSceneGraph FIND_LIBRARY
# macro.
MACRO(FIND_OCHRE_LIBRARY MYLIBRARY MYLIBRARYNAME)
  FIND_LIBRARY("${MYLIBRARY}_DEBUG"
    NAMES "${MYLIBRARYNAME}_d"
    PATHS
    $ENV{OCHRE_ROOT}/lib/Debug
    $ENV{OCHRE_ROOT}/lib
    NO_DEFAULT_PATH
  )

  FIND_LIBRARY("${MYLIBRARY}_DEBUG"
    NAMES "${MYLIBRARYNAME}_d"
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/local/lib64
    /usr/lib
    /usr/lib64
    /opt/local/lib
    /sw/local/lib
    /sw/lib
  )

  FIND_LIBRARY(${MYLIBRARY}
    NAMES "${MYLIBRARYNAME}"
    PATHS
    $ENV{OCHRE_ROOT}/lib/Release
    $ENV{OCHRE_ROOT}/lib
    NO_DEFAULT_PATH
  )

  FIND_LIBRARY(${MYLIBRARY}
    NAMES "${MYLIBRARYNAME}"
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/local/lib64
    /usr/lib
    /usr/lib64
    /opt/local/lib
    /sw/local/lib
    /sw/lib
  )

  IF(NOT ${MYLIBRARY}_DEBUG)
    IF(MYLIBRARY)
      SET(${MYLIBRARY}_DEBUG ${MYLIBRARY})
    ENDIF(MYLIBRARY)
  ENDIF(NOT ${MYLIBRARY}_DEBUG)
ENDMACRO(FIND_OCHRE_LIBRARY LIBRARY LIBRARYNAME)

# Find the core elements
FIND_OCHRE_LIBRARY(OCHRE_LIBRARY ochre)
FIND_OCHRE_LIBRARY(OCHRE_VIEWER_LIBRARY ochre_viewer)
