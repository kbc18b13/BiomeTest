#include "Perlin.h"

Perlin::Perlin(){}

float Perlin::PerlinNoise( float x, float y, float z ){
	/*if (m_repeat > 0) {
		x = x % m_repeat;
		y = y % m_repeat;
		z = z % m_repeat;
	}*/

	//単位立方体内部の座標
	float xf = x - (int)x;
	float yf = y - (int)y;
	float zf = z - (int)z;

	float u = Fade( xf );
	float v = Fade( yf );
	float w = Fade( zf );

	//単位立方体の各隅に勾配を与えるためのハッシュ値。
	int aaa, aab, aba, abb, baa, bab, bba, bbb;
	aaa = Hash( x, y, z );
	aab = Hash( x, y, z + 1 );
	aba = Hash( x, y + 1, z );
	abb = Hash( x, y + 1, z + 1 );
	baa = Hash( x + 1, y, z );
	bab = Hash( x + 1, y, z + 1 );
	bba = Hash( x + 1, y + 1, z );
	bbb = Hash( x + 1, y + 1, z + 1 );

	double x1, x2, y1, y2;
	x1 = Lerp( Grad( aaa, xf, yf, zf ), Grad( baa, xf - 1, yf, zf ), u );

	x2 = Lerp( Grad( aba, xf, yf - 1, zf ), Grad( bba, xf - 1, yf - 1, zf ), u );

	y1 = Lerp( x1, x2, v );

	x1 = Lerp( Grad( aab, xf, yf, zf - 1 ), Grad( bab, xf - 1, yf, zf - 1 ), u );

	x2 = Lerp( Grad( abb, xf, yf - 1, zf - 1 ), Grad( bbb, xf - 1, yf - 1, zf - 1 ), u );

	y2 = Lerp( x1, x2, v );

	return ( Lerp( y1, y2, w ) + 1 ) / 2;
}

float Perlin::OctavePerlin( float x, float y, float z, int octaves, float persistence ){
	float total = 0;
	float frequency = 1;
	float amplitude = 1;
	float maxValue = 0;

	for( int i = 0; i < octaves; i++ ){
		total += PerlinNoise( x * frequency, y * frequency, z * frequency ) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

int Perlin::Hash( float x, float y, float z ){
	unsigned r = xorshift32( int( x ) + m_seed );
	r = xorshift32( r + int( y ) );
	r = xorshift32( r + int( z ) );
	return r;
}

float Perlin::Grad( int hash, float x, float y, float z ){
	switch( hash & 0xF ){
	case 0x0: return  x + y;
	case 0x1: return -x + y;
	case 0x2: return  x - y;
	case 0x3: return -x - y;
	case 0x4: return  x + z;
	case 0x5: return -x + z;
	case 0x6: return  x - z;
	case 0x7: return -x - z;
	case 0x8: return  y + z;
	case 0x9: return -y + z;
	case 0xA: return  y - z;
	case 0xB: return -y - z;
	case 0xC: return  y + x;
	case 0xD: return -y + z;
	case 0xE: return  y - x;
	case 0xF: return -y - z;
	default: return 0; // never happens
	}
}