#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
	int j = 0;
	char **new;
	int count_lett;

	if (!s)
		return NULL;
	new = (char **)malloc(sizeof(char *) * (mx_count_words(s, c) + 1));
	for (int i = 0; s[i]; i++) {
		if (s[i] != c) {
			count_lett = mx_count_letters(&s[i], c);
			new[j] = mx_strnew(count_lett);
			for (int k = 0; k < count_lett; k++) {
				new[j][k] = s[i];
				i++;
			}
			j++;
		}
	}
	new[j] = NULL;
	return new;
}
