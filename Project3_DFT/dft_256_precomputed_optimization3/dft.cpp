#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft (DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE]) {
	int i, j;
	DTYPE cos, sin, temp_real, temp_imag;

	//Partition arrays into smaller arrays to individual elements to provide:
	// multiple registers instead of one large memory to Potentially improves the throughput of the design
	#pragma HLS array_partition variable=real_sample cyclic factor=8
	#pragma HLS array_partition variable=imag_sample cyclic factor=8
	#pragma HLS array_partition variable=real_out cyclic factor=8
	#pragma HLS array_partition variable=imag_out cyclic factor=8
	#pragma HLS array_partition variable=cos_coefficients_table cyclic factor=8
	#pragma HLS array_partition variable=sin_coefficients_table cyclic factor=8

	// Compute each frequency domain sample
	for (i = 0; i < SIZE; i += 1) {
		temp_real = 0;
		temp_imag = 0;

		// Calculate the jth frequency sample sequentially
		for (j = 0; j < SIZE; j += 1) {
			#pragma HLS unroll factor=8
			// 
			int index = (i*j)%SIZE;
			cos = cos_coefficients_table[index];
			sin = sin_coefficients_table[index];

			// Multiply the current phasor with the appropriate input sample
			// then summation
			temp_real += (real_sample[j] * cos - imag_sample[j] * sin);
			temp_imag += (real_sample[j] * sin + imag_sample[j] * cos);
		}
		real_out[i] = temp_real;
		imag_out[i] = temp_imag;
	}
}
