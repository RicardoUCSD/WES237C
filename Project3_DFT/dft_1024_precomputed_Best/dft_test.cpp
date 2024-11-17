/*
This is DFT computation using matrix vector multiplication form.
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal in time domain.
OUTPUT:
	Out_R, Out_I[]: Real and Imag parts of Complex signal in frequency domain.

*/

#include<stdio.h>
#include <stdlib.h>
#include<iostream>
#include <math.h>
#include "dft.h"

struct Rmse
{
	int num_sq;
	float sum_sq;
	float error;

	Rmse(){ num_sq = 0; sum_sq = 0; error = 0; }

	float add_value(float d_n)
	{
		num_sq++;
		sum_sq += (d_n*d_n);
		error = sqrtf(sum_sq / num_sq);
		return error;
	}

};


Rmse rmse_R,  rmse_I;

//DTYPE In_R[SIZE], In_I[SIZE],Out_R[SIZE],Out_I[SIZE];   //Modify the testbench while checking for demo. You will have to access the data variable of the structure//
stream_t In_R,In_I,Out_R,Out_I;   //Modify the testbench while checking for demo. You will have to access the data variable of the structure//

int main()
{
	int index;
	float gold_R, gold_I;

	//float tmp, tmp2 = 0.0;
	transPkt tmp_R, tmp_I;

	FILE * fp = fopen("out.gold.dat","r");

	// getting input data
	//for(int i=0; i<SIZE; i++)
	//{
	//	In_R[i].data = i;
	//	In_I[i].data = 0.0;
	//}


	for(int i=0; i<SIZE; i++)
	{
		tmp_R.data = float(i);
		tmp_R.last = i==SIZE-1 ? 1 : 0;
		tmp_I.data = 0.0;
		tmp_I.last = i==SIZE-1 ? 1 : 0;
		In_R.write(tmp_R);
		In_I.write(tmp_I);
	}
	
	// DFT
	dft(In_R, In_I,Out_R,Out_I);

	// comparing with golden output
	for(int i=0; i<SIZE; i++)
	{
		tmp_R = Out_R.read();
		tmp_I = Out_I.read();
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R.add_value(tmp_R.data - gold_R);
		rmse_I.add_value(tmp_I.data - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("----------------------------------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R.error, rmse_I.error);
	printf("----------------------------------------------\n");

	if (rmse_R.error > 0.1 || rmse_I.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
	    return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
	    return 0;
	}

}
