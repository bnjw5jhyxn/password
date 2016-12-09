public class PrintNew {
	/* measured in characters; adjust to fit your screen */
	private static int screenWidth = 80;
	private static int screenHeight = 21;
	public static void main(String[] args) {
		/* defaults to making usernames */
		RandomWord generator = new Username();
		if(args.length > 0 &&
				args[0].toLowerCase().equals("password")) {
			/* makes passwords */
			generator = new Password();
		}
		int rowLength = screenWidth / (generator.getLength() + 1);
		StringBuilder words = new StringBuilder();
		for(int i = 0; i < screenHeight - 1; i ++) {
			if(i != 0) {words.append('\n');}
			for(int j = 0; j < rowLength; j ++) {
				if(j != 0) {words.append(' ');}
				words.append(generator.nextValue());
			}
		}
		System.out.println(words);
	}
}
