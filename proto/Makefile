# using ubuntu protoc package:
#
#    sudo apt-get install protobuf-compiler
#    sudo apt-get install libprotobuf-java
#
# version is 2.6.1

PROTOC_JAVA := /usr/bin/protoc
PROTO_JAVA_JAR := /usr/share/java/protobuf-2.6.1.jar

# well this is embarrassing - protobuf C++ includes are for protobuf version 3.1, whereas
# the Java jar files are for protobuf 2.6.1. (probably got out of sync during an eval of
# protobuf 3.1). Will resolve when we move to new build environment)...

PROTOC_CPP := /usr/local/bin/protoc

JAVA_HOME := ${HOME}/Downloads/jdk1.8.0_112

JAVAC  := ${JAVA_HOME}/bin/javac
JAVAH  := ${JAVA_HOME}/bin/javah
JAVA   := ${JAVA_HOME}/bin/java
JAR    := ${JAVA_HOME}/bin/jar

CPP := /usr/bin/g++


all: scaffold.o scaffold_SAPI.jar
	@echo proto derived code available.


#-------------------------------------------------------------------------------------------------------------------
# compile proto to C++ object...
#-------------------------------------------------------------------------------------------------------------------

scaffold.pb.cc scaffold.pb.h: scaffold.proto
	${PROTOC_CPP} --cpp_out=. scaffold.proto

scaffold.o: scaffold.pb.cc scaffold.pb.h
	${CPP} -fPIC -c scaffold.pb.cc -o $@


#-------------------------------------------------------------------------------------------------------------------
# build simulator serial Java interface...
#-------------------------------------------------------------------------------------------------------------------

# scaffold.proto + google protoc compiler generates Java protocol code...

scaffold_SAPI/ScaffoldSAPI.java: scaffold.proto
	${PROTOC_JAVA} --java_out=. scaffold.proto

# ScaffoldSAPI.jar - make jar file from scaffold java classes...
# ScaffoldSAPI.class - compiled protocol code...

scaffold_SAPI.jar: scaffold_SAPI/ScaffoldSAPI.class
	${JAR} -cvf scaffold_SAPI.jar -C scaffold_SAPI .

scaffold_SAPI/ScaffoldSAPI.class: scaffold_SAPI/ScaffoldSAPI.java
	${JAVAC} -cp ${PROTO_JAVA_JAR}:. scaffold_SAPI/ScaffoldSAPI.java


clean:
	rm -rf scaffold.pb.cc scaffold.pb.h scaffold.pb.o scaffold_SAPI scaffold_SAPI.jar

