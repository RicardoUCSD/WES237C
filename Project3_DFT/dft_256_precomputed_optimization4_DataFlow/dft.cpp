#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void Loop1(int i, DTYPE cos[SIZE], DTYPE sin[SIZE]) {
	int j;
	for (j = 0; j < SIZE; j ++) {
#pragma HLS unroll factor=4
		//
		int index = (i * j) % SIZE;
		cos[j] = cos_coefficients_table[index];
		sin[j] = sin_coefficients_table[index];
	}
}

void Loop2(DTYPE cos[SIZE], DTYPE sin[SIZE], DTYPE real_in[SIZE], DTYPE imag_in[SIZE], DTYPE temp_real_out[SIZE], DTYPE temp_imag_out[SIZE]) {
	int j;
	for (j = 0; j < SIZE; j ++) {
#pragma HLS unroll factor=4
		DTYPE cos_temp = cos[j];
		DTYPE sin_temp = sin[j];
		DTYPE temp_real_in = real_in[j];
		DTYPE temp_imag_in = imag_in[j];
		temp_real_out[j] = (temp_real_in * cos_temp - temp_imag_in * sin_temp);
		temp_imag_out[j] = (temp_real_in * sin_temp + temp_imag_in * cos_temp);
	}
}

void Loop3(int i, DTYPE temp_real_out[SIZE], DTYPE temp_imag_out[SIZE], DTYPE sum_real[SIZE], DTYPE sum_imag[SIZE]) {
	int j;
	for (j = 0; j < SIZE; j ++) {
#pragma HLS unroll factor=4
		if (j==0) {
			sum_real[i]=temp_real_out[j];
			sum_imag[i]=temp_imag_out[j];
		} else {
			sum_real[i]+=temp_real_out[j];
			sum_imag[i]+=temp_imag_out[j];
		}
	}
}

void LastPart(int i, DTYPE sum_real[SIZE], DTYPE sum_imag[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE]) {
	real_out[i] = sum_real[i];
	imag_out[i] = sum_imag[i];
}

void dft (DTYPE real_in[SIZE], DTYPE imag_in[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE]) {
	//Partition arrays into smaller arrays to individual elements to provide:
	// multiple registers instead of one large memory to Potentially improves
	// the throughput of the design
	#pragma HLS array_partition variable=real_in cyclic factor=4
	#pragma HLS array_partition variable=imag_in cyclic factor=4
	#pragma HLS array_partition variable=real_out cyclic factor=4
	#pragma HLS array_partition variable=imag_out cyclic factor=4
	#pragma HLS array_partition variable=cos_coefficients_table cyclic factor=4
	#pragma HLS array_partition variable=sin_coefficients_table cyclic factor=4
	// Compute each frequency domain sample
	for (int i = 0; i < SIZE; i ++) {
		#pragma HLS dataflow
		DTYPE cos[SIZE], sin[SIZE];
		DTYPE temp_real_out[SIZE], temp_imag_out[SIZE];
		DTYPE sum_real[SIZE], sum_imag[SIZE];
		Loop1(i, cos, sin);												// Lookup tables
		Loop2(cos, sin, real_in, imag_in, temp_real_out, temp_imag_out);// Multiply the current phasor with the appropriate input sample
		Loop3(i, temp_real_out, temp_imag_out, sum_real, sum_imag);		// Summation of products
		LastPart(i,sum_real,sum_imag, real_out, imag_out);				// Return values
	}
}
