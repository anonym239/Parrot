/* Parrot OS - Kernel v0.1: Textbildschirm, Tastatur, kleine Shell */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VGA ((volatile u16 *)0xB8000)
#define COLS 80
#define ROWS 25

static int cx = 0, cy = 0;
static u8 color = 0x0A; /* hellgruen auf schwarz */

static inline u8 inb(u16 p) { u8 v; __asm__ volatile("inb %1,%0" : "=a"(v) : "Nd"(p)); return v; }
static inline void outb(u16 p, u8 v) { __asm__ volatile("outb %0,%1" : : "a"(v), "Nd"(p)); }

static void clear(void) {
    for (int i = 0; i < COLS * ROWS; i++) VGA[i] = (color << 8) | ' ';
    cx = cy = 0;
}

static void scroll(void) {
    for (int i = 0; i < COLS * (ROWS - 1); i++) VGA[i] = VGA[i + COLS];
    for (int i = 0; i < COLS; i++) VGA[COLS * (ROWS - 1) + i] = (color << 8) | ' ';
    cy = ROWS - 1;
}

static void putc(char c) {
    if (c == '\n') { cx = 0; cy++; }
    else if (c == '\b') { if (cx > 0) { cx--; VGA[cy * COLS + cx] = (color << 8) | ' '; } }
    else { VGA[cy * COLS + cx] = (color << 8) | (u8)c; cx++; }
    if (cx >= COLS) { cx = 0; cy++; }
    if (cy >= ROWS) scroll();
}

static void puts(const char *s) { while (*s) putc(*s++); }

static int streq(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return *a == *b;
}

static int starts(const char *s, const char *p) {
    while (*p) { if (*s++ != *p++) return 0; }
    return 1;
}

/* US-Layout, Scancode Set 1 */
static const char map[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' '
};

static char getchar(void) {
    for (;;) {
        if (inb(0x64) & 1) {
            u8 sc = inb(0x60);
            if (sc & 0x80) continue;      /* Taste losgelassen */
            if (sc < 128 && map[sc]) return map[sc];
        }
    }
}

static void reboot(void) {
    while (inb(0x64) & 2) {}
    outb(0x64, 0xFE);
}

void kernel_main(void) {
    clear();
    puts("Parrot OS v0.1\n");
    puts("Tippe 'help' fuer Befehle.\n\n");

    char buf[80];
    for (;;) {
        puts("parrot> ");
        int n = 0;
        for (;;) {
            char c = getchar();
            if (c == '\n') { putc('\n'); break; }
            if (c == '\b') { if (n > 0) { n--; putc('\b'); } continue; }
            if (n < 78) { buf[n++] = c; putc(c); }
        }
        buf[n] = 0;

        if (streq(buf, "help"))
            puts("help  clear  about  echo <text>  reboot\n");
        else if (streq(buf, "clear")) clear();
        else if (streq(buf, "about"))
            puts("Parrot OS v0.1 - mein eigenes Betriebssystem\n");
        else if (starts(buf, "echo ")) { puts(buf + 5); putc('\n'); }
        else if (streq(buf, "reboot")) reboot();
        else if (n > 0) puts("Unbekannter Befehl\n");
    }
}
