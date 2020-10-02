#include "Bitmap.h"

static const uint32_t BF_TYPE = ( uint32_t( 'M' ) << 8 ) | 'B';

#pragma pack(2)
struct BitmapHeader{
	uint16_t  bfType;       /**< �t�@�C���^�C�v�A�K��"BM" */
	uint32_t  bfSize;       /**< �t�@�C���T�C�Y */
	uint16_t  bfReserved1 = 0;  /**< ���U�[�u */
	uint16_t  bfReserved2 = 0;  /**< ���U�[�u */
	uint32_t  bfOffBytes;   /**< �擪����摜���܂ł̃I�t�Z�b�g */
};

#pragma pack()
struct BitmapInfoHeader{
	uint32_t biSize;         /**< ���̍\���̂̃T�C�Y */
	int32_t biWidth;         /**< �摜�̕� */
	int32_t biHeight;        /**< �摜�̍��� */
	uint16_t biPlanes;       /**< �摜�̖����A�ʏ�1 */
	uint16_t biBitCount;     /**< ��F�̃r�b�g�� */
	uint32_t biCompression;  /**< ���k�`�� */
	uint32_t biSizeImage;    /**< �摜�̈�̃T�C�Y */
	int32_t biXPelsPerMeter; /**< �摜�̉������𑜓x��� */
	int32_t biYPelsPerMeter; /**< �摜�̏c�����𑜓x���*/
	uint32_t biClrUsed;      /**< �J���[�p���b�g�̂������ۂɎg���Ă���F�̌� */
	uint32_t biClrImportant; /**< �J���[�p���b�g�̂����d�v�ȐF�̐� */
};

void Bitmap::Init( uint32_t width, uint32_t height ){
	m_width = width;
	m_height = height;
	m_image.resize( width * height );
}

template<class T>
inline void Write(std::ofstream& ofs , T& v){
	ofs.write( reinterpret_cast<char*>( &v ), sizeof( T ) );
}

void Bitmap::WriteFile( const char* filePath ){
	std::ofstream ofs(filePath, std::ios::out | std::ios::binary);

	if( !ofs ){
		abort();
	}

	//����byte����4�̔{���ɂ��낦��
	int stride = ( m_width * 3 + 3 ) / 4 * 4;
	int sub_stride = stride - m_width * 3;

	BitmapHeader header;
	header.bfType = BF_TYPE;
	header.bfSize = sizeof( BitmapHeader ) + sizeof( BitmapInfoHeader ) + stride * m_height;
	header.bfOffBytes = sizeof( BitmapHeader ) + sizeof( BitmapInfoHeader );

	BitmapInfoHeader info;
	info.biSize = sizeof( BitmapInfoHeader );
	info.biWidth = m_width;
	info.biHeight = m_height;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = 0;
	info.biSizeImage = stride * m_height;
	info.biXPelsPerMeter = 0;
	info.biYPelsPerMeter = 0;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	Write( ofs, header );
	Write( ofs, info );

	for( int y = 0; y < m_height; y++ ){
		for( int x = 0; x < m_width; x++ ){

			BitColor& color = m_image[y * m_width + x];

			ofs.write( reinterpret_cast<char*>( &color ), 3 );
		}

		char pad[2]{};

		ofs.write( pad, sub_stride );
	}

	ofs.close();
}
