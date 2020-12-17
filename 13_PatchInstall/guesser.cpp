#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

#define DOMAIN(x) "\"" #x "\""
#define _(STRING) gettext(STRING)

int main(int argc, char **argv) {

	setlocale (LC_ALL, "");
	bindtextdomain ("guesser", DOMAIN(CMAKE_INSTALL_FULL_LOCALEDIR));
	textdomain("guesser");

	int start = 1, end = 100, half;
	printf(_("Guess the number from 1 to 100\n"));
	char answer[256];

	while (true) {
		if (end - start < 2) {
			printf(_("Your number is %d\n"), end);
			break;
		}
		half = (end - start) / 2;
		printf(_("Is it bigger than %d?\n"), start + half);
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
