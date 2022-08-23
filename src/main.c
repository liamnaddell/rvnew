int putch(char c) {
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
				putch(c);
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

void putstr(char *buf) {
	for (int i = 0;buf[i] != '\0';i++) {
		putch(buf[i]);
	}
}

extern char hiasm;

void kmain() {
	char buf[50];
	putstr(&hiasm);
	char *str = "hi from c\n";
	putstr(str);
	for (;;) {
		getn(buf,50);
		
	}
}
