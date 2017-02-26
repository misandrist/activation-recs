// Essentially a 6502-ish emulation of the non-tail-recursive
// statement of fibonacci.

#include <iostream>
#include <gmpxx.h>
#include <stack>

using namespace std;

// The word type for the stack.
typedef mpz_class fib_t;

// The stack itself.
typedef stack<fib_t> fib_s;

// The processor state. We use an implicit sp here, which is the top
// of st.
template  <typename T>
class pregs {
private:
    T _a;
    T _x;
    T _y;
    stack<T> _st;

    // Zero flag
    T _z;

    // Overflow flag
    T _v;

    // Minus flag
    T _m;

    // Set the flags based on the value.
    void _set_flags(const T &n);

    // Set the flags and overflow.
    void _set_flags(const T &n, bool v);

public:
    void lda(const T &v);
    void ldx(const T &v);
    void ldy(const T &v);

    // These return copies.
    T sta() const;
    T stx() const;
    T sty() const;

    void tax();
    void tay();
    void txa();
    void tya();

    void inx();
    void iny();

    void dex();
    void dey();

    void cpx(const T &v);

    void pha();
    void pla();

    // Overflow
    bool vs() const;
    bool vc() const;

    // Zero
    bool ne() const;
    bool eq() const;

    // Negative
    bool mi() const;
    bool pl() const;
};

template <typename T>
void pregs<T>::_set_flags(const T &n) {
    if (n == 0)
        _z = true;
    else
        _z = false;

    if (n < 0)
        _m = true;
    else
        _m = false;

    _v = false;
}

template <typename T>
void pregs<T>::_set_flags(const T &n, bool v) {
    _set_flags(n);
    _v = v;
}

template <typename T>
void pregs<T>::lda(const T &v) {
    _a = v;
    _set_flags(v);
}

template <typename T>
void pregs<T>:: ldx(const T &v) {
    _x = v;
    _set_flags(v);
}

template <typename T>
void pregs<T>::ldy(const T &v) {
    _y = v;
    _set_flags(v);
}

template <typename T>
T pregs<T>::sta() const {
    return _a;
}

template <typename T>
T pregs<T>::stx() const {
    return _x;
}

template <typename T>
T pregs<T>::sty() const {
    return _y;
}

template <typename T>
void pregs<T>::tax() {
    _x = _a;
    _set_flags(_x);
}

template <typename T>
void pregs<T>::tay() {
    _y = _a;
    _set_flags(_y);
}

template <typename T>
void pregs<T>::txa() {
    _a = _x;
    _set_flags(_a);
}

template <typename T>
void pregs<T>::tya() {
    _a = _y;
    _set_flags(_a);
}

template <typename T>
void pregs<T>::inx() {
    T _v0 = _x;
    _x++;

    _set_flags(_x, _x < _v0);
}

template <typename T>
void pregs<T>::iny() {
    T _v0 = _y;
    _y++;
    _set_flags(_y, _y < _v0);
}

template <typename T>
void pregs<T>::dex() {
    T _v0 = _x;
    _x--;
    _set_flags(_x, _x > _v0);
}

template <typename T>
void pregs<T>::dey() {
    T _v0 = _y;
    _y--;
    _set_flags(_y, _y > _v0);
}

template <typename T>
void pregs<T>::pha() {
    _st.push(_a);
}

template <typename T>
void pregs<T>::pla() {
    _a = _st.top();
    _st.pop();
    _set_flags(_a);
}

template <typename T>
void pregs<T>::cpx(const T &v) {
    T c(_x - v);

    _set_flags(c);
}

template <typename T>
bool pregs<T>::ne() const {
    return !_z;
}

template <typename T>
bool pregs<T>::eq() const {
    return _z;
}

template <typename T>
bool pregs<T>::mi() const {
    return _m;
}

template <typename T>
bool pregs<T>::pl() const {
    return _m;
}


// Calculate the non-tail-recursive Fibonacci of n using the 6502
// execution model.
fib_t fib(const fib_t &n);

fib_t fib(const fib_t &n) {
    pregs<fib_t> regs;

    // Guard case: 0 -> 0, 1 -> 1.
    if (n <= 1)
        return n;

    // Otherwise, return f (n - 1) + f (n - 2)

    // Load n into x
    regs.ldx(n);

    regs.cpx(2);
    // While x >= 2:
    while (regs.pl()) {
        // Decrement x and push activation record for f(n - 1)
        regs.dex();

        regs.txa();
        regs.pha();

        // Decrement x and push activation record for f(n - 2)
        regs.dex();

        // Push activation record for f(n - 2)
        regs.txa();
        regs.pha();
    }

    // All activation records have been pushed, so now we start
    // popping and evaluating.
}

int main() {

    for (fib_t f=0; f < 10; f++)
        cout << "Fib " << f << ": " << fib(f) << endl;

    return 0;
}
