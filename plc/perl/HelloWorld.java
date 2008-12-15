
# John Reese
# 2005-12-02
#
# outputs Java method declarations form all source
# files in the current directory


class HelloWorld {
	
	public void SayHello ( int times, String phrase ) {
		for (x = 0; x < times; x++)
			system.out.println(phrase);
	}

	public static void Main ( String [] args ) {
		SayHello(4,"Hello!");
	}
}
