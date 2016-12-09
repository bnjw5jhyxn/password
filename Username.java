public class Username extends RandomWord {
	/*
	 * username generator
	 * each username has nine lowercase letters and a decimal digit
	 * it has no capital letters
	 */
	public Username() {
		/* 9 letters, a decimal digit and no capitals */
		super(9, true, false);
	}
}
