int strnlen(char *s, int maxsize) {
	int i=0;
	while (!(s[i] == '\0' || i == maxsize)) {
		i++;
	}
	return i;
}
int putchar(char c) {
		char *addr = (char *) 0x10000000;
		if (c == '\r') {
			*addr = '\r';
			*addr = '\n';
			return 0;
		}
		*addr = c;
		return 0;
}

char getch() {
		char *addr = (char *) 0x10000000;
		for (;;) {
			if ((addr[5] & 1) != 0) {
				char c = *addr;
				//echo character
				putchar(c);
				return c;
			}
		}
}

void getn(char *buf, int n) {
	char ch = '\0';
	int i = 0;
	while (ch != '\r' && i+1 < n) {
		ch = getch();
		buf[i] = ch;
		i++;
	}
	buf[i] = '\0';
}

int puts(char *buf) {
	for (int i = 0;buf[i] != '\0';i++) {
		putchar(buf[i]);
	}
	return 0;
}
