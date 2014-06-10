//-*-C++-*-

#ifndef COSISNUS_VALUE_H
#define COSISNUS_VALUE_H


template<int i, int n>
struct COSINE_EVAL 
{};

template<int i, int n>
struct SINE_EVAL 
{};

template<>
struct COSINE_EVAL<0, 1>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 1>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 2>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 2>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<2, 2>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 3>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 3>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<2, 3>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<3, 3>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 4>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 4>
{
	static double value(){
		return 6.12323399574e-17;
	}
};

template<>
struct COSINE_EVAL<2, 4>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<3, 4>
{
	static double value(){
		return -1.83697019872e-16;
	}
};

template<>
struct COSINE_EVAL<4, 4>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 5>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 5>
{
	static double value(){
		return 0.309016994375;
	}
};

template<>
struct COSINE_EVAL<2, 5>
{
	static double value(){
		return -0.809016994375;
	}
};

template<>
struct COSINE_EVAL<3, 5>
{
	static double value(){
		return -0.809016994375;
	}
};

template<>
struct COSINE_EVAL<4, 5>
{
	static double value(){
		return 0.309016994375;
	}
};

template<>
struct COSINE_EVAL<5, 5>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 6>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 6>
{
	static double value(){
		return 0.5;
	}
};

template<>
struct COSINE_EVAL<2, 6>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<3, 6>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<4, 6>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<5, 6>
{
	static double value(){
		return 0.5;
	}
};

template<>
struct COSINE_EVAL<6, 6>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 7>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 7>
{
	static double value(){
		return 0.623489801859;
	}
};

template<>
struct COSINE_EVAL<2, 7>
{
	static double value(){
		return -0.222520933956;
	}
};

template<>
struct COSINE_EVAL<3, 7>
{
	static double value(){
		return -0.900968867902;
	}
};

template<>
struct COSINE_EVAL<4, 7>
{
	static double value(){
		return -0.900968867902;
	}
};

template<>
struct COSINE_EVAL<5, 7>
{
	static double value(){
		return -0.222520933956;
	}
};

template<>
struct COSINE_EVAL<6, 7>
{
	static double value(){
		return 0.623489801859;
	}
};

template<>
struct COSINE_EVAL<7, 7>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 8>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 8>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct COSINE_EVAL<2, 8>
{
	static double value(){
		return 6.12323399574e-17;
	}
};

template<>
struct COSINE_EVAL<3, 8>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct COSINE_EVAL<4, 8>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<5, 8>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct COSINE_EVAL<6, 8>
{
	static double value(){
		return -1.83697019872e-16;
	}
};

template<>
struct COSINE_EVAL<7, 8>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct COSINE_EVAL<8, 8>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 9>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 9>
{
	static double value(){
		return 0.766044443119;
	}
};

template<>
struct COSINE_EVAL<2, 9>
{
	static double value(){
		return 0.173648177667;
	}
};

template<>
struct COSINE_EVAL<3, 9>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<4, 9>
{
	static double value(){
		return -0.939692620786;
	}
};

template<>
struct COSINE_EVAL<5, 9>
{
	static double value(){
		return -0.939692620786;
	}
};

template<>
struct COSINE_EVAL<6, 9>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<7, 9>
{
	static double value(){
		return 0.173648177667;
	}
};

template<>
struct COSINE_EVAL<8, 9>
{
	static double value(){
		return 0.766044443119;
	}
};

template<>
struct COSINE_EVAL<9, 9>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 10>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 10>
{
	static double value(){
		return 0.809016994375;
	}
};

template<>
struct COSINE_EVAL<2, 10>
{
	static double value(){
		return 0.309016994375;
	}
};

template<>
struct COSINE_EVAL<3, 10>
{
	static double value(){
		return -0.309016994375;
	}
};

template<>
struct COSINE_EVAL<4, 10>
{
	static double value(){
		return -0.809016994375;
	}
};

template<>
struct COSINE_EVAL<5, 10>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<6, 10>
{
	static double value(){
		return -0.809016994375;
	}
};

