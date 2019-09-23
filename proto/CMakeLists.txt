cmake_minimum_required (VERSION 2.8)

project (windvane)

find_package(Protobuf REQUIRED)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS scaffold.proto)

add_library(scaffold_lib scaffold.pb.cc)

