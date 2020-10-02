#include "Perlin.h"
#include "Bitmap.h"

int main(){
	Perlin& perlin = Perlin::GetInstance();
	Bitmap bmp;

	const uint32_t width = 500;

	bmp.Init( width, width );

	while( true ){

		std::random_device randDevice;
		uint32_t seedX = randDevice() % 101;
		uint32_t seedZ = randDevice() % 101;

		uint32_t seedX2 = seedX + 50 % 101;
		uint32_t seedZ2 = seedZ + 50 % 101;

		float relief;

		std::cout << "reliefの値を入力してください。>> ";
		std::cin >> relief;

		if( relief == -1 ){
			break;
		}

		for( int i = 0; i < width; i++ ){
			for( int j = 0; j < width; j++ ){
				auto& c = bmp.At( i, j );

				float noise = perlin.PerlinNoise( ( i + seedX ) / relief, 0, ( j + seedZ ) / relief );
				//float noise2 = perlin.PerlinNoise( ( i + seedX2 ) / relief, 0, ( j + seedZ2 ) / relief );

				c.SetAll( noise * 255 );

				/*if( noise > 0.501f ){
					if( noise2 > 0.5f ){
						c.SetF( 0, 1, 0 );
					} else{
						c.SetF( 0.7f, 0.3f, 0 );
					}
				} else{
					c.SetF( 0, 0, 1 );
				}*/
			}
		}
		bmp.WriteFile( ".\\file.bmp" );

	}
}