template<>
struct COSINE_EVAL<7, 10>
{
	static double value(){
		return -0.309016994375;
	}
};

template<>
struct COSINE_EVAL<8, 10>
{
	static double value(){
		return 0.309016994375;
	}
};

template<>
struct COSINE_EVAL<9, 10>
{
	static double value(){
		return 0.809016994375;
	}
};

template<>
struct COSINE_EVAL<10, 10>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 11>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 11>
{
	static double value(){
		return 0.841253532831;
	}
};

template<>
struct COSINE_EVAL<2, 11>
{
	static double value(){
		return 0.415415013002;
	}
};

template<>
struct COSINE_EVAL<3, 11>
{
	static double value(){
		return -0.142314838273;
	}
};

template<>
struct COSINE_EVAL<4, 11>
{
	static double value(){
		return -0.654860733945;
	}
};

template<>
struct COSINE_EVAL<5, 11>
{
	static double value(){
		return -0.959492973614;
	}
};

template<>
struct COSINE_EVAL<6, 11>
{
	static double value(){
		return -0.959492973614;
	}
};

template<>
struct COSINE_EVAL<7, 11>
{
	static double value(){
		return -0.654860733945;
	}
};

template<>
struct COSINE_EVAL<8, 11>
{
	static double value(){
		return -0.142314838273;
	}
};

template<>
struct COSINE_EVAL<9, 11>
{
	static double value(){
		return 0.415415013002;
	}
};

template<>
struct COSINE_EVAL<10, 11>
{
	static double value(){
		return 0.841253532831;
	}
};

template<>
struct COSINE_EVAL<11, 11>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 12>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 12>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct COSINE_EVAL<2, 12>
{
	static double value(){
		return 0.5;
	}
};

template<>
struct COSINE_EVAL<3, 12>
{
	static double value(){
		return 6.12323399574e-17;
	}
};

template<>
struct COSINE_EVAL<4, 12>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<5, 12>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct COSINE_EVAL<6, 12>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<7, 12>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct COSINE_EVAL<8, 12>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<9, 12>
{
	static double value(){
		return -1.83697019872e-16;
	}
};

template<>
struct COSINE_EVAL<10, 12>
{
	static double value(){
		return 0.5;
	}
};

template<>
struct COSINE_EVAL<11, 12>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct COSINE_EVAL<12, 12>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 13>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 13>
{
	static double value(){
		return 0.885456025653;
	}
};

template<>
struct COSINE_EVAL<2, 13>
{
	static double value(){
		return 0.568064746731;
	}
};

template<>
struct COSINE_EVAL<3, 13>
{
	static double value(){
		return 0.120536680255;
	}
};

template<>
struct COSINE_EVAL<4, 13>
{
	static double value(){
		return -0.354604887043;
	}
};

template<>
struct COSINE_EVAL<5, 13>
{
	static double value(){
		return -0.748510748171;
	}
};

template<>
struct COSINE_EVAL<6, 13>
{
	static double value(){
		return -0.970941817426;
	}
};

template<>
struct COSINE_EVAL<7, 13>
{
	static double value(){
		return -0.970941817426;
	}
};

template<>
struct COSINE_EVAL<8, 13>
{
	static double value(){
		return -0.748510748171;
	}
};

template<>
struct COSINE_EVAL<9, 13>
{
	static double value(){
		return -0.354604887043;
	}
};

template<>
struct COSINE_EVAL<10, 13>
{
	static double value(){
		return 0.120536680255;
	}
};

template<>
struct COSINE_EVAL<11, 13>
{
	static double value(){
		return 0.568064746731;
	}
};

template<>
struct COSINE_EVAL<12, 13>
{
	static double value(){
		return 0.885456025653;
	}
};

template<>
struct COSINE_EVAL<13, 13>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 14>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 14>
{
	static double value(){
		return 0.900968867902;
	}
};

template<>
struct COSINE_EVAL<2, 14>
{
	static double value(){
		return 0.623489801859;
	}
};

