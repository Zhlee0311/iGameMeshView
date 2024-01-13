# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/iGameView_Lite_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/iGameView_Lite_autogen.dir/ParseCache.txt"
  "iGameView_Lite_autogen"
  )
endif()
