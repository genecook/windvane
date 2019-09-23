import scaffold_SAPI.ScaffoldSAPI.*;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;

public class A64SimTrace {
    public static void main(String[] args) {
        System.out.println("#Test a64sim sim trace in Java!");

        try {
          Scaffold my_scaffold = Scaffold.parseFrom(new FileInputStream(args[0]));
          System.out.println("SimTrace: " + my_scaffold.toString());
	} catch(FileNotFoundException e) {
          System.out.println(args[0] + ": File not found.");
        } catch(IOException e) {
          System.out.println(args[0] + ": Unable to open file.");
        }

    }
}
