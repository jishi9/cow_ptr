cow_ptr
=======

Copy-on-write pointer for C++

Basic usage
===========
    cow_ptr<int> cp(new int(0));
    (*cp)++;
    (*cp)++;
    // *cp == 2

    cow_ptr<int> cp2(cp);
    (*cp)++;
    (*cp)++;
    // *cp == 4
    // *cp2 == 2

Non-owning version
==================
    int x = 3;
    cow_ptr<int> cp(&x, false);
    (*cp)++;
    (*cp)++;
    // *cp == 5
    // *x == 3
