#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_CHAR_LIMIT 11 // + \0

typedef struct {
	char **start;
	int size;
	int writeIdx;
	int readIdx;
} cb_t;

cb_t *cb_create(int n);
int cb_put(cb_t *cb, char *line);
char *cb_get(cb_t *cb);
void cb_free(cb_t *cb);
int print_lines(cb_t *cb);
int load_lines(char *filename, cb_t *cb);

bool is_number(char *s) {
	for (int i = 0, n = strlen(s); i < n; i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

int main(int argc, char **argv) {

	int line_count = 10;
	char *filename = NULL;

	// TODO: Rewrite on switch
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0 && i < argc - 1) {
			// FIX: Simplify
			line_count = is_number(argv[i + 1]) ? atoi(argv[i + 1]) : 10;
		} else {
			filename = argv[i];
		}
	}

	if (line_count < 1) {
		printf("main: nespravny pocet radku");
		return 1;
	}

	cb_t *cb = cb_create(line_count);
	if (cb == NULL) {
		return 1;
	}

	if (load_lines(filename, cb) != 1) {
		return 1;
	}

	if (print_lines(cb) != 1) {
		return 1;
	}

	return 0;
}

void skip(FILE *file) {
	int c;

	while (c = fgetc(file), c != '\n' && c != EOF)
		;
	return;
}

int load_lines(char *filename, cb_t *cb) {
	if (filename == NULL) {
		// TODO: load from stdin
	}

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "load_lines: soubor se nepodarilo otevrit!");
		return 0;
	}

	char line[LINE_CHAR_LIMIT];
	while (fgets(line, sizeof(line), file) != NULL) {
		if (line[strlen(line) - 1] == '\n') {
			line[strcspn(line, "\n")] = 0;
			cb_put(cb, line);
		} else {
			cb_put(cb, line);
			skip(file);
		}
	}

	fclose(file);
	return 1;
}

int print_lines(cb_t *cb) {
	// NOTE: Do not know how to use cb_get
	int startIdx = cb->writeIdx;
	for (int i = 0; i < cb->size; i++) {
		int idx = (startIdx + i) % cb->size;
		if (cb->start[idx] != NULL) {
			printf("%s\n", cb->start[idx]);
		}
	}

	cb_free(cb);
	return 1;
}

int cb_put(cb_t *cb, char *line) {
	if ((cb->writeIdx + 1) % cb->size == cb->readIdx) {
		cb_get(cb);
	}

	strcpy(cb->start[cb->writeIdx], line);
	cb->writeIdx = (cb->writeIdx + 1) % cb->size;

	return 1;
}

char *cb_get(cb_t *cb) {
	if (cb->readIdx == cb->writeIdx) {
		return NULL;
	}

	char *line = cb->start[cb->readIdx];
	cb->readIdx = (cb->readIdx + 1) % cb->size;

	return line;
}

cb_t *cb_create(int n) {
	cb_t *cb =
		calloc(1, sizeof(cb_t) + (n * sizeof(char *)) + (n * LINE_CHAR_LIMIT));
	if (cb == NULL) {
		fprintf(stderr, "cb_create: nedostatek mista");
		return NULL;
	}

	// NOTE: skipping initial cb_t struct and casting to correct type
	cb->start = (char **)((char *)cb + sizeof(cb_t));
	cb->size = n;
	cb->writeIdx = 0;
	cb->readIdx = 0;

	// NOTE: skip line pointers
	char *curr = (char *)(cb->start) + (n * sizeof(char *));

	for (int i = 0; i < n; i++) {
		cb->start[i] = curr + (i * LINE_CHAR_LIMIT);
	}

	return cb;
}

void cb_free(cb_t *cb) { free(cb); }
