if(NOT DEFINED URL)
  message(FATAL_ERROR "URL not defined")
endif()

if(NOT DEFINED FILENAME_ONLINE)
  message(FATAL_ERROR "FILENAME_ONLINE not defined")
endif()

if(NOT DEFINED FILENAME_LOCAL)
  message(FATAL_ERROR "FILENAME_LOCAL not defined")
endif()

set(FULLURL "${URL}/${FILENAME_ONLINE}")

message(STATUS "Downloading ${FULLURL} ...")

file(DOWNLOAD "${FULLURL}" "${FILENAME_LOCAL}" STATUS result_list)

list(GET result_list 0 result)
if(result EQUAL 0)
  message(STATUS "... success")
else()
  list(GET result_text 1 result_str)
  message(STATUS "... FAILED")
  message(FATAL_ERROR "${result_str}")
endif()