template<>
struct COSINE_EVAL<3, 14>
{
	static double value(){
		return 0.222520933956;
	}
};

template<>
struct COSINE_EVAL<4, 14>
{
	static double value(){
		return -0.222520933956;
	}
};

template<>
struct COSINE_EVAL<5, 14>
{
	static double value(){
		return -0.623489801859;
	}
};

template<>
struct COSINE_EVAL<6, 14>
{
	static double value(){
		return -0.900968867902;
	}
};

template<>
struct COSINE_EVAL<7, 14>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<8, 14>
{
	static double value(){
		return -0.900968867902;
	}
};

template<>
struct COSINE_EVAL<9, 14>
{
	static double value(){
		return -0.623489801859;
	}
};

template<>
struct COSINE_EVAL<10, 14>
{
	static double value(){
		return -0.222520933956;
	}
};

template<>
struct COSINE_EVAL<11, 14>
{
	static double value(){
		return 0.222520933956;
	}
};

template<>
struct COSINE_EVAL<12, 14>
{
	static double value(){
		return 0.623489801859;
	}
};

template<>
struct COSINE_EVAL<13, 14>
{
	static double value(){
		return 0.900968867902;
	}
};

template<>
struct COSINE_EVAL<14, 14>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 15>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 15>
{
	static double value(){
		return 0.913545457643;
	}
};

template<>
struct COSINE_EVAL<2, 15>
{
	static double value(){
		return 0.669130606359;
	}
};

template<>
struct COSINE_EVAL<3, 15>
{
	static double value(){
		return 0.309016994375;
	}
};

template<>
struct COSINE_EVAL<4, 15>
{
	static double value(){
		return -0.104528463268;
	}
};

template<>
struct COSINE_EVAL<5, 15>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<6, 15>
{
	static double value(){
		return -0.809016994375;
	}
};

template<>
struct COSINE_EVAL<7, 15>
{
	static double value(){
		return -0.978147600734;
	}
};

template<>
struct COSINE_EVAL<8, 15>
{
	static double value(){
		return -0.978147600734;
	}
};

template<>
struct COSINE_EVAL<9, 15>
{
	static double value(){
		return -0.809016994375;
	}
};

template<>
struct COSINE_EVAL<10, 15>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct COSINE_EVAL<11, 15>
{
	static double value(){
		return -0.104528463268;
	}
};

template<>
struct COSINE_EVAL<12, 15>
{
	static double value(){
		return 0.309016994375;
	}
};

template<>
struct COSINE_EVAL<13, 15>
{
	static double value(){
		return 0.669130606359;
	}
};

template<>
struct COSINE_EVAL<14, 15>
{
	static double value(){
		return 0.913545457643;
	}
};

template<>
struct COSINE_EVAL<15, 15>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<0, 16>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct COSINE_EVAL<1, 16>
{
	static double value(){
		return 0.923879532511;
	}
};

template<>
struct COSINE_EVAL<2, 16>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct COSINE_EVAL<3, 16>
{
	static double value(){
		return 0.382683432365;
	}
};

template<>
struct COSINE_EVAL<4, 16>
{
	static double value(){
		return 6.12323399574e-17;
	}
};

template<>
struct COSINE_EVAL<5, 16>
{
	static double value(){
		return -0.382683432365;
	}
};

template<>
struct COSINE_EVAL<6, 16>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct COSINE_EVAL<7, 16>
{
	static double value(){
		return -0.923879532511;
	}
};

template<>
struct COSINE_EVAL<8, 16>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct COSINE_EVAL<9, 16>
{
	static double value(){
		return -0.923879532511;
	}
};

template<>
struct COSINE_EVAL<10, 16>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct COSINE_EVAL<11, 16>
{
	static double value(){
		return -0.382683432365;
	}
};

template<>
struct COSINE_EVAL<12, 16>
{
	static double value(){
		return -1.83697019872e-16;
	}
};

template<>
struct COSINE_EVAL<13, 16>
{
	static double value(){
		return 0.382683432365;
	}
};

