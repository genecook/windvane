public class KickMe {
    static {
	System.loadLibrary("kickme");
    }

    private native String sayKickMe(String XS);

    public static void main(String[] args) {
        String response = new KickMe().sayKickMe("Say Dude!"); // invoke the native method
        System.out.println(response);
    }
}
