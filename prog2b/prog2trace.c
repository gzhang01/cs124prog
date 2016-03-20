/* Requires inputs ./strassen 0 dimension inputfile */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/* Set threshold for switching algorithms */
int N = 4;

/* Declarations */
int ** multmat(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d);
int ** add(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d, int I);
int ** tradmult(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d);
int ** stramult(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d);
int pad(int d);

/* Figures out how many extra rows and columns are needed to reach a power of 2 */
int pad(int dim)
{
	int padn = 2;
	while(padn < dim)
	{
		padn = 2*padn;
	}
	return padn;
}


/* Decides which multiplication method to use based on d */
int ** multmat(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d)
{
	if(d > N)
		return stramult(startx1, starty1, mat1, startx2, starty2, mat2, d);
	else
		return tradmult(startx1, starty1, mat1, startx2, starty2, mat2, d);
}

/* Add two matrices */
/* d holds the dimensions of the matrices (guaranteed to be square) and I holds either 1 or -1 to signify if the arrays are added or subtracted) */
int ** add(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d, int I)
{
	int ** sum;
	sum = malloc(sizeof(int*) * d);
	for(int v = 0; v < d; v++)
		sum[v] = malloc(sizeof(int) * d);

	for(int x = 0; x < d; x++)
	{
		for(int y = 0; y < d; y++)
		{
			sum[x][y] = mat1[x][y] + I * mat2[x][y];
		}
	}
	return sum;
}

/* Conventional matrix multiplication. Faster at some smaller d of n0 */
int ** tradmult(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d)
{
	/* Initialize a dxd matrix that will contain the result of the muliplication */
	int ** prodmat;
	prodmat = malloc(sizeof(int*) * d);
	for(int v = 0; v < d; v++)
		prodmat[v] = malloc(sizeof(int) * d);

	for(int x = 0; x < d; x++)
	{
		for(int y = 0; y < d; y++)
		{
			int elementsum = 0;
			for(int z = 0; z < d; z++)
			{
				elementsum = elementsum + mat1[startx1+x][starty1+z] * mat2[startx2+z][starty2+y];
			}
			prodmat[x][y] = elementsum;
		}
	}
	return prodmat;
}

/* Implement Strassen's Algorithm */
/* STILL HAS INDEX ERRORS */
int ** stramult(int startx1, int starty1, int ** mat1, int startx2, int starty2, int ** mat2, int d)
{
	int ** P1 = multmat(startx1, starty1, mat1, 0, 0, add(startx2+d/2, starty2, mat2, startx2+d/2, starty2+d/2, mat2, d/2, -1), d/2);
	int ** P2 = multmat(0, 0, add(startx1, starty1, mat1, startx1+d/2, starty1, mat1, d/2, 1), startx2+d/2, starty2+d/2, mat2, d/2);
	int ** P3 = multmat(0, 0, add(startx1, starty1+d/2, mat1, startx2+d/2, starty2+d/2, mat1, d/2, 1), startx2, starty2, mat2, d/2);
	int ** P4 = multmat(startx1+d/2, starty1+d/2, mat1, 0, 0, add(startx2, starty2+d/2, mat2, startx2, starty2, mat2, d/2, -1), d/2);
	int ** P5 = multmat(0, 0, add(startx1, starty1, mat1, startx1+d/2, starty1+d/2, mat1, d/2, 1), 0, 0, add(startx2, starty2, mat2, startx2+d/2, starty2+d/2, mat2, d/2, 1), d/2);
	int ** P6 = multmat(0, 0, add(startx1+d/2, starty1, mat1, startx1+d/2, starty1+d/2, mat1, d/2, -1), 0, 0, add(startx2, starty2+d/2, mat2, startx2+d/2, starty2+d/2, mat2, d/2, 1), d/2);
	int ** P7 = multmat(0, 0, add(startx1, starty1, mat1, startx1, starty1+d/2, mat1, d/2, -1), 0, 0, add(startx2, starty2, mat2, startx2+d/2, starty2, mat2, d/2, 1), d/2);

	int ** Q1 = add(0, 0, add(0, 0, add(0, 0, P5, 0, 0, P4, d/2, 1), 0, 0, P2, d/2, -1), 0, 0, P6, d/2, 1);
	int ** Q2 = add(0, 0, P1, 0, 0, P2, d/2, 1);
	int ** Q3 = add(0, 0, P3, 0, 0, P4, d/2, 1);
	int ** Q4 = add(0, 0, add(0, 0, add(0, 0, P5, 0, 0, P1, d/2, 1), 0, 0, P3, d/2, -1), 0, 0, P7, d/2, -1);


	int ** result;
	result = malloc(sizeof(int*) * d);
	for(int v = 0; v < d; v++)
		result[v] = malloc(sizeof(int) * d);

	for(int x = 0; x < d/2; x++)
	{
		for(int y = 0; y < d/2; y++)
		{
			result[x][y] = Q1[x][y];
			result[x+d/2][y] = Q2[x][y];
			result[x][y+d/2] = Q3[x][y];
			result[x+d/2][y+d/2] = Q4[x][y];
		}
	}

	return result;

}

int main(int argc, char *argv[])
{
	if(argc < 4)
		printf("Too few arguments supplied.\n");
	else if(argc > 4)
		printf("Too many arguments supplied.\n");
	else
	{
		int dim = atoi(argv[2]);

		int padded = pad(dim);

		int ** MAT1;
		MAT1 = malloc(sizeof(int*) * padded);
		for(int v = 0; v < padded; v++)
			MAT1[v] = malloc(sizeof(int) * padded);

		int ** MAT2;
		MAT2 = malloc(sizeof(int*) * padded);
		for(int v = 0; v < padded; v++)
			MAT2[v] = malloc(sizeof(int) * padded);


		/* For testing, input numbers in commandline */
		int n[2*dim*dim];

		for (int c = 0; c < 2*dim*dim; c++)
			scanf("%d", &n[c]);

		int count = 0;
		for(int x = 0; x < padded; x++)
		{
			for(int y = 0; y < padded; y++)
			{
				if(x < dim && y < dim)
				{
					MAT1[x][y] = n[count];
					count++;
				}
				else // Pad with zeros
				{
					MAT1[x][y] = 0;
				}
				
			}
		}

		for(int x = 0; x < padded; x++)
		{
			for(int y = 0; y < padded; y++)
			{
				if(x < dim && y < dim)
				{
					MAT2[x][y] = n[count];
					count++;
				}
				else // Pad with zeros
				{
					MAT2[x][y] = 0;
				}
			}
		}

		int ** prodmat = multmat(0, 0, MAT1, 0, 0, MAT2, dim);

		/* Trim off the padding by only copying the dim x dim submatrix */
		int ** trimmed;
		trimmed = malloc(sizeof(int*) * dim);
		for(int v = 0; v < dim; v++)
			trimmed[v] = malloc(sizeof(int) * dim);

		for(int x = 0; x < dim; x++)
		{
			for(int y = 0; y < dim; y++)
			{
				trimmed[x][y] = prodmat[x][y];
			}
		}

		/* Printing for testing */
		for(int p = 0; p < dim; p++)
		{
			for(int q = 0; q < dim; q++)
			{
				printf("%i\n", prodmat[p][q]);
			}
		}
	}
}

