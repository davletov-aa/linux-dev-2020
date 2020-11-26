#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <iostream>

#define _(STRING) gettext(STRING)

//! first 100 roman numbers
char * arab2Roman[100] = {
	"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

/*! Converts integer from arabic notation to roman notation
	\param arabic
	\returns input in roman notation
*/
const char * fromArab2Roman(int arabic) {
	return arab2Roman[arabic - 1];
}

/*! Converts integer from roman notation to arabic notation
	\param roman
	\returns input in roman notation
*/
int fromRoman2Arabic(const char *roman) {
	for (int i = 0; i < 100; ++i) {
		if (!strcmp(roman, arab2Roman[i])) {
			return i + 1;
		}
	}
	return 0;
}


#define HELP_MSG _(\
			"Guesser game, just try it%1$s%1$s"\
			"Usage: game [--help] [-r]%1$s%1$s"\
			"Options:%1$s"\
			"\t--help,  -- print help message%1$s"\
			"\t-r,      -- turn on roman numbers notation%1$s%1$s")


int main(int argc, char **argv) {

	setlocale (LC_ALL, "");
	bindtextdomain ("guesser", ".");
	textdomain("guesser");
	bool romanMode;
	if (argc != 1) {
		
		if (!strcmp(argv[1], "--help")) {
			printf(HELP_MSG, "\n");
		}
		if (!strcmp(argv[1], "--version")) {
			printf("guesser 1.0.1\n");
		}
		if (!strcmp(argv[1], "--help-doxy")) {
			printf("/*!\n\\mainpage\n");
			printf(HELP_MSG, "\n\n");
			printf("*/\n");
		}
		if (strcmp(argv[1], "-r") == 0) {
			romanMode = true;
		} else {
			return 0;
		}
	} else {
		romanMode = false;
	}

	int start = 1, end = 100, half;
	if (romanMode){
		printf(_("Guess the number from %s to %s\n"), fromArab2Roman(1), fromArab2Roman(100));
	} else {
		printf(_("Guess the number from %d to %d\n"), 1, 100);
	}
	char answer[256];

	while (true) {
		if (end - start < 2) {
			if (romanMode) {
				printf(_("Your number is %s\n"), fromArab2Roman(end));
			} else {
				printf(_("Your number is %d\n"), end);
			}
			break;
		}
		half = (end - start) / 2;

		if (romanMode) {
			printf(_("Is it bigger than %s?\n"), fromArab2Roman(start + half));
		} else {
			printf(_("Is it bigger than %d?\n"), start + half);
		}
		printf(_("Type %s or %s\n"), _("yes"), _("no"));
		scanf("%s", answer);

		if (strncmp(answer, _("yes"), strlen(_("yes"))) == 0) {
			start = start + half;
		}
		if (strncmp(answer, _("no"), strlen(_("no"))) == 0) {
			end = start + half;
		}
	}
	return 0;
}