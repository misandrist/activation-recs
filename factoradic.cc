/** \mainpage C++ example of the Lehman permutation algorithm.
 *
 * (C) 2017 Claire Cavanaugh

 * \section intro_sec Introduction
 *
 * This is a demonstration of the Lehman permutation algorithm.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 Claire Cavanaugh, 2017 */

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

typedef unsigned long nat;
typedef unsigned long index;
typedef unsigned long fact;
typedef vector<nat> nats;
typedef vector<index> indices;

fact factorial(const nat n);
void perms(const nats &a);
void perm_print(const nats &a, indices &p);
void lehmer(indices &p, nat c);

int main() {
    nats a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    perms(a);
    return 0;
}

/**
 * Computes \f$n!\f$
 *
 * @param[in] n The number to compute the factorial of.
 */
fact factorial(const nat n) {
    /* Computes n! */
    nat f = 1; // Initialise to value of 0!
    for (nat i = 1; i <= n; i++) f *= i;
    return f;
}

/**
 * Prints the elements of \f$a\f$ in the order specified by \f$p\$f.
 *
 * @param[in] a The elements to print the permutation of.
 * @param[in] p The list of indices of \f$a\f$ to print in order.
*/
void perm_print(const nats &a, indices &p) {
    for (nats::const_iterator i = p.begin(); i != p.end(); i++) {
        std::cout << a[*i];
    }
    std::cout << std::endl;
}

/**
 * Prints every permutation of \f$a\f$.

 @param[in,out] a List of numbers to find and print every permutation of.
*/
void perms(const nats &a) {
    indices p(a.size(), 0);
    fact limit = factorial(a.size());

    for (nat c=0; c < limit; c++) {
        lehmer(p, c);
        perm_print(a, p);
    }
}

/**
 * Modifies the list of indices to contain the indices for the c-th
 * permutation of a set of items.
 *
 * @param [in,out] p A pre-allocated vector of indices.
 * @param [in] c The permutation to find.
 */
void lehmer(indices &p, nat c) {
    for (indices::iterator i = p.begin(); i != p.end(); i++) {
        index n = static_cast<index> (i - p.begin());

        /* What's going on here is a bit confusing so I'll go into
         * detail here. We're converting c to the corresponding lehmer
         * code (factoradic numeral). We do this using the standard
         * change-of-base algorithm, but the radix we mod by increases
         * by one for every iteration. For each place we calculate, we
         * also immediately run the "correction" to decode the lehmer
         * code into the indexes of the permutation. Then, as per the
         * change-of-base algorithm, we reduce c to its quotient with
         * the radix. */
        index r = c % (n + 1);
        *i = r;
        for (indices::iterator j = p.begin(); j < i; j++)
            if (*j >= r) (*j)++;
        c = c / (n + 1);
    }
}
