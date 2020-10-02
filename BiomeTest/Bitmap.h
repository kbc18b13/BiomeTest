#pragma once

struct BitColor{
	uint8_t b = 0;
	uint8_t g = 0;
	uint8_t r = 0;

	void SetAll( uint8_t v){
		Set( v, v, v );
	}
	
	void Set( uint8_t _r, uint8_t _g, uint8_t _b ){
		r = _r; g = _g; b = _b;
	}

	void SetF( float _r, float _g, float _b ){
		Set( static_cast<uint8_t>( _r*255 ),
			 static_cast<uint8_t>( _g*255 ),
			 static_cast<uint8_t>( _b*255 ) );
	}
};

class Bitmap{
public:
	void Init( uint32_t width, uint32_t height );

	void WriteFile( const char* filePath );

	BitColor& At( uint32_t x, uint32_t y ){
		int _y = m_height - y - 1;
		return m_image[x + _y * m_width];
	}

private:
	uint32_t m_width = 0;
	uint32_t m_height = 0;

	std::vector<BitColor> m_image;
};

