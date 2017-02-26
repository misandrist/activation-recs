#include <iostream>
#include <memory>
#include <cstdint>

typedef uint64_t fact_t;
typedef uint64_t fp_t;

fact_t factorial(fact_t n);
fact_t factoral_flat(fact_t n);

struct fact_frame {
    fact_t n;
    fp_t loc;
};

template <typename T>
class Stack {
private:
    std::size_t          top;
    std::size_t          max;
    std::unique_ptr<T[]> arr;
public:
    Stack<T>(std::size_t size=2048) {
        top = 0;
        max = size;
        arr = std::make_unique<T[]>(size);
    }
    bool pop(T& val) {
        if (top == 0) {
            return false;
        }
        else {
            val = arr[--top];
            return true;
        }
    }
    bool push(T& val) {
            if (top == max) {
            return false;
        }
        else {
            arr[top++] = val;
            return true;
        }
    }
    bool empty() {
        return top == 0;
    }
    std::size_t size() {
        return top;
    }
};

fact_t factorial(fact_t n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

fact_t factoral_flat(fact_t n) {
    Stack<fact_frame> s;
    fact_frame f; f.n = n; f.loc = 0; s.push(f);
    fact_t ret = 1;
    while (!s.empty()) {
        s.pop(f);
        switch(f.loc) {
        case 0:
            if (f.n <= 1)
                ret = 1;
            else {
                // Professor's comments:
                //
                // You are pushing two stack frames corresponding to
                // the recursive calls, but you don't add the return
                // values anywhere. You're going to have to save the
                // return value from the first call while you do the
                // second, and then after returning from the second,
                // add the two return values to become the return
                // value for your current call. So you will need to
                // remember at least three locations: about to do
                // first call,between two calls, after both calls. And
                // you will need to put have another lint on your
                // stack frame to remember the return value from the
                // first call.
                f.loc = 1; s.push(f);
                fact_frame g; g.n = f.n - 1; g.loc = 0;
                s.push(g);
            }
            break;
        case 1:
            ret *= f.n;
            break;
        }
    }
    return ret;
}

int main() {
    std::cout << factorial(15) << std:: endl << factoral_flat(15) << std::endl;
    return 0;
}
