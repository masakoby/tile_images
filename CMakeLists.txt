cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_CXX_STANDARD 17)  


project(tile_images)

include_directories("${CMAKE_CURRENT_LIST_DIR}/../common")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../cv")

file(GLOB source1 "./src/*.cpp")
set(source2 
../cv/kb_cv_string.cpp ../cv/kb_cv_string.h 
../cv/kb_cv_arrange_cvmat.cpp ../cv/kb_cv_arrange_cvmat.h 
../cv/kb_cv_resize.cpp ../cv/kb_cv_resize.h 
../common/kb_searchfiles.cpp ../common/kb_searchfiles.h 
../common/kb_searchfolders.cpp ../common/kb_searchfolders.h 
../common/kb_split_string.cpp ../common/kb_split_string.h 
)

add_executable(tile_images ${source1} ${source2})


