#!/bin/sh -f

echo "\nStarting up simulation-trace viewer tool...\n"

if [ -n "$JAVA_HOME" ]; then
    echo JAVA_HOME already set to: $JAVA_HOME
else
    JAVA_HOME=~/Desktop/tools/jdk-13
    echo Assuming JAVA_HOME is: $JAVA_HOME
fi

if [ -n "$JAVAFX_HOME" ]; then
    echo JAVAFX_HOME already set to: $JAVAFX_HOME
else
    JAVAFX_HOME=~/Desktop/tools/javafx-sdk-13
    echo Assuming JAVAFX_HOME is: $JAVAFX_HOME
fi

SCRIPT=`realpath $0`
SCRIPTPATH=`dirname $SCRIPT`

if [ -f './stv.jar' ]; then
    echo "Found simtrace-viewer jar file (stv.jar) in current directory. Will ASSUME its current..."
    STV_HOME='.'
else
    echo "Assuming simtrace-viewer jar-file is located in same directory as this script..."
    STV_HOME=$SCRIPTPATH
fi

JDK_MODULES=javafx.base,javafx.controls,javafx.fxml,javafx.graphics

if [ -f $STV_HOME/stv.jar ]; then
    $JAVA_HOME/bin/java --module-path $STV_HOME:$JAVAFX_HOME/lib --add-modules stv,$JDK_MODULES simtrace_viewer.Main
else
    echo "simtrace-viewer jar file ($STV_HOME/stv.jar) not found."
fi




