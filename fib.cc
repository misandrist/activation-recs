#include <cstdio>
#include <cstdint>
#include <stack>

typedef uint64_t fib_t;
fib_t fib(fib_t n);

fib_t fib(fib_t n) {
    fib_t a = 0;
    fib_t p = 1;
    fib_t s = 1;
    while (n > 1) {
        n -= 1;
        a = p + s;
        p = s;
        s = a;
    }
    return s;
}

int main() {

    for (fib_t f=0; f < 20; f++)
        printf("Fib %ld: %ld\n", f, fib(f));

    return 0;
}
