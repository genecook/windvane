# using ubuntu protoc package:
#
#    sudo apt-get install protobuf-compiler
#    sudo apt-get install libprotobuf-java
#
# version is 3.6.1

PROTOC := /usr/bin/protoc

PROTO_JAVA_JAR := /usr/share/java/protobuf-3.6.1.jar

JAVA_HOME := ${HOME}/Desktop/tools/jdk-13

JAVAC  := ${JAVA_HOME}/bin/javac
JAVAH  := ${JAVA_HOME}/bin/javah
JAVA   := ${JAVA_HOME}/bin/java
JAR    := ${JAVA_HOME}/bin/jar

CPP := /usr/bin/g++
CFLAGS := -I/usr/include -g

all: scaffold.o scaffold_SAPI.jar
	@echo proto derived code available.


#-------------------------------------------------------------------------------------------------------------------
# compile proto to C++ object...
#-------------------------------------------------------------------------------------------------------------------

scaffold.pb.cc scaffold.pb.h: scaffold.proto
	${PROTOC} --cpp_out=. scaffold.proto

scaffold.o: scaffold.pb.cc scaffold.pb.h
	${CPP} ${CFLAGS} -fPIC -c scaffold.pb.cc -o $@


#-------------------------------------------------------------------------------------------------------------------
# build simulator serial Java interface...
#-------------------------------------------------------------------------------------------------------------------

# scaffold.proto + google protoc compiler generates Java protocol code...

scaffold_SAPI/ScaffoldSAPI.java: scaffold.proto
	${PROTOC} --java_out=. scaffold.proto

# ScaffoldSAPI.jar - make jar file from scaffold java classes...
# ScaffoldSAPI.class - compiled protocol code...

scaffold_SAPI.jar: scaffold_SAPI/ScaffoldSAPI.class
	${JAR} -cvf scaffold_SAPI.jar -C scaffold_SAPI .

scaffold_SAPI/ScaffoldSAPI.class: scaffold_SAPI/ScaffoldSAPI.java
	${JAVAC} -cp ${PROTO_JAVA_JAR}:. scaffold_SAPI/ScaffoldSAPI.java


clean:
	rm -rf scaffold.pb.cc scaffold.pb.h scaffold.pb.o scaffold.o scaffold_SAPI scaffold_SAPI.jar

