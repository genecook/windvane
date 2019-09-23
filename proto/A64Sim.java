import scaffold_SAPI.ScaffoldSAPI.Command;
import scaffold_SAPI.ScaffoldSAPI.Response;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;

public class A64Sim {
    static {
	System.loadLibrary("scaffold");
    }

    private native byte[] SimSerialAPI(byte[] request);

    public void show_result(byte[] response_array) throws Exception {
        Response response = Response.parseFrom(response_array);
        if (response.getStatus() == 0) {
	    System.out.format("%s",response.getTracelog());
	} else {
            System.out.format("Response: type: %d status: %d\n",response.getType(),response.getStatus());
            System.out.format("          runlog-entry: '%s'\nerrlog-entry: '%s'\ntracelog-entry: '%s'\ndebuglog-entry: '%s'\n",
            response.getRunlog(),response.getErrlog(),response.getTracelog(),response.getDebuglog());
	}
    }

    public static void main(String[] args) throws Exception {
        System.out.println("#Test serial simulator interface in Java!");

        int num_instrs = 1;

        if (args.length > 0) {
	    num_instrs = Integer.parseInt(args[0]);
        }

        Command.Builder cmd = Command.newBuilder();


        System.out.println("#BOOT SIMULATOR...");

        cmd.setType(Command.Type.BOOT);
        cmd.setCpuid(0);

        byte[] response_array = new A64Sim().SimSerialAPI(cmd.build().toByteArray());
	new A64Sim().show_result(response_array);
        response_array = null;


        System.out.println("#INITIALIZE SIMULATOR...");

        cmd.setType(Command.Type.INIT);

        response_array = new A64Sim().SimSerialAPI(cmd.build().toByteArray());
	new A64Sim().show_result(response_array);
        response_array = null;


        System.out.println("#SETUP FOR FREERUN...");

        cmd.setType(Command.Type.INIT_FREERUN);
        cmd.setCpuid(0);
        cmd.setCount(1);
        cmd.setSeed((int) System.currentTimeMillis());
        cmd.setVerbose(0);

        System.out.format("Seed: %d\n",cmd.getSeed());

        response_array = new A64Sim().SimSerialAPI(cmd.build().toByteArray());
	new A64Sim().show_result(response_array);
        response_array = null;


        cmd.setType(Command.Type.FREERUN_STEP);

        for (int i = 0; i < num_instrs; i++) {
           cmd.setStepIndex(i);
           response_array = new A64Sim().SimSerialAPI(cmd.build().toByteArray());
   	   new A64Sim().show_result(response_array);
           response_array = null;
	}


        System.out.println("#POWER DOWN SIMULATOR...");

        cmd.setType(Command.Type.POWER_DOWN);

        response_array = new A64Sim().SimSerialAPI(cmd.build().toByteArray());
	new A64Sim().show_result(response_array);
        response_array = null;
    }
}
