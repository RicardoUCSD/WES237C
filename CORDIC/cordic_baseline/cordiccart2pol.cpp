#include "cordiccart2pol.h"
#include "ap_int.h"
#include "stdio.h"
#include "math.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};
data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};


void cordiccart2pol(data_t x, data_t y, data_t * r, data_t * theta) {
	#pragma HLS INTERFACE mode=s_axilite port=x
	#pragma HLS INTERFACE mode=s_axilite port=y
	#pragma HLS INTERFACE mode=s_axilite port=r
	#pragma HLS INTERFACE mode=s_axilite port=theta
	#pragma HLS INTERFACE mode=s_axilite port=return

	data_t cart_x = x;
	data_t cart_y = y;
	data_t theta_now = 0;	//Initialized in Quadrant I, zero degrees
    // Quadrants:	I   (+,+), II (-,+)
    // 				III (+,+), IV (+,-)
    if(cart_x<0){		//If x resides in the left side  quadrants(II & III)?
    	if(cart_y>0){	// If (y) resides in quadrant II
    		cart_y = -x;
    		cart_x = +y;
    		theta_now = 1.5707963267945; //Then theta_now is in 90º= + π/2

    	}else{			//Else (y) resides in quadrant III ?
    		cart_y = +x;
    		cart_x = -y;
    		theta_now = -1.5707963267945; //Then theta_now is in 270º= - π/2
    	}
    }

    data_t x_shifting, y_shifting, sigma;
    coef_t i;
    for(i = 0;i<NO_ITER;i++){
    	sigma = (cart_y > 0)? -1:1;
    	x_shifting = cart_x * sigma * Kvalues[i];
    	y_shifting = cart_y * sigma * Kvalues[i];

    	cart_x = cart_x - y_shifting;
    	cart_y = cart_y + x_shifting;

    	theta_now += -sigma*angles[i];
    }
    data_t gain = 1.64676025786545;
    *r = cart_x/ gain;
   	*theta = theta_now;

}
