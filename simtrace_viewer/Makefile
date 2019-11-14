# makefile for simtrace_viewer

JDK_HOME        := ${HOME}/Desktop/tools/jdk-13
JDK_LIBS        := ${JDK_HOME}/lib

JAVAFX_HOME     := ${HOME}/Desktop/tools/javafx-sdk-13
JAVAFX_LIBS     := ${JAVAFX_HOME}/lib

JAVAFX_MODULES  := javafx.base,javafx.controls,javafx.fxml,javafx.graphics

WINDVANE_HOME   := $(shell cd ..;pwd)

SCAFFOLD_LIBDIR := ${WINDVANE_HOME}/proto
PROTO_JAR       := /usr/share/java/protobuf-3.6.1.jar
SCAFFOLD_JAR    := ${SCAFFOLD_LIBDIR}/scaffold_SAPI.jar

LD_LIBRARY_PATH := .:/usr/local/lib:/usr/lib/x86_64-linux-gnu:../lib
JAVA_LIBPATH    := ${SCAFFOLD_LIBDIR}

CLASSPATH       := ..:${SCAFFOLD_JAR}:${PROTO_JAR}

JAVAC           := ${JDK_HOME}/bin/javac
JAVA_EXEC       := ${JDK_HOME}/bin/java
JAR_EXEC        := ${JDK_HOME}/bin/jar


VIEWER_SRCS = InstrView.java RegisterView.java TranslationView.java MemoryView.java SimTraceController.java \
            Disasm.java DisasmEntry.java ParseSymbols.java Symbol.java RegisterDecode.java

VIEWER_CLASSES = $(patsubst %.java,%.class,$(VIEWER_SRCS))

%.class: %.java
	${JAVAC} --module-path ${JAVAFX_LIBS} --add-modules ${JAVAFX_MODULES} --class-path ${CLASSPATH} $<


all: Main.class
	echo a64 sim trace viewer ready.

Main.class: Main.java ${VIEWER_CLASSES}

test:
	${JAVA_EXEC} --module-path ${JAVAFX_LIBS} --add-modules ${JAVAFX_MODULES} --class-path ${CLASSPATH} \
                simtrace_viewer.Main ${TESTCASE} ${COREID} ${CLOCK}

clean:
	rm -rf *.class *.o *.so *~ *# *.jar tmpdir

# To build simtrace viewer java jar file:
#   cd to .. ( ${WINDVANE_HOME} )
#   make soft link to scaffold_SAPI class dir: ln -s ${WINDVANE_HOME}/proto/scaffold_SAPI  # if it does not already exist
#   make -f simtrace_viewer/Makefile simtrace_viewer.jar
#   make tmpdir: mkdir tmpdir (remove old one if there)
#   cd tmpdir
#   extract simtrace viewer jar contents:
#     ${JDK_HOME}/bin/jar -xf ../simtrace_viewer.jar
#   extract java protobuf jar contents:
#     ${JDK_HOME}/bin/jar -xf ${PROTO_JAR}
#   combine into one jar file:
#     cd ..;${JDK_HOME}/bin/jar -cvfm stv.jar simtrace_viewer/SimTraceViewer.mf -C tmpdir .
#
# Now 'install' the simtrace viewer shell script and jar file:
#   cp simtrace_viewer/simtrace_viewer.sh bin
#   cp stv.jar bin

simtrace_viewer.jar: Main.class ${VIEWER_CLASSES}
	cd ..;ln -sf proto/scaffold_SAPI;${JAR_EXEC} cvfm simtrace_viewer.jar simtrace_viewer/SimTraceViewer.mf simtrace_viewer/*.class simtrace_viewer/simtrace_viewer.fxml \
        simtrace_viewer/images/logo.png simtrace_viewer/images/logo.jpg simtrace_viewer/css/simtrace.css simtrace_viewer/css/background.jpg \
        scaffold_SAPI/*.class
	mv ../simtrace_viewer.jar .