template<>
struct COSINE_EVAL<14, 16>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct COSINE_EVAL<15, 16>
{
	static double value(){
		return 0.923879532511;
	}
};

template<>
struct COSINE_EVAL<16, 16>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct SINE_EVAL<0, 1>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 1>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 2>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 2>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<2, 2>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 3>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 3>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<2, 3>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<3, 3>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 4>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 4>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct SINE_EVAL<2, 4>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<3, 4>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct SINE_EVAL<4, 4>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 5>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 5>
{
	static double value(){
		return 0.951056516295;
	}
};

template<>
struct SINE_EVAL<2, 5>
{
	static double value(){
		return 0.587785252292;
	}
};

template<>
struct SINE_EVAL<3, 5>
{
	static double value(){
		return -0.587785252292;
	}
};

template<>
struct SINE_EVAL<4, 5>
{
	static double value(){
		return -0.951056516295;
	}
};

template<>
struct SINE_EVAL<5, 5>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 6>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 6>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<2, 6>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<3, 6>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<4, 6>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<5, 6>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<6, 6>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 7>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 7>
{
	static double value(){
		return 0.781831482468;
	}
};

template<>
struct SINE_EVAL<2, 7>
{
	static double value(){
		return 0.974927912182;
	}
};

template<>
struct SINE_EVAL<3, 7>
{
	static double value(){
		return 0.433883739118;
	}
};

template<>
struct SINE_EVAL<4, 7>
{
	static double value(){
		return -0.433883739118;
	}
};

template<>
struct SINE_EVAL<5, 7>
{
	static double value(){
		return -0.974927912182;
	}
};

template<>
struct SINE_EVAL<6, 7>
{
	static double value(){
		return -0.781831482468;
	}
};

template<>
struct SINE_EVAL<7, 7>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 8>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 8>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct SINE_EVAL<2, 8>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct SINE_EVAL<3, 8>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct SINE_EVAL<4, 8>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<5, 8>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct SINE_EVAL<6, 8>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct SINE_EVAL<7, 8>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct SINE_EVAL<8, 8>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 9>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 9>
{
	static double value(){
		return 0.642787609687;
	}
};

template<>
struct SINE_EVAL<2, 9>
{
	static double value(){
		return 0.984807753012;
	}
};

template<>
struct SINE_EVAL<3, 9>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<4, 9>
{
	static double value(){
		return 0.342020143326;
	}
};

template<>
struct SINE_EVAL<5, 9>
{
	static double value(){
		return -0.342020143326;
	}
};

template<>
struct SINE_EVAL<6, 9>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<7, 9>
{
	static double value(){
		return -0.984807753012;
	}
};

template<>
struct SINE_EVAL<8, 9>
{
	static double value(){
		return -0.642787609687;
	}
};

template<>
struct SINE_EVAL<9, 9>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 10>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 10>
{
	static double value(){
		return 0.587785252292;
	}
};

template<>
struct SINE_EVAL<2, 10>
{
	static double value(){
		return 0.951056516295;
	}
};

template<>
struct SINE_EVAL<3, 10>
{
	static double value(){
		return 0.951056516295;
	}
};

template<>
struct SINE_EVAL<4, 10>
{
	static double value(){
		return 0.587785252292;
	}
};

template<>
struct SINE_EVAL<5, 10>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<6, 10>
{
	static double value(){
		return -0.587785252292;
	}
};

template<>
struct SINE_EVAL<7, 10>
{
	static double value(){
		return -0.951056516295;
	}
};

template<>
struct SINE_EVAL<8, 10>
{
	static double value(){
		return -0.951056516295;
	}
};

template<>
struct SINE_EVAL<9, 10>
{
	static double value(){
		return -0.587785252292;
	}
};

template<>
struct SINE_EVAL<10, 10>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 11>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 11>
{
	static double value(){
		return 0.540640817456;
	}
};

template<>
struct SINE_EVAL<2, 11>
{
	static double value(){
		return 0.909631995355;
	}
};

template<>
struct SINE_EVAL<3, 11>
{
	static double value(){
		return 0.989821441881;
	}
};

