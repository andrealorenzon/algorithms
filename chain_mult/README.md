*For this assignment, the code has been provided.*

*Nonetheless, I also implemented it from scratch in my_cmm.c file. It can be compiled with make chain_my and run with chain.x A N, where A = number of matrices and N = max dimension size*


Matrix chain multiplication (or Matrix Chain Ordering Problem, MCOP) is an optimization problem that can be solved using dynamic programming. Given a sequence of matrices, the goal is to find the most efficient way to multiply these matrices. The problem is not actually to perform the multiplications, but merely to decide the sequence of the matrix multiplications involved.

There are many options because matrix multiplication is associative. In other words, no matter how the product is parenthesized, the result obtained will remain the same. For example, for four matrices A, B, C, and D, we would have:

    ((AB)C)D = (A(BC))D = (AB)(CD) = A((BC)D) = A(B(CD)).

However, the order in which the product is parenthesized affects the number of simple arithmetic operations needed to compute the product, that is the computational complexity. For example, if A is a 10 × 30 matrix, B is a 30 × 5 matrix, and C is a 5 × 60 matrix, then

    computing (AB)C needs (10×30×5) + (10×5×60) = 1500 + 3000 = 4500 operations, while
    computing A(BC) needs (30×5×60) + (10×30×60) = 9000 + 18000 = 27000 operations.

Clearly the first method is more efficient. With this information, the problem statement can be refined as "how to determine the optimal parenthesization of a product of n matrices?" Checking each possible parenthesization (brute force) would require a run-time that is exponential in the number of matrices, which is very slow and impractical for large n. A quicker solution to this problem can be achieved by breaking up the problem into a set of related subproblems. By solving subproblems once and reusing the solutions, the required run-time can be drastically reduced. This concept is known as dynamic programming. 

To begin, let us assume that all we really want to know is the minimum cost, or minimum number of arithmetic operations needed to multiply out the matrices. If we are only multiplying two matrices, there is only one way to multiply them, so the minimum cost is the cost of doing this. In general, we can find the minimum cost using the following recursive algorithm:

    Take the sequence of matrices and separate it into two subsequences.
    Find the minimum cost of multiplying out each subsequence.
    Add these costs together, and add in the cost of multiplying the two result matrices.
    Do this for each possible position at which the sequence of matrices can be split, and take the minimum over all of them.

For example, if we have four matrices ABCD, we compute the cost required to find each of (A)(BCD), (AB)(CD), and (ABC)(D), making recursive calls to find the minimum cost to compute ABC, AB, CD, and BCD. We then choose the best one. Better still, this yields not only the minimum cost, but also demonstrates the best way of doing the multiplication: group it the way that yields the lowest total cost, and do the same for each factor.

However, if we implement this algorithm we discover that it is just as slow as the naive way of trying all permutations! What went wrong? The answer is that we're doing a lot of redundant work. For example, above we made a recursive call to find the best cost for computing both ABC and AB. But finding the best cost for computing ABC also requires finding the best cost for AB. As the recursion grows deeper, more and more of this type of unnecessary repetition occurs.

One simple solution is called memoization: each time we compute the minimum cost needed to multiply out a specific subsequence, we save it. If we are ever asked to compute it again, we simply give the saved answer, and do not recompute it. Since there are about n2/2 different subsequences, where n is the number of matrices, the space required to do this is reasonable. It can be shown that this simple trick brings the runtime down to O(n3) from O(2n), which is more than efficient enough for real applications. This is top-down dynamic programming.

The following bottom-up approach computes, for each 2 ≤ k ≤ n, the minimum costs of all subsequences of length k using the costs of smaller subsequences already computed. It has the same asymptotic runtime and requires no recursion. 


    / Matrix A[i] has dimension dims[i-1] x dims[i] for i = 1..n
    MatrixChainOrder(int dims[])
    {
    // length[dims] = n + 1
    n = dims.length - 1;
    // m[i,j] = Minimum number of scalar multiplications (i.e., cost)
    // needed to compute the matrix A[i]A[i+1]...A[j] = A[i..j]
    // The cost is zero when multiplying one matrix
    for (i = 1; i <= n; i++)
        m[i, i] = 0;

    for (len = 2; len <= n; len++) { // Subsequence lengths
        for (i = 1; i <= n - len + 1; i++) {
            j = i + len - 1;
            m[i, j] = MAXINT;
            for (k = i; k <= j - 1; k++) {
                cost = m[i, k] + m[k+1, j] + dims[i-1]*dims[k]*dims[j];
                if (cost < m[i, j]) {
                    m[i, j] = cost;
                    s[i, j] = k; // Index of the subsequence split that achieved minimal cost
                }
            }
        }
    }
    }
