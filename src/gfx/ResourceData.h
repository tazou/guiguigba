// ================================================================================
// File automatically generated by katie.exe v1.5
// http://www.console-dev.de
// 
// WARNING: All changes made in this file will be lost!
// ================================================================================

#ifndef SRC_GFX_RESOURCEDATA_H
#define SRC_GFX_RESOURCEDATA_H

#ifdef __cplusplus
	extern "C"{
#endif

// src/gfx/raw/imgBackground.map
#define RES_IMGBACKGROUND_MAP	0
#define RES_IMGBACKGROUND_MAP_SIZE	1280
#define RES_IMGBACKGROUND_MAP_SIZEPADDED	1280
#define RES_IMGBACKGROUND_MAP_SIZE16	640
#define RES_IMGBACKGROUND_MAP_SIZE16PADDED	640
#define RES_IMGBACKGROUND_MAP_SIZE32	320
#define RES_IMGBACKGROUND_MAP_SIZE32PADDED	320

// src/gfx/raw/imgBackground.raw
#define RES_IMGBACKGROUND_RAW	1280
#define RES_IMGBACKGROUND_RAW_SIZE	24576
#define RES_IMGBACKGROUND_RAW_SIZEPADDED	24576
#define RES_IMGBACKGROUND_RAW_SIZE16	12288
#define RES_IMGBACKGROUND_RAW_SIZE16PADDED	12288
#define RES_IMGBACKGROUND_RAW_SIZE32	6144
#define RES_IMGBACKGROUND_RAW_SIZE32PADDED	6144

// src/gfx/raw/screen.pal
#define RES_SCREEN_PAL	25856
#define RES_SCREEN_PAL_SIZE	512
#define RES_SCREEN_PAL_SIZEPADDED	512
#define RES_SCREEN_PAL_SIZE16	256
#define RES_SCREEN_PAL_SIZE16PADDED	256
#define RES_SCREEN_PAL_SIZE32	128
#define RES_SCREEN_PAL_SIZE32PADDED	128

// src/gfx/raw/text.map
#define RES_TEXT_MAP	26368
#define RES_TEXT_MAP_SIZE	320
#define RES_TEXT_MAP_SIZEPADDED	320
#define RES_TEXT_MAP_SIZE16	160
#define RES_TEXT_MAP_SIZE16PADDED	160
#define RES_TEXT_MAP_SIZE32	80
#define RES_TEXT_MAP_SIZE32PADDED	80

// src/gfx/raw/text.raw
#define RES_TEXT_RAW	26688
#define RES_TEXT_RAW_SIZE	6016
#define RES_TEXT_RAW_SIZEPADDED	6016
#define RES_TEXT_RAW_SIZE16	3008
#define RES_TEXT_RAW_SIZE16PADDED	3008
#define RES_TEXT_RAW_SIZE32	1504
#define RES_TEXT_RAW_SIZE32PADDED	1504


#define ResData(_identifier)	((const void*)&__ResourceData__[_identifier])
#define ResData8(_identifier)	((const unsigned char*)&__ResourceData__[_identifier])
#define ResData8X(_identifier, _index)	((const unsigned char*)&__ResourceData__[(_identifier)+(_index)])
#define ResData16(_identifier)	((const unsigned short*)&__ResourceData__[_identifier])
#define ResData16X(_identifier, _index)	((const unsigned short*)&__ResourceData__[(_identifier)+((_index)<<1)])
#define ResData32(_identifier)	((const unsigned long*)&__ResourceData__[_identifier])
#define ResData32X(_identifier, _index)	((const unsigned long*)&__ResourceData__[(_identifier)+((_index)<<2)])
#define ResDataType(_type, _identifier)	((const _type*)&__ResourceData__[_identifier])
#define ResDataTypeX(_type, _identifier, _index)	((const _type*)&__ResourceData__[(_identifier)+((_index)*sizeof(_type)])


extern const unsigned char __ResourceData__[];

#ifdef __cplusplus
	}
#endif

#endif // SRC_GFX_RESOURCEDATA_H

