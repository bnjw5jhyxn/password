# password-generator
Yes, I actually use this to generate all of my passwords. If it's a bad idea (or badly implemented), please let me know, preferably before you take over all my online accounts.

I'm currently unsure about the utility of separate classes for passwords and usernames. On one hand, these classes do nothing except call the parent constructor with specific parameters. On the other, they are very convenient for storing these parameters and not having to care about their values.

I typically run the driver method just to get one pasword, so this shouldn't be a huge issue for me personally, but I never reseed the random number generator. Should I reseed the generator? If so, how ofter should I do it?
