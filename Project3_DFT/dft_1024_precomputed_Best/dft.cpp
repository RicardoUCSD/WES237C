#include<math.h>
#include "dft.h"
#include "coefficients1024.h"

typedef double TEMP_TYPE; // Data type for the temporary variables
#define N 1024
ap_uint<4> keep_re[SIZE]; // 32 bits = 4x bytes
ap_uint<4> keep_im2[SIZE];

void Loop1(int i, float cos[SIZE], float sin[SIZE]) {
	int j;
	for (j = 0; j < SIZE; j ++) {
#pragma HLS unroll factor=8
		//
		int index = (i * j) % SIZE;
		cos[j] = cos_coefficients_table[index];
		sin[j] = sin_coefficients_table[index];
	}
}

void Loop2(float cos[SIZE], float sin[SIZE], float real_in[SIZE], float imag_in[SIZE], float temp_real_out[SIZE], float temp_imag_out[SIZE]) {
	int j;
	for (j = 0; j < SIZE; j ++) {
#pragma HLS unroll factor=8
		float cos_temp = cos[j];
		float sin_temp = sin[j];
		float temp_real_in = real_in[j];
		float temp_imag_in = imag_in[j];
		temp_real_out[j] = (temp_real_in * cos_temp - temp_imag_in * sin_temp);
		temp_imag_out[j] = (temp_real_in * sin_temp + temp_imag_in * cos_temp);
	}
}
void Loop3(int i, float temp_real_out[SIZE], float temp_imag_out[SIZE], float sum_real[SIZE], float sum_imag[SIZE]) {
	int j;
	for (j = 0; j < SIZE; j ++) {
#pragma HLS unroll factor=8
		if (j==0) {
			sum_real[i]=temp_real_out[j];
			sum_imag[i]=temp_imag_out[j];
		} else {
			sum_real[i]+=temp_real_out[j];
			sum_imag[i]+=temp_imag_out[j];
		}
	}
}

void dft (stream_t &real_in, stream_t &imag_in, stream_t  &real_out, stream_t  &imag_out) {
	//Partition arrays into smaller arrays to individual elements to provide: multiple registers instead of one large
	//memory to Potentially improves the throughput of the design
	#pragma HLS array_partition variable=real_in cyclic factor=8
	#pragma HLS array_partition variable=imag_in cyclic factor=8
	#pragma HLS array_partition variable=real_out cyclic factor=8
	#pragma HLS array_partition variable=imag_out cyclic factor=8
	#pragma HLS array_partition variable=cos_coefficients_table cyclic factor=8
	#pragma HLS array_partition variable=sin_coefficients_table cyclic factor=8

	transPkt   tmp_R, tmp_I;
	transPkt   tmp2_R, tmp2_I;
	float Real[SIZE], Imag[SIZE];
	float real[SIZE], imag[SIZE];
	for (int k = 0;k<SIZE;k++){
		Real[k] = 0;
		Imag[k] = 0;
		tmp_R = real_in.read();
		tmp_I = imag_in.read();
		real[k] = tmp_R.data;
		imag[k] = tmp_I.data;
	}

	// Compute for each freq.
	for (int i = 0; i < SIZE; i ++) {
		#pragma HLS dataflow
		float cos[SIZE], sin[SIZE];
		float temp_real_out[SIZE], temp_imag_out[SIZE];
		float sum_real[SIZE], sum_imag[SIZE];
		Loop1(i, cos, sin);	  //	was &tmp_R, &tmp_I									// Lookup tables
		Loop2(cos, sin, real, imag, temp_real_out, temp_imag_out);// Multiply the current phasor with the appropriate input sample
		Loop3(i, temp_real_out, temp_imag_out, sum_real, sum_imag);		// Summation of products

		//LastPart(i,sum_real,sum_imag, real_out, imag_out);				// Return values
		tmp2_R.data = sum_real[i];
		tmp2_R.last = (i==SIZE-1) ? 1 : 0;
		tmp2_I.data = sum_imag[i];
		tmp2_I.last = (i==SIZE-1) ? 1 : 0;
		real_out.write(tmp2_R);
		imag_out.write(tmp2_I);
	}
}

