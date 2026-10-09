# Jeff Erickson's Algorithms, my solutions

My own C++ solutions to exercises from [*Algorithms* by Jeff Erickson](https://jeffe.cs.illinois.edu/teaching/algorithms/) (free online). Work in progress, adding chapters as I go.

The book isn't included here, get it from the link above.

## What's here

| Topic | Exercises |
|---|---|
| [Basic graph algorithms](Graphs/Basic%20Graph%20Algorithms) | 14, 15, 16, 17A, 17B, 18, 19A, 19BC |
| [Depth-first search](Graphs/DFS) | 9, 12 |
| [Shortest paths](Graphs/SSSP) | 2, 3, 11, 12, 13, 14 (+2 variants), 18, 19A, 19B |

Files are named after the exercise number, e.g. `Q9.cpp`.

## Running one

```sh
g++ -std=c++17 -O2 Graphs/SSSP/Q2.cpp -o q2 && ./q2
```

Each file is a standalone program that reads its input from stdin. They all compile cleanly with `g++ -std=c++17`, but they're not run against an official test suite, so treat the answers as mine and not as the reference.
