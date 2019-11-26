# algorithms
Homeworks for algorithms exam

## general comments

I moved most repeated functions in a single utility.c/utility.h library, changing the Makefile accordingly.

## Strassen

Code works, I had a few problems with optimized code, but they are solved. I modified correctness check to perform multiple checks between different matrices.
See legend in run file for details.

## Matrix chain multiplication

The code provided worked. I commented various functions to understand better the process, reformatted the output. For some reason, optimized solution does not scale linearly with N, for N>16. This could be explained by the code optimization itself.

## Sorting

<add comments>
  
## Heap

<add comments>

## Dijkstra

Heap implementation used c++ STL std::PriorityQueue, that is internally implemented as binary heap.

Times are average of 10 runs, in msec.

Number of nodes | avg. Number of edges| VectorTime | HeapTime

```
64   |    2.048 K  |    0.113  |    0.097
128  |    3.276 K  |    0.248  |    0.128
256  |   13.107 K  |    1.084  |    0.557
512  |   52.428 K  |    2.508  |    1.026
1024 |  209.732 K  |    7.710  |    1.714
2048 |  838.835 K  |    33.257 |    6.569
4096 |    3.355 M  |   116.696 |   25.028
8192 |   13.421 M  |   391.842 |   96.493
16384|   53.687 M  |  1437.601 |  389.118
32768|  214.748 M  |  5628.451 | 1590.324

```
[Chart](dijkstraSpeed.png)