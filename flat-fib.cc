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
    fib_t l = 1;
    for (fib_t i=2; i<n; i++) {
        fs.push(fs.top() + l);
        l = fs.top();
    }

    cout << "Stack size: " << fs.size() << endl;
    return fs.top();
}

int main() {

    for (fib_t f=0; f < 1000; f++)
        cout << "Fib " << f << ": " << fib(f) << endl;

    return 0;
}
