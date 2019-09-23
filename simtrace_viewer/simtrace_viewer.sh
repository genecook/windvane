#!/bin/sh -f

#---------------------------------------------------------------------------------------
# simtrace_viewer.sh
#
#    shell script wrapper for a64 simulator trace viewer.
#
# locate java executable via JAVA_HOME if set
# else see if java executable is found and if so use that
# else check linux java install directory /usr/lib/jvm/default-java
# 
# Need Java version 1.8 or greater.
#---------------------------------------------------------------------------------------

export STV_HOME=`/usr/bin/dirname $0`
export STV_JAR=$STV_HOME/stv.jar

if [ -n "$JAVA_HOME" ] && [ -x "$JAVA_HOME/bin/java" ];  then
    echo found java executable in $JAVA_HOME     
    _java="$JAVA_HOME/bin/java"
elif [ -p java ]; then
    echo found java executable in PATH
    _java=java
elif [ -x "/usr/lib/jvm/default-java/bin/java" ];  then
    echo "no java, will ASSUME JAVA_HOME is /usr/lib/jvm/default-java..."
    export JAVA_HOME=/usr/lib/jvm/default-java
    _java="$JAVA_HOME/bin/java"
else
    echo "No java executable found, cannot continue. Need Java version 1.8 or greater."
fi

if [ "$_java" ]; then
    version=$("$_java" -version 2>&1 | awk -F '"' '/version/ {print $2}')
    echo version "$version"
    if [ "$version" > "1.7" ]; then
        echo Java version checks out. Starting viewer...
        ${_java} -jar ${STV_JAR} $*
    else         
        echo Java version is less than 1.8. Cannot continue.
    fi
fi

