#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h> //INT_MAX

// naive dynamic programming solution (O(n³))


int ChainMM(unsigned dims[], int n) {

    unsigned M[n][n];
    int bracket[n][n];
    int i, j, k, L, cost;

    for (i=1; i<n; i++)
        M[i][i] = 0;

    for (L=2; L<n; L++) {        // for every length
        for (i=1; i<n-L+1; i++)  // consider all subsequences
        {
            j = i+L-1;
            M[i][j]= INT_MAX;    // initialize cost to max
            for (k=i; k<=j-1; k++) {
                cost = M[i][k] +   //unit: 1 scalar mult
                       M[k+1][j] + 
                       dims[i-1]*dims[k]*dims[j];
                if (cost < M[i][j]) {
                    M[i][j]=cost;  //update min(cost)
                    bracket[i][j]=k;  //update bracket matrix
                }
            
            }

        }
    }

    return M[1][n-1];

}


int main(int argc, char const *argv[])
{
  //number of matrices
  unsigned n, maxdim;
  sscanf(argv[1], "%u", &n);
  sscanf(argv[2], "%u", &maxdim);
  
  //initialize rand
  srand(time(0));

  // initialize dimensions array
  unsigned dims[n+1];

  for (unsigned i = 0; i <=n; i++) { 
      dims[i] = rand()%maxdim+1;
    //  printf("%u \n", dims[i]);
    };

    int x = ChainMM(dims, n);

    for (unsigned i=0; i<n; i++) {
        printf("A[%d] : %d \tx %d\n", i, dims[i], dims[i+1]);
    }
    printf("total cost: %d ops \n", x);
    
    
    return 0;
}
