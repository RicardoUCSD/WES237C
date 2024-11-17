#include <ap_int.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#define SIZE 1024 		/* SIZE OF DFT */
//				Sample structure for streaming. You can use this for the demo.
/*
struct DTYPE							
{
	float data;
	ap_uint<1> last;
};
*/
/*
struct fp_int{
	int i;
	float fp;
};
*/
struct fp_int{
	int last;
	float data;
};

///
typedef ap_axis<32,2,5,6> transPkt;

//~typedef hls::stream<DTYPE> stream_t;
typedef hls::stream<transPkt> stream_t; //32 bits per packet

//typedef float DTYPE;

void dft(stream_t &real_in, stream_t &imag_in,stream_t &real_out, stream_t &imag_out);
//void dft(DTYPE real_in[SIZE], DTYPE imag_in[SIZE],DTYPE real_out[SIZE], DTYPE imag_out[SIZE]);
//void dft(DTYPE *, DTYPE *,DTYPE *, DTYPE *); use this for doing the demo//
