package simtrace_viewer;

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.lang.Integer;
import java.io.File;

//Long l1 = Long.parseUnsignedLong("17916881237904312345");
//String l1Str = Long.toUnsignedString(l1)
//System.out.println(l1Str);

public class Symbol {
    long address;
    String file;
    int line;

    public void Symbol() {
	address = 0;
        file    = "";
        line    = -1;
    }

    public void Set(long _address, String _file, int _line) {
	address = _address;
        file    = _file;
        line    = _line;
    }

    public void Set(Symbol _sym) {
	address = _sym.address;
        file    = _sym.file;
        line    = _sym.line;
    }

    public long   Address() { return address; }
    public String File()    { return file;    }
    public int    Line()    { return line;    } 

    public boolean Match(long _address) {
        return IsDefined() && (address == _address);
    }

    public boolean IsDefined() {
        return (line > 0);
    }

    public void Dump() {
        System.out.println("Address:" + address);
        System.out.println("File:"    + file);
        System.out.println("Line:"    + line);
    }
}

