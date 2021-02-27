void init(void) {
	unsigned long i;

	for (i = 0xa0000; i < 0xaffff; i++) {
		*((char *) i) = 0x0f;
	}

	for (;;);
}
