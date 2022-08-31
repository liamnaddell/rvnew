int strnlen(char *s, int maxsize) {
	int i=0;
	while (!(s[i] == '\0' || i == maxsize)) {
		i++;
	}
	return i;
}

int strlen(char *s) {
	int i=0;
	while (!(s[i] == '\0')) {
		i++;
	}
	return i;
}

int putchar(char c) {
		char *addr = (char *) 0x10000000;
		*addr = c;
		return 0;
}

char getch() {
		char *addr = (char *) 0x10000000;
		for (;;) {
			if ((addr[5] & 1) != 0) {
				char c = *addr;
				//echo character
				if (c == '\r') {
					c = '\n';
				}
				putchar(c);
				return c;
			}
		}
}

void getn(char *buf, int n) {
	char ch = '\0';
	int i = 0;
	while (ch != '\n' && i+1 < n) {
		ch = getch();
		buf[i] = ch;
		i++;
	}
	buf[i] = '\0';
}

int puts_nonl(char *buf) {
	int i;
	for (i = 0;buf[i] != '\0';i++) {
		putchar(buf[i]);
	}
	return 0;
}

int puts(char *buf) {
	int rval = puts_nonl(buf);
	putchar('\n');
	return 0;
}

int streq(char *s1, char *s2) {
	int i = 0;
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (len1 != len2) {
		return 0;
	}

	while (*s1 != '\0') {
		if (*s1 != *s2) {
			return 0;
		}
		s1++;
		s2++;
	}
	return 1;
}
int strcmp(char *s1, char *s2) {
	return streq(s1,s2);
}


//redo in assembly
void *memcpy(char *dest, char *src, long unsigned int n) {
	for (int i = 0; i < n; i++) {
		*dest=*src;
		dest++;
		src++;
	}
	return dest;
}
