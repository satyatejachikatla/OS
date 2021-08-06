#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint8_t hi(uint8_t x){
	return (x >> 4) & (0x10-1);
}

uint8_t lo(uint8_t x) {
	return (0x10-1)&x;
}

uint16_t multiply(uint8_t a,uint8_t b) {

	// high   - low

	// 32bits - 32bits
	// wx * yz = (w0*y0)+(w0*0z)+(0x*z0)+(0x*0z)

	// w = hi(a)
	// x = lo(a)

	// y = hi(b)
	// z = lo(b) 

	// s1 =   w*y 00
	// s2 =   0 wz 0
	// s3 =   0 xz 0
	// s4 =   00 x*z

	uint16_t s1 = (uint16_t)(hi(a) * hi(b)) << 8; 
	uint16_t s2 = (uint16_t)(lo(a) * hi(b)) << 4;
	uint16_t s3 = (uint16_t)(hi(a) * lo(b)) << 4;
	uint16_t s4 = (uint16_t)(lo(a) * lo(b));


	return s1+s2+s3+s4;
}


int main() {


	uint8_t a = 0x12;
	uint8_t b = 0x34;
	uint16_t ans;

	printf("A hi:%x lo:%x\n",hi(a),lo(a));
	printf("B hi:%x lo:%x\n",hi(b),lo(b));	

	ans = a*b;
	if (a != 0 && ans/a != b || 1/*Forcing to exectue the if*/){
		printf("Here\n");
		ans = multiply(a,b);
	}

	printf("Ans %x\n",ans);

	return 0;
}
