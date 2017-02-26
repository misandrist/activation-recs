#include <iostream>
#include <gmpxx.h>
#include <stack>

using namespace std;

typedef mpz_class fib_t;
typedef stack<fib_t> fib_s;

fib_t fib(fib_t n);

fib_t fib(fib_t n) {
    fib_s fs;

    if (n == 0)
        return 0;

    fs.push(0);
    fs.push(1);

    while (n > 1) {
        n -= 1;

        fib_t l = fs.top();
        fs.pop();
        fib_t k= fs.top();
        fs.pop();

        fs.push(l);
        fs.push(k + l);
    }
    return fs.top();
}

int main() {

    for (fib_t f=0; f < 1000; f++)
        cout << "Fib " << f << ": " << fib(f) << endl;

    return 0;
}
