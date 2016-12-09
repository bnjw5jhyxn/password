public class Password extends RandomWord {
	/*
	 * password generator
	 * each password has 16 total characters
	 * 14 lowercase letters, 1 uppercase letter, and 1 decimal digit
	 */
	public Password() {
		/* 15 total letters, has a digit and a capital letter */
		super(15, true, true);
	}
}
