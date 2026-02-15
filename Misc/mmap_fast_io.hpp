#include <sys/mman.h> // POSIX
#include <sys/stat.h>
#include <unistd.h>

/**
 * read_int() to read a int
 */

char *buf;
size_t len, pos = 0;

inline int read_int() {
    int x = 0;
    while (pos < len && buf[pos] < '0') pos++;
    while (pos < len && buf[pos] >= '0') {
        x = x * 10 + (buf[pos] & 15);
        pos++;
    }
    return x;
}

/**
 *
 */
static char outbuf[1 << 20]; // 1MB
static size_t outpos = 0;

inline void write_int(long long x) {
    if (x == 0) {
        outbuf[outpos++] = '0';
        return;
    }
    char s[24];
    int n = 0;
    while (x) {
        s[n++] = '0' + (x % 10);
        x /= 10;
    }
    while (n--) outbuf[outpos++] = s[n];
}

inline void write_char(char c) {
    outbuf[outpos++] = c;
}

int main() {
    struct stat st;
    fstat(STDIN_FILENO, &st);
    len = st.st_size;
    buf = (char *)mmap(nullptr, len, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    // solve();
    write(STDOUT_FILENO, outbuf, outpos);
}

/**
 *
 */
