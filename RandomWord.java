import java.security.SecureRandom;
import java.util.ArrayList;
public class RandomWord {
	/*
	 * username and password generator
	 * total length is one more than the number of letters
	 * the username of password has exactly one decimal digit
	 * it may have a capital letter (the rest are lowercase)
	 */
	private static char[] miniscule =
		"abcdefghijklmnopqrstuvwxyz".toCharArray();
	private static char[] majuscule =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
	private SecureRandom generator;
	private int numberOfLetters;
	private boolean digit;
	private boolean capital;
	private ArrayList<String> values;
	private float entropy;
	public RandomWord(int numberOfLetters, boolean digit, boolean capital) {
		/* initializes the random number generator */
		generator = new SecureRandom();
		/*
		 * the total length of the word will be one more
		 * than the number of letters
		 */
		this.numberOfLetters = numberOfLetters;
		/* digit is true if and only if the word has a decimal digit */
		this.digit = digit;
		/*
		 * capital is true if and only if the word has a capital letter
		 */
		this.capital = capital;
		/* stores all previously generated words */
		values = new ArrayList<String>();
		entropy = computeEntropy();
	}
	public String nextValue() {
		if(numberOfLetters < 0) {return null;}
		StringBuilder word = new StringBuilder();
		/* selects one of the letters to be capitalized */
		int capitalPosition = generator.nextInt(numberOfLetters);
		/*
		 * selects the position of the digit
		 * the digit can be in front of one of the letters
		 * or it can be at the end of the word
		 */
		int digitPosition = generator.nextInt(numberOfLetters + 1);
		/* selects a decimal digit */
		int digitValue = generator.nextInt(10);
		for(int i = 0; i <= numberOfLetters; i ++) {
			int letterIndex = generator.nextInt(26);
			if(i == digitPosition && digit) {
				word.append(digitValue);
			}
			if(i == numberOfLetters) {break;}
			if(i == capitalPosition && capital) {
				word.append(majuscule[letterIndex]);
			} else {
				word.append(miniscule[letterIndex]);
			}
		}
		String newWord = word.toString();
		values.add(newWord);
		return newWord;
	}
	private float computeEntropy() {
		/* each letter has logtwo(26) bits of entropy */
		float letterEntropy = numberOfLetters * logtwo(26);
		float digitEntropy = 0f;
		/*
		 * entropy from both the position and value of the digit
		 * will be evaluated if and only if there is a digit
		 */
		if(digit) {
			digitEntropy = logtwo(numberOfLetters + 1) + logtwo(10);
		}
		float capitalEntropy = 0f;
		/*
		 * entropy from the capitalization of a letter will be counted
		 * if and only if the word actually has a capital letter
		 */
		if(capital) {
			capitalEntropy = logtwo(numberOfLetters);
		}
		return letterEntropy + digitEntropy + capitalEntropy;
	}
	private static float logtwo(int antilog) {
		/* uses the quotient rule of logarithms */
		return (float) (Math.log(antilog) / Math.log(2));
	}
	public int getLength() {
		return numberOfLetters + 1;
	}
	public int getNumberOfLetters() {
		return numberOfLetters;
	}
	public boolean hasDigit() {
		return digit;
	}
	public boolean hasCapital() {
		return capital;
	}
	public String[] getValues() {
		return values.toArray(new String[values.size()]);
	}
	public int getNumberOfValues() {
		return values.size();
	}
	public float getEntropy() {
		return entropy;
	}
}