template<>
struct SINE_EVAL<4, 11>
{
	static double value(){
		return 0.755749574354;
	}
};

template<>
struct SINE_EVAL<5, 11>
{
	static double value(){
		return 0.281732556841;
	}
};

template<>
struct SINE_EVAL<6, 11>
{
	static double value(){
		return -0.281732556841;
	}
};

template<>
struct SINE_EVAL<7, 11>
{
	static double value(){
		return -0.755749574354;
	}
};

template<>
struct SINE_EVAL<8, 11>
{
	static double value(){
		return -0.989821441881;
	}
};

template<>
struct SINE_EVAL<9, 11>
{
	static double value(){
		return -0.909631995355;
	}
};

template<>
struct SINE_EVAL<10, 11>
{
	static double value(){
		return -0.540640817456;
	}
};

template<>
struct SINE_EVAL<11, 11>
{
	static double value(){
		return -1.13310777953e-15;
	}
};

template<>
struct SINE_EVAL<0, 12>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 12>
{
	static double value(){
		return 0.5;
	}
};

template<>
struct SINE_EVAL<2, 12>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<3, 12>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct SINE_EVAL<4, 12>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<5, 12>
{
	static double value(){
		return 0.5;
	}
};

template<>
struct SINE_EVAL<6, 12>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<7, 12>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct SINE_EVAL<8, 12>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<9, 12>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct SINE_EVAL<10, 12>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<11, 12>
{
	static double value(){
		return -0.5;
	}
};

template<>
struct SINE_EVAL<12, 12>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 13>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 13>
{
	static double value(){
		return 0.464723172044;
	}
};

template<>
struct SINE_EVAL<2, 13>
{
	static double value(){
		return 0.822983865894;
	}
};

template<>
struct SINE_EVAL<3, 13>
{
	static double value(){
		return 0.992708874098;
	}
};

template<>
struct SINE_EVAL<4, 13>
{
	static double value(){
		return 0.935016242685;
	}
};

template<>
struct SINE_EVAL<5, 13>
{
	static double value(){
		return 0.663122658241;
	}
};

template<>
struct SINE_EVAL<6, 13>
{
	static double value(){
		return 0.239315664288;
	}
};

template<>
struct SINE_EVAL<7, 13>
{
	static double value(){
		return -0.239315664288;
	}
};

template<>
struct SINE_EVAL<8, 13>
{
	static double value(){
		return -0.663122658241;
	}
};

template<>
struct SINE_EVAL<9, 13>
{
	static double value(){
		return -0.935016242685;
	}
};

template<>
struct SINE_EVAL<10, 13>
{
	static double value(){
		return -0.992708874098;
	}
};

template<>
struct SINE_EVAL<11, 13>
{
	static double value(){
		return -0.822983865894;
	}
};

template<>
struct SINE_EVAL<12, 13>
{
	static double value(){
		return -0.464723172044;
	}
};

template<>
struct SINE_EVAL<13, 13>
{
	static double value(){
		return 6.43249059871e-16;
	}
};

template<>
struct SINE_EVAL<0, 14>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 14>
{
	static double value(){
		return 0.433883739118;
	}
};

template<>
struct SINE_EVAL<2, 14>
{
	static double value(){
		return 0.781831482468;
	}
};

template<>
struct SINE_EVAL<3, 14>
{
	static double value(){
		return 0.974927912182;
	}
};

template<>
struct SINE_EVAL<4, 14>
{
	static double value(){
		return 0.974927912182;
	}
};

template<>
struct SINE_EVAL<5, 14>
{
	static double value(){
		return 0.781831482468;
	}
};

template<>
struct SINE_EVAL<6, 14>
{
	static double value(){
		return 0.433883739118;
	}
};

template<>
struct SINE_EVAL<7, 14>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<8, 14>
{
	static double value(){
		return -0.433883739118;
	}
};

template<>
struct SINE_EVAL<9, 14>
{
	static double value(){
		return -0.781831482468;
	}
};

template<>
struct SINE_EVAL<10, 14>
{
	static double value(){
		return -0.974927912182;
	}
};

