package simtrace_viewer;

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.lang.Integer;
import java.io.File;

//Long l1 = Long.parseUnsignedLong("17916881237904312345");
//String l1Str = Long.toUnsignedString(l1)
//System.out.println(l1Str);

public class DisasmEntry {
    long   address;
    String function_name;
    int    line;

    public void DisasmEntry() {
	address       = 0;
        function_name = "";
        line          = 0;
    }

    public void Set(long _address, String _function_name, int _line) {
	address       = _address;
        function_name = _function_name;
        line          = _line;
    }

    public void Set(DisasmEntry _sym) {
	address       = _sym.address;
        function_name = _sym.function_name;
        line          = _sym.line;
    }

    public long   Address()      { return address;       }
    public String FunctionName() { return function_name; }
    public int    Line()         { return line;          } 

    public boolean Match(long _address) {
        return address == _address;
    }
    public boolean Below(long _address) {
        return address < _address;
    }
    public boolean Passed(long _address) {
        return address > _address;
    }

    public boolean IsDefined() {
        return (line > 0);
    }

    public void Dump() {
        System.out.println("Address:       " + address);
        System.out.println("Function Name: " + function_name);
        System.out.println("Line:          " + line);
    }
}

