cmake_minimum_required (VERSION 2.8)

project (windvane)

add_custom_target(derived ALL
                  COMMAND /bin/cp ${PROJECT_SOURCE_DIR}/* .) 
