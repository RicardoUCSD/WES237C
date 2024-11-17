#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft (DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE]) {
	int i, j;
	DTYPE w, cos, sin, temp_real, temp_imag;
	// Calculate each frequency domain sample iteratively
	for (i = 0; i < SIZE; i += 1) {
		temp_real = 0;
		temp_imag = 0;
		// Calculate the jth frequency sample sequentially
		for (j = 0; j < SIZE; j += 1) {
			// Utilize HLS tool to calculate sine and cosine values
			int index = (i * j) % SIZE;
			cos = cos_coefficients_table[index];
			sin = sin_coefficients_table[index];

			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			temp_real += (real_sample[j] * cos - imag_sample[j] * sin);
			temp_imag += (real_sample[j] * sin + imag_sample[j] * cos);
		}

		real_out[i] = temp_real;
		imag_out[i] = temp_imag;
	}
}