template<>
struct SINE_EVAL<11, 14>
{
	static double value(){
		return -0.974927912182;
	}
};

template<>
struct SINE_EVAL<12, 14>
{
	static double value(){
		return -0.781831482468;
	}
};

template<>
struct SINE_EVAL<13, 14>
{
	static double value(){
		return -0.433883739118;
	}
};

template<>
struct SINE_EVAL<14, 14>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

template<>
struct SINE_EVAL<0, 15>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 15>
{
	static double value(){
		return 0.406736643076;
	}
};

template<>
struct SINE_EVAL<2, 15>
{
	static double value(){
		return 0.743144825477;
	}
};

template<>
struct SINE_EVAL<3, 15>
{
	static double value(){
		return 0.951056516295;
	}
};

template<>
struct SINE_EVAL<4, 15>
{
	static double value(){
		return 0.994521895368;
	}
};

template<>
struct SINE_EVAL<5, 15>
{
	static double value(){
		return 0.866025403784;
	}
};

template<>
struct SINE_EVAL<6, 15>
{
	static double value(){
		return 0.587785252292;
	}
};

template<>
struct SINE_EVAL<7, 15>
{
	static double value(){
		return 0.207911690818;
	}
};

template<>
struct SINE_EVAL<8, 15>
{
	static double value(){
		return -0.207911690818;
	}
};

template<>
struct SINE_EVAL<9, 15>
{
	static double value(){
		return -0.587785252292;
	}
};

template<>
struct SINE_EVAL<10, 15>
{
	static double value(){
		return -0.866025403784;
	}
};

template<>
struct SINE_EVAL<11, 15>
{
	static double value(){
		return -0.994521895368;
	}
};

template<>
struct SINE_EVAL<12, 15>
{
	static double value(){
		return -0.951056516295;
	}
};

template<>
struct SINE_EVAL<13, 15>
{
	static double value(){
		return -0.743144825477;
	}
};

template<>
struct SINE_EVAL<14, 15>
{
	static double value(){
		return -0.406736643076;
	}
};

template<>
struct SINE_EVAL<15, 15>
{
	static double value(){
		return -1.13310777953e-15;
	}
};

template<>
struct SINE_EVAL<0, 16>
{
	static double value(){
		return 0.0;
	}
};

template<>
struct SINE_EVAL<1, 16>
{
	static double value(){
		return 0.382683432365;
	}
};

template<>
struct SINE_EVAL<2, 16>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct SINE_EVAL<3, 16>
{
	static double value(){
		return 0.923879532511;
	}
};

template<>
struct SINE_EVAL<4, 16>
{
	static double value(){
		return 1.0;
	}
};

template<>
struct SINE_EVAL<5, 16>
{
	static double value(){
		return 0.923879532511;
	}
};

template<>
struct SINE_EVAL<6, 16>
{
	static double value(){
		return 0.707106781187;
	}
};

template<>
struct SINE_EVAL<7, 16>
{
	static double value(){
		return 0.382683432365;
	}
};

template<>
struct SINE_EVAL<8, 16>
{
	static double value(){
		return 1.22464679915e-16;
	}
};

template<>
struct SINE_EVAL<9, 16>
{
	static double value(){
		return -0.382683432365;
	}
};

template<>
struct SINE_EVAL<10, 16>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct SINE_EVAL<11, 16>
{
	static double value(){
		return -0.923879532511;
	}
};

template<>
struct SINE_EVAL<12, 16>
{
	static double value(){
		return -1.0;
	}
};

template<>
struct SINE_EVAL<13, 16>
{
	static double value(){
		return -0.923879532511;
	}
};

template<>
struct SINE_EVAL<14, 16>
{
	static double value(){
		return -0.707106781187;
	}
};

template<>
struct SINE_EVAL<15, 16>
{
	static double value(){
		return -0.382683432365;
	}
};

template<>
struct SINE_EVAL<16, 16>
{
	static double value(){
		return -2.44929359829e-16;
	}
};

#endif

