// Essentially a 6502-ish emulation of the non-tail-recursive
// statement of fibonacci.

#include <iostream>
#include <gmpxx.h>
#include <stack>
#include <cstdint>

using namespace std;

// The word type for the stack.
// typedef mpz_class fib_t;
typedef int64_t fib_t;

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
    bool _z;

    // Overflow flag
    bool _v;

    // Minus flag
    bool _m;

    //  Carry flag
    bool _c;

    // Set the flags based on the value.
    void _set_flags(const T &n, bool v, bool c);

public:
    pregs() :
        _a(0), _x(0), _y(0), _st(),
        _z(false), _v(false), _m(false), _c(false) {}

    void lda(const T &v);
    void ldx(const T &v);
    void ldy(const T &v);

    // These return copies.
    void sta(T &v);
    void stx(T &v);
    void sty(T &v);

    // Add with carry from memory to (a).
    void adc(const T &v);

    void tax();
    void tay();
    void txa();
    void tya();

    void inx();
    void iny();

    void dex();
    void dey();

    void cmp(const T &v);
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

  // Carry
    bool cs() const;
    bool cc() const;
};

template <typename T>
void pregs<T>::_set_flags(const T &n, const bool v, const bool c) {
    _z = false;
    _m = false;

    if (n == 0){
        _z = true;
    }   else
        _z = false;

    if (n < 0)
        _m = true;
    else
        _m = false;

    _v = v;
    _c = c;
}

template <typename T>
void pregs<T>:: lda(const T &v) {
    _a = v;
    _set_flags(v, false, false);
}

template <typename T>
void pregs<T>:: ldx(const T &v) {
    _x = v;
    _set_flags(v, false, false);
}

template <typename T>
void pregs<T>::ldy(const T &v) {
    _y = v;
    _set_flags(v, false, false);
}

template <typename T>
void pregs<T>::sta(T &v) {
    v = _a;
    _set_flags(_a, false, false);
}

template <typename T>
void pregs<T>::stx(T &v) {
    v = _x;
    _set_flags(_x, false, false);
}

template <typename T>
void pregs<T>::sty(T &v) {
    v = _y;
    _set_flags(_y, false, false);
}

template <typename T>
void pregs<T>::adc(const T &v) {
    _a += v;
    _set_flags(_a, _a >= v, false);
}

template <typename T>
void pregs<T>::tax() {
    _x = _a;
    _set_flags(_x, false, false);
}

template <typename T>
void pregs<T>::tay() {
    _y = _a;
    _set_flags(_y, false, false);
}

template <typename T>
void pregs<T>::txa() {
    _a = _x;
    _set_flags(_a, false, false);
}

template <typename T>
void pregs<T>::tya() {
    _a = _y;
    _set_flags(_a, false, false);
}

template <typename T>
void pregs<T>::inx() {
    T _v0 = _x;
    _x++;

    _set_flags(_x, _x < _v0, false);
}

template <typename T>
void pregs<T>::iny() {
    T _v0 = _y;
    _y++;
    _set_flags(_y, _y < _v0, false);
}

template <typename T>
void pregs<T>::dex() {
    T _v0 = _x;
    _x--;
    _set_flags(_x, _x > _v0, false);
}

template <typename T>
void pregs<T>::dey() {
    T _v0 = _y;
    _y--;
    _set_flags(_y, _y > _v0, false);
}

template <typename T>
void pregs<T>::pha() {
    _st.push(_a);
    _set_flags(_a, false, false);
}

template <typename T>
void pregs<T>::pla() {
    _a = _st.top();
    _st.pop();
    _set_flags(_a, false, false);
}

template <typename T>
void pregs<T>::cmp(const T &v) {
    _set_flags(_a - v, false, v <= _a);
}

template <typename T>
void pregs<T>::cpx(const T &v) {
    _set_flags(_x - v, false, v <= _x );
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
    return !_m;
}

template <typename T>
bool pregs<T>::cs() const {
    return _c;
}

template <typename T>
bool pregs<T>::cc() const {
    return !_c;
}

// Calculate the non-tail-recursive Fibonacci of n using the 6502
// execution model.
fib_t fib(const fib_t &n);

fib_t fib(const fib_t &n) {
    pregs<fib_t> regs;

    // Guard case: 0 -> 0, 1 -> 1.
    if (n <= 1)
        return n;

    // Otherwise, calculate fib(n) using fib n = fib (n - 1)  + fib (n - 2)

    regs.ldx(n);
    do {
        // Push activation record for fib (n - 1)
        regs.dex();
        regs.txa();
        regs.pha();

        // Decrement x and push activation record for fib (n - 2)
        regs.dex();
        regs.txa();
        regs.pha();

        regs.cpx(1);
        // Continue while x is greater than 1.
    } while (regs.cs() && regs.ne());

    // All activation records have been pushed, so now we start
    // popping and evaluating. This is exactly the same loop as above,
    // but doing the reduction instead of the expansion.

    // Our memory locations. Pretend they're initialized.
    fib_t p(0), s(1);

    // Reload x so we know when to stop.
    regs.ldx(n);
    do {
        // Decrement x and pop activation record.
        regs.pla();

        // For 0 or 1, we're already set.
        if(regs.eq()) {
            goto cont;
        }

        // If we're at 1, we just store a in s.
        regs.cmp(1);
        if(regs.eq()) {
            goto cont;
        }

        // Otherwise, we need to add p and s, store the old s in p,
        // and store the new sum in s.
        regs.lda(p);
        regs.ldy(s);
        regs.sty(p);
        regs.adc(s);
        regs.sta(s);

  cont:
        regs.dex();
        regs.cmp(1);
    } while (regs.cs() && regs.ne());

    // At this point, s should have fib(n)
    return s;
}

int main() {

    for (fib_t f=0; f < 10; f++)
        cout << "Fib " << f << ": " << fib(f) << endl;

    return 0;
}
