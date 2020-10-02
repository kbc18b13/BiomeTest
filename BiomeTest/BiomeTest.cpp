#include "Perlin.h"
#include "Bitmap.h"

int main(){
	std::random_device randev;
	Perlin& perlin = Perlin::GetInstance(randev());
	Bitmap bmp;

	Bitmap bmp2;

	const uint32_t width = 500;

	bmp.Init( width, width );
	bmp2.Init( width, width );

	while( true ){
		std::cout << "シード:" << perlin.GetSeed() << "\n";

		float relief;

		std::cout << "reliefの値を入力してください。>> ";
		std::cin >> relief;

		if( relief == -1 ){
			break;
		}

		for( int i = 0; i < width; i++ ){
			for( int j = 0; j < width; j++ ){
				auto& c = bmp.At( i, j );
				auto& c2 = bmp2.At( i, j );

				float noise = perlin.PerlinNoise( i / relief, 0, j / relief );

				c.SetAll( noise * 255 );

				if( noise > 0.5f ){
					c2.SetF( 0, 1, 0 );
				} else{
					c2.SetF( 0, 0, 1 );
				}
			}
		}
		perlin.SetSeed( randev() );
		bmp.WriteFile( ".\\file.bmp" );
		bmp2.WriteFile( ".\\file2.bmp" );
	}
}