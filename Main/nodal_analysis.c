
/*

	The algorithm uses linear algebra methods to elaborate the 
	nodal analysis method, called node-voltage analysis, to
	determine the potential difference between the nodes in an
	electrical circuit.

	The nodal analysis metod used in this program uses the hypothesis
	of current controlled sides of the electrical circuit.

	Another hypothesis is that the electric circuit is linear and it is
	built by single bipolar elements.

	It is applied on a circuit of 3 nodes.

*/

#include <stdio.h>

#define NODES 3

// Function to get cofactor of mat[p][q] in temp[][]. n is
// current dimension of mat[][]
void getCofactor(int mat[NODES][NODES], int temp[NODES][NODES], int p,
                 int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. */
int determinantOfMatrix(int mat[NODES][NODES], int n)
{
    int D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return mat[0][0];
 
    int temp[NODES][NODES]; // To store cofactors
 
    int sign = 1; // To store sign multiplier
 
    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}

int main(int argc, char * argv[]){

	int nodal_matrix[NODES][NODES];
	int i,j, k, nRes, isOK;
	int current_injections[NODES];
	float voltages[NODES];
	int resistance;
	int Dx[NODES][NODES], Dy[NODES][NODES], Dz[NODES][NODES];
	int dx, dy, dz, nodal;

	for(i=0; i<NODES; i++){
		nodal_matrix[i][i]=0;
	}

	for(i=0; i<NODES; i++){
		printf("How many resistances do arrive on node number %d?\n", i+1);
		scanf("%d", &nRes);
		for(j=0; j<nRes; j++){
			printf("Insert resistance number %d:\n", j+1);
			scanf("%d", &resistance);
			nodal_matrix[i][i] += resistance;
		}
		printf("\n");
	}
	printf("\n");

	for(i=0; i<NODES-2; i++){
		for(j=i+1; j<NODES; j++){
			printf("Insert the resistance between node number %d and %d:\n", i+1, j+1);
			scanf("%d", &nodal_matrix[i][j]);
		}
	}
	printf("\n");

	printf("Insert the resistance between node number 2 and 3:\n");
	scanf("%d", &resistance);
	nodal_matrix[1][2] = resistance;

	for(i=0; i<NODES; i++){
		for(j=0; j<NODES; j++){
			if(i!=j){
				nodal_matrix[j][i] = nodal_matrix[i][j];
			}
		}
	}

	printf("The nodal matrix of coefficients is:\n");
	printf("\n");
	for(i=0; i<NODES; i++){
		for(j=0; j<NODES; j++){
			printf("%2d ", nodal_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Insert now the current injected in the different nodes:\n");
	for(i=0; i<NODES; i++){
		printf("Current injected in node number %d:\n", i+1);
		scanf("%d", &current_injections[i]);
	}

	printf("The vector of current injections is:\n");
	printf("[ ");
	for(i=0; i<NODES; i++)
		printf("%2d ", current_injections[i]);
	printf("]");
	printf("\n");

	/* Calcuation of the Dx Dy and Dz matrices to utilize the Cramer rule */

	for(i=0; i<NODES; j++){
		for(j=0; j<NODES; j++){
			Dx[i][j] = nodal_matrix[i][j];
		}
	}
	for(i=0; i<NODES; i++){
		Dx[i][0] = current_injections[i];
	}

	printf("Dx matrix is:\n");
	for(i=0; i<NODES; i++){
		for(j=0; j<NODES; j++){
			printf("%d ", Dx[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for(i=0; i<NODES; j++){
		for(j=0; j<NODES; j++){
			Dy[i][j] = nodal_matrix[i][j];
		}
	}
	for(i=0; i<NODES; i++){
		Dy[i][1] = current_injections[i];
	}

	printf("Dy matrix is:\n");
	for(i=0; i<NODES; i++){
		for(j=0; j<NODES; j++){
			printf("%d ", Dy[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for(i=0; i<NODES; j++){
		for(j=0; j<NODES; j++){
			Dz[i][j] = nodal_matrix[i][j];
		}
	}
	for(i=0; i<NODES; i++){
		Dz[i][2] = current_injections[i];
	}

	printf("Dz matrix is:\n");
	for(i=0; i<NODES; i++){
		for(j=0; j<NODES; j++){
			printf("%d ", Dz[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	/* Determinants */

	dx = determinantOfMatrix(Dx, NODES);
	dy = determinantOfMatrix(Dy, NODES);
	dz = determinantOfMatrix(Dz, NODES);
	nodal = determinantOfMatrix(nodal_matrix, NODES);

	/* Calculate the voltages */

	voltages[0] = (float)dx/nodal;
	voltages[1] = (float)dy/nodal;
	voltages[2] = (float)dz/nodal;

	/* Print the results */

	printf("The voltages wanted are:\n");
	printf("[ ");
	for(i=0; i<NODES; i++){
		printf("%f ", voltages[i]);
	}
	printf("]");
	printf("\n");

	return 0;
}


