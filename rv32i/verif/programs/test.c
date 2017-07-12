asm (
    "_entry:\n"
    "   li     sp,     0x1000\n"
    "   j      main\n"
);

int a = (unsigned const)'0';

int add1(int a);
void writes(char const* const str);

void main(void) {
    int i, j;

    for (j = 0; j < 4; ++j) {
        for (i = 0; i < j; ++i) {
            writes((char const *const)&a);
            a += 1;

            writes("Hello World!\n");
        }
    }

    writes("From the Merlin RV32I test program\n");

    *(unsigned *const)0xfffffffc = 0; // end test
}

int add1(int a) {
    return a + 1;
}

void writes(char const* str) {
    char const *word_addr;
    unsigned word;
    unsigned index;
    unsigned c;
    
    word_addr = (char const *const)((unsigned const)str & ~0x3);
    word = *(unsigned const *const)word_addr;
    do {
        index     = (unsigned const)str &  0x3;

        if (index == 0) {
            word_addr = (char const *const)((unsigned const)str & ~0x3);
            word = *(unsigned const *const)word_addr;
        }

        c = word >> (index << 3);

        if (c != '\0') {
            *(unsigned *const)0x80000000 = c;
            ++str;
        }
    } while (c != '\0');
}

