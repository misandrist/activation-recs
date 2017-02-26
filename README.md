# Problem  Statement

Model a non-tail-recursive implementation of Fibonacci and/or factorial.

LadyClaire:

> The function definition I'm using goes::

    int fibonacci(int n) {
        if (n <=1)
           return 1;
       else
           return fibonacci(n-1) + fibonacci(n-2);
    }

In `lady-claire-01.cc`, the professor's comments on::

    f.loc = 1; s.push(f);
    fact_frame g; g.n = f.n - 1; g.loc = 0;
    s.push(g);

are:

> You are pushing two stack frames corresponding to the recursive
> calls, but you don't add the return values anywhere. You're going to
> have to save the return value from the first call while you do the
> second, and then after returning from the second, add the two return
> values to become the return value for your current call. So you will
> need to remember at least three locations: about to do first call,
> between two calls, after both calls. And you will need to put have
> another lint on your stack frame to remember the return value from
> the first call.

and, with regard to activation records:

> A push should be the last thing you do before looping. This
> corresponds to a function call: pushing a stack frame on the stack
> and jumping to the code of the function. In particular, you
> shouldn't have two calls to push in the same iteration of the
> loop. An exception would be when you need to make two recursive
> calls, but the second call doesn't depend on the outcome of the
> first, for example if your function has a void return type and it
> only performs side-effects (e.g., printing something out or updating
> global variables). In that case, you could just push both frames on
> the stack before continuing your loop. (See the Tower of Hanoi
> example from the book.)
