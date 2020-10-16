#include "Perlin.h"
#include "Bitmap.h"

struct test{
	int x;
	int y;
};

int main(){
	Perlin& perlin = Perlin::GetInstance();
	Bitmap bmp;

	const uint32_t width = 500;

	bmp.Init( width, width );

	std::random_device randDevice;

	while( true ){
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

				int x = i;
				int z = j;

				float noise = perlin.OctavePerlin( x / relief + seedX, 0, z / relief + seedZ, 3, 0.3f);

				/*if( noise > 0.5f ){
					if( noise2 > 0.5f )
						c.SetF( 1, 0, 0 );
					else
						c.SetF( 1, 1, 0 );
				} else{
					if( noise2 > 0.5f )
						c.SetF( 0, 1, 0 );
					else
						c.SetF( 0, 0, 1 );
				}*/

				c.SetAll(noise * 256);
			}
		}
		bmp.WriteFile( ".\\file.bmp" );
	}
}