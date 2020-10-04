#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void getFileInfo(char *filename, int *nlines, int *ncolumns) {
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	char *buffer = (char *) malloc(sizeof(char) * size);
	fseek(fp, 0, SEEK_SET);
	int lines = 0, columns = 0;
	while(fgets(buffer, size, fp)) {
		lines++;
		columns = strlen(buffer) > columns ? strlen(buffer) : columns;
	}
	free(buffer);
	fclose(fp);
	*nlines = lines;
	*ncolumns = columns + 1;
}


char **readFile(char *filename, int *maxlines, int *maxcolumns) {
	getFileInfo(filename, maxlines, maxcolumns);
	char **buffer = (char **) malloc((*maxlines) * sizeof(char *));
	for (int i = 0; i < *maxlines; ++i) {
		buffer[i] = (char *) malloc(sizeof(char) * (*maxcolumns));
	}
	FILE *fp = fopen(filename, "r");
	for (int i = 0; i < *maxlines; ++i) {
		fgets(buffer[i], *maxcolumns, fp);
		buffer[i][strlen(buffer[i]) - 1] = 0;
	}
	fclose(fp);
	return buffer;
}

void draw(WINDOW *win, char **buffer, int start, int end, int start_col,
	int end_col, int maxlines, int maxcolumns) {
	char *tmp = (char *) malloc(sizeof(char) * (maxcolumns + 1));
	for (int i = 0; i < maxlines; ++i) {
		if ((start <= i) && (i < end)) {
			if (strlen(buffer[i]) < (end_col - start_col)) {
				wprintw(win, "%d: %s\n", i, buffer[i]);
			} else {
				memset(tmp, 0, maxcolumns + 1);
			    memcpy(tmp, buffer[i] + start_col, end_col - start_col);
				wprintw(win, "%d: %s\n", i, tmp);
			}
		}
	}
	free(tmp);
}

void update_screen(WINDOW *win, char *filename, int ch, char **buffer, int *start,
	int *end, int *start_col, int *end_col,
	int maxlines, int maxcolumns) {

	int height, width;

	getmaxyx(win, height, width);
	wprintw(stdscr, "%s\n", filename);


	switch (ch) {
		case -1:
			break;
		case KEY_UP:
			*start = MAX(*start - 1, 0);
			*end = MAX(*end - 1, height);
			break;
		case KEY_DOWN:
		case ' ':
			*start = MIN(*start + 1, maxlines - height);
			*end = MIN(*end + 1, maxlines);
			break;
		case KEY_RIGHT:
			*start_col = MIN(*start_col + 1, maxcolumns - width);
			*end_col = MIN(*end_col + 1, maxcolumns);
			break;
		case KEY_LEFT:
			*start_col = MAX(0, *start_col - 1);
			*end_col = MAX(width, *end_col - 1);
			break;
		default:
			break;
	}
	draw(win, buffer, *start, *end, *start_col, *end_col, maxlines, maxcolumns);
}

void display(char *filename) {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int maxlines, maxcolumns;
	char **buffer = readFile(filename, &maxlines, &maxcolumns);

	int height, width;
	getmaxyx(stdscr, height, width);
	WINDOW *win = newwin(height - 1, width, 1, 0);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	whline(win, ACS_HLINE, width);
	getmaxyx(win, height, width);

	int start = 0, end = height, start_col = 0, end_col = width;

	update_screen(win, filename, -1, buffer, &start, &end, &start_col, &end_col, maxlines, maxcolumns);
	
	int ch = getch();
	while (ch != 'q') {
	    werase(stdscr);
	    werase(win);
		update_screen(win, filename, ch, buffer, &start, &end, &start_col, &end_col, maxlines, maxcolumns);
		wrefresh(stdscr);
		wrefresh(win);
		ch = getch();
	}

	for (int i = 0; i < maxlines; ++i) {
		free(buffer[i]);
	}
	free(buffer);
	endwin();
}

int main(int argc, char **argv) {
	char *filename = argv[1];
	display(filename);
	return 0;
}