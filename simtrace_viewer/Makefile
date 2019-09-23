# makefile for simtrace_viewer

JAVA_HOME       := ${HOME}/Downloads/jdk1.8.0_112
WINDVANE_HOME   := $(shell cd ..;pwd)

SCAFFOLD_LIBDIR := ${WINDVANE_HOME}/proto
PROTO_JAR       := /usr/share/java/protobuf-2.6.1.jar
SCAFFOLD_JAR    := ${SCAFFOLD_LIBDIR}/scaffold_SAPI.jar

LD_LIBRARY_PATH := .:/usr/local/lib:/usr/lib/x86_64-linux-gnu:../lib
JAVA_LIBPATH    := ${SCAFFOLD_LIBDIR}

JAVAFX_JAR      := ${JAVA_HOME}/jre/lib/ext/jfxrt.jar
CLASSPATH       := ${JAVA_HOME}/jre/lib/ext:${JAVA_HOME}/jre/lib:${JAVA_HOME}/lib
JAVAC           := ${JAVA_HOME}/bin/javac
JAVA_EXEC       := ${JAVA_HOME}/bin/java
JAR_EXEC        := ${JAVA_HOME}/bin/jar


all: Main.class
	echo a64 sim trace viewer ready.


InstrView.class: InstrView.java
	${JAVAC} -cp .:${SCAFFOLD_LIBDIR}:${PROTO_JAR}:${JAVAFX_JAR}:${CLASSPATH} InstrView.java

RegisterView.class: RegisterView.java
	${JAVAC} -cp .:${SCAFFOLD_LIBDIR}:${PROTO_JAR}:${JAVAFX_JAR}:${CLASSPATH} RegisterView.java

TranslationView.class: TranslationView.java
	${JAVAC} -cp .:${SCAFFOLD_LIBDIR}:${PROTO_JAR}:${JAVAFX_JAR}:${CLASSPATH} TranslationView.java

MemoryView.class: MemoryView.java
	${JAVAC} -cp .:${SCAFFOLD_LIBDIR}:${PROTO_JAR}:${JAVAFX_JAR}:${CLASSPATH} MemoryView.java

Disasm.class: Disasm.java
	${JAVAC} -cp ..:${CLASSPATH} Disasm.java

DisasmEntry.class: DisasmEntry.java
	${JAVAC} -cp ..:${CLASSPATH} DisasmEntry.java

ParseSymbols.class: ParseSymbols.java
	${JAVAC} -cp ..:${CLASSPATH} ParseSymbols.java

Symbol.class: Symbol.java
	${JAVAC} -cp ..:${CLASSPATH} Symbol.java

RegisterDecode.class: RegisterDecode.java
	${JAVAC} -cp ..:${CLASSPATH} RegisterDecode.java

SimTraceController.class: SimTraceController.java
	${JAVAC} -cp ..:${SCAFFOLD_LIBDIR}:${PROTO_JAR}:${JAVAFX_JAR}:${CLASSPATH} SimTraceController.java

Main.class: Main.java InstrView.class RegisterView.class TranslationView.class MemoryView.class SimTraceController.class \
            Disasm.class DisasmEntry.class ParseSymbols.class Symbol.class RegisterDecode.class
	${JAVAC} -cp ..:${SCAFFOLD_LIBDIR}:${PROTO_JAR}:${JAVAFX_JAR}:${CLASSPATH} Main.java


# NOTE: add the soft link (see process below), prior to running test for 1st time:

test:
	cd ..;[ -e 'scaffold_SAPI' ] && echo 'link to scaffold jar exists' || ln -s ${WINDVANE_HOME}/proto/scaffold_SAPI
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH};${JAVA_EXEC} -cp ${WINDVANE_HOME}:${JAVAFX_JAR}:${SCAFFOLD_JAR}:${PROTO_JAR} simtrace_viewer.Main ${TESTCASE} ${COREID} ${CLOCK}

# To build simtrace viewer java jar file:
#   cd to .. ( ${WINDVANE_HOME} )
#   make soft link to scaffold_SAPI class dir: ln -s ${WINDVANE_HOME}/proto/scaffold_SAPI  # if it does not already exist
#   make -f simtrace_viewer/Makefile simtrace_viewer.jar
#   make tmpdir: mkdir tmpjar (remove old one if there)
#   cd tmpdir
#   extract simtrace viewer jar contents:
#     ${JAVA_HOME}/bin/jar -xf ../simtrace_viewer.jar
#   extract java protobuf jar contents:
#     ${JAVA_HOME}/bin/jar -xf ${PROTO_JAR}
#   combine into one jar file:
#     cd ..;${JAVA_HOME}/bin/jar -cvfm stv.jar simtrace_viewer/SimTraceViewer.mf -C tmpdir .
#
# Now 'install' the simtrace viewer shell script and jar file:
#   cp simtrace_viewer/simtrace_viewer.sh bin
#   cp stv.jar bin

simtrace_viewer.jar:
	${JAR_EXEC} cvfm simtrace_viewer.jar simtrace_viewer/SimTraceViewer.mf simtrace_viewer/*.class simtrace_viewer/simtrace_viewer.fxml \
             simtrace_viewer/images/logo.png simtrace_viewer/images/logo.jpg simtrace_viewer/css/simtrace.css simtrace_viewer/css/background.jpg \
             simtrace_viewer/cpu.simtrace scaffold_SAPI/*.class

test_jar:
	${JAVA_EXEC} -cp ${JAVAFX_JAR}:${PROTO_JAR}:${WINDVANE_HOME}/simtrace_viewer.jar simtrace_viewer.Main


clean:
	rm -rf *.class *.o *.so *~ *# *.jar

