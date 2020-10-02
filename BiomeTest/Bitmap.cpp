#include "Bitmap.h"

static const uint32_t BF_TYPE = ( uint32_t( 'M' ) << 8 ) | 'B';

#pragma pack(2)
struct BitmapHeader{
	uint16_t  bfType;       /**< ファイルタイプ、必ず"BM" */
	uint32_t  bfSize;       /**< ファイルサイズ */
	uint16_t  bfReserved1 = 0;  /**< リザーブ */
	uint16_t  bfReserved2 = 0;  /**< リザーブ */
	uint32_t  bfOffBytes;   /**< 先頭から画像情報までのオフセット */
};

#pragma pack()
struct BitmapInfoHeader{
	uint32_t biSize;         /**< この構造体のサイズ */
	int32_t biWidth;         /**< 画像の幅 */
	int32_t biHeight;        /**< 画像の高さ */
	uint16_t biPlanes;       /**< 画像の枚数、通常1 */
	uint16_t biBitCount;     /**< 一色のビット数 */
	uint32_t biCompression;  /**< 圧縮形式 */
	uint32_t biSizeImage;    /**< 画像領域のサイズ */
	int32_t biXPelsPerMeter; /**< 画像の横方向解像度情報 */
	int32_t biYPelsPerMeter; /**< 画像の縦方向解像度情報*/
	uint32_t biClrUsed;      /**< カラーパレットのうち実際に使っている色の個数 */
	uint32_t biClrImportant; /**< カラーパレットのうち重要な色の数 */
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

	//幅のbyte数を4の倍数にそろえる
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
