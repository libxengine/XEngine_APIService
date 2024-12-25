#pragma once
/********************************************************************
//    Created:     2022/03/04  13:37:09
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp
//    File Base:   ModuleHelp_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出帮助模块定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                            枚举类型
//////////////////////////////////////////////////////////////////////////
typedef enum
{
	ENUM_XENGINE_IMAGE_COLOR_BGR2BGRA = 0, //!< add alpha channel to RGB or BGR image
	ENUM_XENGINE_IMAGE_COLOR_RGB2RGBA = ENUM_XENGINE_IMAGE_COLOR_BGR2BGRA,

	ENUM_XENGINE_IMAGE_COLOR_BGRA2BGR = 1, //!< remove alpha channel from RGB or BGR image
	ENUM_XENGINE_IMAGE_COLOR_RGBA2RGB = ENUM_XENGINE_IMAGE_COLOR_BGRA2BGR,

	ENUM_XENGINE_IMAGE_COLOR_BGR2RGBA = 2, //!< convert between RGB and BGR color spaces (with or without alpha channel)
	ENUM_XENGINE_IMAGE_COLOR_RGB2BGRA = ENUM_XENGINE_IMAGE_COLOR_BGR2RGBA,

	ENUM_XENGINE_IMAGE_COLOR_RGBA2BGR = 3,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2RGB = ENUM_XENGINE_IMAGE_COLOR_RGBA2BGR,

	ENUM_XENGINE_IMAGE_COLOR_BGR2RGB = 4,
	ENUM_XENGINE_IMAGE_COLOR_RGB2BGR = ENUM_XENGINE_IMAGE_COLOR_BGR2RGB,

	ENUM_XENGINE_IMAGE_COLOR_BGRA2RGBA = 5,
	ENUM_XENGINE_IMAGE_COLOR_RGBA2BGRA = ENUM_XENGINE_IMAGE_COLOR_BGRA2RGBA,

	ENUM_XENGINE_IMAGE_COLOR_BGR2GRAY = 6, //!< convert between RGB/BGR and grayscale, @ref color_convert_rgb_gray "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2GRAY = 7,
	ENUM_XENGINE_IMAGE_COLOR_GRAY2BGR = 8,
	ENUM_XENGINE_IMAGE_COLOR_GRAY2RGB = ENUM_XENGINE_IMAGE_COLOR_GRAY2BGR,
	ENUM_XENGINE_IMAGE_COLOR_GRAY2BGRA = 9,
	ENUM_XENGINE_IMAGE_COLOR_GRAY2RGBA = ENUM_XENGINE_IMAGE_COLOR_GRAY2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2GRAY = 10,
	ENUM_XENGINE_IMAGE_COLOR_RGBA2GRAY = 11,

	ENUM_XENGINE_IMAGE_COLOR_BGR2BGR565 = 12, //!< convert between RGB/BGR and BGR565 (16-bit images)
	ENUM_XENGINE_IMAGE_COLOR_RGB2BGR565 = 13,
	ENUM_XENGINE_IMAGE_COLOR_BGR5652BGR = 14,
	ENUM_XENGINE_IMAGE_COLOR_BGR5652RGB = 15,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2BGR565 = 16,
	ENUM_XENGINE_IMAGE_COLOR_RGBA2BGR565 = 17,
	ENUM_XENGINE_IMAGE_COLOR_BGR5652BGRA = 18,
	ENUM_XENGINE_IMAGE_COLOR_BGR5652RGBA = 19,

	ENUM_XENGINE_IMAGE_COLOR_GRAY2BGR565 = 20, //!< convert between grayscale to BGR565 (16-bit images)
	ENUM_XENGINE_IMAGE_COLOR_BGR5652GRAY = 21,

	ENUM_XENGINE_IMAGE_COLOR_BGR2BGR555 = 22,  //!< convert between RGB/BGR and BGR555 (16-bit images)
	ENUM_XENGINE_IMAGE_COLOR_RGB2BGR555 = 23,
	ENUM_XENGINE_IMAGE_COLOR_BGR5552BGR = 24,
	ENUM_XENGINE_IMAGE_COLOR_BGR5552RGB = 25,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2BGR555 = 26,
	ENUM_XENGINE_IMAGE_COLOR_RGBA2BGR555 = 27,
	ENUM_XENGINE_IMAGE_COLOR_BGR5552BGRA = 28,
	ENUM_XENGINE_IMAGE_COLOR_BGR5552RGBA = 29,

	ENUM_XENGINE_IMAGE_COLOR_GRAY2BGR555 = 30, //!< convert between grayscale and BGR555 (16-bit images)
	ENUM_XENGINE_IMAGE_COLOR_BGR5552GRAY = 31,

	ENUM_XENGINE_IMAGE_COLOR_BGR2XYZ = 32, //!< convert RGB/BGR to CIE XYZ, @ref color_convert_rgb_xyz "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2XYZ = 33,
	ENUM_XENGINE_IMAGE_COLOR_XYZ2BGR = 34,
	ENUM_XENGINE_IMAGE_COLOR_XYZ2RGB = 35,

	ENUM_XENGINE_IMAGE_COLOR_BGR2YCrCb = 36, //!< convert RGB/BGR to luma-chroma (aka YCC), @ref color_convert_rgb_ycrcb "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2YCrCb = 37,
	ENUM_XENGINE_IMAGE_COLOR_YCrCb2BGR = 38,
	ENUM_XENGINE_IMAGE_COLOR_YCrCb2RGB = 39,

	ENUM_XENGINE_IMAGE_COLOR_BGR2HSV = 40, //!< convert RGB/BGR to HSV (hue saturation value) with H range 0..180 if 8 bit image, @ref color_convert_rgb_hsv "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2HSV = 41,

	ENUM_XENGINE_IMAGE_COLOR_BGR2Lab = 44, //!< convert RGB/BGR to CIE Lab, @ref color_convert_rgb_lab "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2Lab = 45,

	ENUM_XENGINE_IMAGE_COLOR_BGR2Luv = 50, //!< convert RGB/BGR to CIE Luv, @ref color_convert_rgb_luv "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2Luv = 51,
	ENUM_XENGINE_IMAGE_COLOR_BGR2HLS = 52, //!< convert RGB/BGR to HLS (hue lightness saturation) with H range 0..180 if 8 bit image, @ref color_convert_rgb_hls "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2HLS = 53,

	ENUM_XENGINE_IMAGE_COLOR_HSV2BGR = 54, //!< backward conversions HSV to RGB/BGR with H range 0..180 if 8 bit image
	ENUM_XENGINE_IMAGE_COLOR_HSV2RGB = 55,

	ENUM_XENGINE_IMAGE_COLOR_Lab2BGR = 56,
	ENUM_XENGINE_IMAGE_COLOR_Lab2RGB = 57,
	ENUM_XENGINE_IMAGE_COLOR_Luv2BGR = 58,
	ENUM_XENGINE_IMAGE_COLOR_Luv2RGB = 59,
	ENUM_XENGINE_IMAGE_COLOR_HLS2BGR = 60, //!< backward conversions HLS to RGB/BGR with H range 0..180 if 8 bit image
	ENUM_XENGINE_IMAGE_COLOR_HLS2RGB = 61,

	ENUM_XENGINE_IMAGE_COLOR_BGR2HSV_FULL = 66, //!< convert RGB/BGR to HSV (hue saturation value) with H range 0..255 if 8 bit image, @ref color_convert_rgb_hsv "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2HSV_FULL = 67,
	ENUM_XENGINE_IMAGE_COLOR_BGR2HLS_FULL = 68, //!< convert RGB/BGR to HLS (hue lightness saturation) with H range 0..255 if 8 bit image, @ref color_convert_rgb_hls "color conversions"
	ENUM_XENGINE_IMAGE_COLOR_RGB2HLS_FULL = 69,

	ENUM_XENGINE_IMAGE_COLOR_HSV2BGR_FULL = 70, //!< backward conversions HSV to RGB/BGR with H range 0..255 if 8 bit image
	ENUM_XENGINE_IMAGE_COLOR_HSV2RGB_FULL = 71,
	ENUM_XENGINE_IMAGE_COLOR_HLS2BGR_FULL = 72, //!< backward conversions HLS to RGB/BGR with H range 0..255 if 8 bit image
	ENUM_XENGINE_IMAGE_COLOR_HLS2RGB_FULL = 73,

	ENUM_XENGINE_IMAGE_COLOR_LBGR2Lab = 74,
	ENUM_XENGINE_IMAGE_COLOR_LRGB2Lab = 75,
	ENUM_XENGINE_IMAGE_COLOR_LBGR2Luv = 76,
	ENUM_XENGINE_IMAGE_COLOR_LRGB2Luv = 77,

	ENUM_XENGINE_IMAGE_COLOR_Lab2LBGR = 78,
	ENUM_XENGINE_IMAGE_COLOR_Lab2LRGB = 79,
	ENUM_XENGINE_IMAGE_COLOR_Luv2LBGR = 80,
	ENUM_XENGINE_IMAGE_COLOR_Luv2LRGB = 81,

	ENUM_XENGINE_IMAGE_COLOR_BGR2YUV = 82, //!< convert between RGB/BGR and YUV
	ENUM_XENGINE_IMAGE_COLOR_RGB2YUV = 83,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR = 84,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB = 85,

	//! YUV 4:2:0 family to RGB
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_NV12 = 90,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_NV12 = 91,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_NV21 = 92,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_NV21 = 93,
	ENUM_XENGINE_IMAGE_COLOR_YUV420sp2RGB = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_NV21,
	ENUM_XENGINE_IMAGE_COLOR_YUV420sp2BGR = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_NV21,

	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_NV12 = 94,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_NV12 = 95,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_NV21 = 96,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_NV21 = 97,
	ENUM_XENGINE_IMAGE_COLOR_YUV420sp2RGBA = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_NV21,
	ENUM_XENGINE_IMAGE_COLOR_YUV420sp2BGRA = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_NV21,

	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YV12 = 98,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YV12 = 99,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_IYUV = 100,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_IYUV = 101,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_I420 = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_IYUV,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_I420 = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_IYUV,
	ENUM_XENGINE_IMAGE_COLOR_YUV420p2RGB = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YV12,
	ENUM_XENGINE_IMAGE_COLOR_YUV420p2BGR = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YV12,

	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YV12 = 102,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YV12 = 103,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_IYUV = 104,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_IYUV = 105,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_I420 = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_IYUV,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_I420 = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_IYUV,
	ENUM_XENGINE_IMAGE_COLOR_YUV420p2RGBA = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YV12,
	ENUM_XENGINE_IMAGE_COLOR_YUV420p2BGRA = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YV12,

	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420 = 106,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_NV21 = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_NV12 = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YV12 = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_IYUV = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_I420 = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,
	ENUM_XENGINE_IMAGE_COLOR_YUV420sp2GRAY = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,
	ENUM_XENGINE_IMAGE_COLOR_YUV420p2GRAY = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_420,

	//! YUV 4:2:2 family to RGB
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_UYVY = 107,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_UYVY = 108,
	//ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_VYUY = 109,
	//ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_VYUY = 110,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_Y422 = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_Y422 = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_UYNV = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_UYNV = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_UYVY,

	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_UYVY = 111,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_UYVY = 112,
	//ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_VYUY = 113,
	//ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_VYUY = 114,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_Y422 = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_Y422 = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_UYNV = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_UYNV = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_UYVY,

	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YUY2 = 115,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YUY2 = 116,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YVYU = 117,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YVYU = 118,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YUYV = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YUYV = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YUNV = ENUM_XENGINE_IMAGE_COLOR_YUV2RGB_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YUNV = ENUM_XENGINE_IMAGE_COLOR_YUV2BGR_YUY2,

	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YUY2 = 119,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YUY2 = 120,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YVYU = 121,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YVYU = 122,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YUYV = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YUYV = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YUNV = ENUM_XENGINE_IMAGE_COLOR_YUV2RGBA_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YUNV = ENUM_XENGINE_IMAGE_COLOR_YUV2BGRA_YUY2,

	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_UYVY = 123,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YUY2 = 124,
	//CV_YUV2GRAY_VYUY    = CV_YUV2GRAY_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_Y422 = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_UYNV = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_UYVY,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YVYU = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YUYV = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YUY2,
	ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YUNV = ENUM_XENGINE_IMAGE_COLOR_YUV2GRAY_YUY2,

	//! alpha premultiplication
	ENUM_XENGINE_IMAGE_COLOR_RGBA2mRGBA = 125,
	ENUM_XENGINE_IMAGE_COLOR_mRGBA2RGBA = 126,

	//! RGB to YUV 4:2:0 family
	ENUM_XENGINE_IMAGE_COLOR_RGB2YUV_I420 = 127,
	ENUM_XENGINE_IMAGE_COLOR_BGR2YUV_I420 = 128,
	ENUM_XENGINE_IMAGE_COLOR_RGB2YUV_IYUV = ENUM_XENGINE_IMAGE_COLOR_RGB2YUV_I420,
	ENUM_XENGINE_IMAGE_COLOR_BGR2YUV_IYUV = ENUM_XENGINE_IMAGE_COLOR_BGR2YUV_I420,

	ENUM_XENGINE_IMAGE_COLOR_RGBA2YUV_I420 = 129,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2YUV_I420 = 130,
	ENUM_XENGINE_IMAGE_COLOR_RGBA2YUV_IYUV = ENUM_XENGINE_IMAGE_COLOR_RGBA2YUV_I420,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2YUV_IYUV = ENUM_XENGINE_IMAGE_COLOR_BGRA2YUV_I420,
	ENUM_XENGINE_IMAGE_COLOR_RGB2YUV_YV12 = 131,
	ENUM_XENGINE_IMAGE_COLOR_BGR2YUV_YV12 = 132,
	ENUM_XENGINE_IMAGE_COLOR_RGBA2YUV_YV12 = 133,
	ENUM_XENGINE_IMAGE_COLOR_BGRA2YUV_YV12 = 134,

	//! Demosaicing, see @ref color_convert_bayer "color conversions" for additional information
	ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR = 46, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR = 47, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR = 48, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR = 49, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGR = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGR = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGR = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGR = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR,

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGR,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGR,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGR,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGR,

	ENUM_XENGINE_IMAGE_COLOR_BayerBG2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2RGB = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_BayerBG2GRAY = 86, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2GRAY = 87, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2GRAY = 88, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2GRAY = 89, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2GRAY = ENUM_XENGINE_IMAGE_COLOR_BayerBG2GRAY,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2GRAY = ENUM_XENGINE_IMAGE_COLOR_BayerGB2GRAY,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2GRAY = ENUM_XENGINE_IMAGE_COLOR_BayerRG2GRAY,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2GRAY = ENUM_XENGINE_IMAGE_COLOR_BayerGR2GRAY,

	//! Demosaicing using Variable Number of Gradients
	ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR_VNG = 62, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR_VNG = 63, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR_VNG = 64, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR_VNG = 65, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGR_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR_VNG,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGR_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR_VNG,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGR_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR_VNG,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGR_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR_VNG,

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGR_VNG,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGR_VNG,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGR_VNG,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGR_VNG,

	ENUM_XENGINE_IMAGE_COLOR_BayerBG2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR_VNG, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR_VNG, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR_VNG, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2RGB_VNG = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR_VNG, //!< equivalent to GBRG Bayer pattern

	//! Edge-Aware Demosaicing
	ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR_EA = 135, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR_EA = 136, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR_EA = 137, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR_EA = 138, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGR_EA = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR_EA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGR_EA = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR_EA,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGR_EA = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR_EA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGR_EA = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR_EA,

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGR_EA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGR_EA,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGR_EA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGR_EA,

	ENUM_XENGINE_IMAGE_COLOR_BayerBG2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGR_EA, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGR_EA, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGR_EA, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2RGB_EA = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGR_EA, //!< equivalent to GBRG Bayer pattern

	//! Demosaicing with alpha channel
	ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGRA = 139, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGRA = 140, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGRA = 141, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGRA = 142, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGRA = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGRA = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGRA = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGRA = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGRA,

	ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BayerBGGR2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerRGGB2BGRA,
	ENUM_XENGINE_IMAGE_COLOR_BayerGBRG2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerGRBG2BGRA,

	ENUM_XENGINE_IMAGE_COLOR_BayerBG2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerRG2BGRA, //!< equivalent to RGGB Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGB2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerGR2BGRA, //!< equivalent to GRBG Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerRG2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerBG2BGRA, //!< equivalent to BGGR Bayer pattern
	ENUM_XENGINE_IMAGE_COLOR_BayerGR2RGBA = ENUM_XENGINE_IMAGE_COLOR_BayerGB2BGRA, //!< equivalent to GBRG Bayer pattern

	ENUM_XENGINE_IMAGE_COLOR_COLORCVT_MAX = 143
}ENUM_XENGINE_IMAGE_COLOR_INFO;
//////////////////////////////////////////////////////////////////////////
//                       导出回调函数
//////////////////////////////////////////////////////////////////////////
typedef void(CALLBACK* CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT)(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XPVOID lParam);
//套接字测试回调:测试句柄，测试的服务器地址，测试的端口，当前测试次数，失败次数,成功次数,状态:0成功报告,1失败报告,2结束报告,自定义参数
typedef void(CALLBACK* CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST)(XNETHANDLE xhToken, LPCXSTR lpszAddr, int nPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus, XPVOID lParam);
//////////////////////////////////////////////////////////////////////////
//                       导出数据结构
//////////////////////////////////////////////////////////////////////////
//计时器
typedef struct 
{
	__int64x dwUserTime;                                                  //用户存在时间
	__int64x dwPacketTime;                                                //包时间,拿到包后的存活时间
	__int64x dwKeepAlive;                                                 //保活计时器时间,经过网络时间
	unsigned short int usTTL : 1;                                         //路由数
}P2XP_TIMER_INFOMATION, * LPP2XP_TIMER_INFOMATION;
//一个节点信息
typedef struct 
{
	XENGINE_P2XPPEER_PROTOCOL st_PeerAddr;                                //P2P通信的时候使用的地址（客户方使用）
	P2XP_TIMER_INFOMATION st_PeerTimer;                                   //节点时间信息
	bool bIsLogin;
}XENGINE_P2XP_PEERINFO, * LPNETENGINE_P2XP_PEERINFO;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleHelp_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的身份证帮助函数                         */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证号生日
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO* pSt_IDInfo);
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证的校验码是否正确
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO* pSt_IDInfo);
/************************************************************************/
/*                         导出的语言转换帮助函数                       */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_Translation_Convert
函数功能：翻译类型转换
 参数.一：enTranslationType
  In/Out：In
  类型：枚举型
  可空：N
  意思：输入要转换的类型
 参数.二：ptszTranslationType
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, XCHAR* ptszTranslationType);
/************************************************************************/
/*                       节点管理器导出函数                             */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_P2PClient_Init
函数功能：初始化P2P客户端
 参数.一：nTimeout
  In/Out：In
  类型：整数型
  可空：N
  意思：输入超时时间,秒
 参数.二：fpCall_P2PClient
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：P2P客户端导出信息
 参数.三：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_Init(int nTimeout, CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT fpCall_P2PClient, XPVOID lParam = NULL);
/********************************************************************
函数名称：ModuleHelp_P2PClient_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_Destory();
/********************************************************************
函数名称：ModuleHelp_P2PClient_Add
函数功能：添加一个客户到一个节点信息
 参数.一：pSt_PeerInfo
  In/Out：In
  类型：结构体指针
  可空：N
  意思：要添加的节点信息
返回值
  类型：逻辑型
  意思：是否添加成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO * pSt_PeerInfo);
/********************************************************************
函数名称：ModuleHelp_P2PClient_GetLan
函数功能：获取局域网IP地址列表
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要查找地址信息
 参数.二：pppSt_P2XPClient
  In/Out：Out
  类型：三级指针
  可空：N
  意思：导出局域网IP地址列表
 参数.三：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出地址列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：参数二需要调用基础库的BaseLib_Memory_Free函数进行内存释放
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL * **pppSt_P2XPClient, int* pInt_ListCount);
/********************************************************************
函数名称：ModuleHelp_P2PClient_GetLList
函数功能：获取同一公网下所有局域网主IP列表
 参数.一：lpszPubAddr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要获取的IP地址
 参数.二：pppszP2XPClient
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出内网主IP地址列表
 参数.三：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：参数二需要调用基础库的BaseLib_Memory_Free函数进行内存释放
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_GetLList(LPCXSTR lpszPubAddr, XCHAR * **pppszP2XPClient, int* pInt_ListCount);
/********************************************************************
函数名称：ModuleHelp_P2PClient_GetWList
函数功能：获取所有连接到的公网地址列表
 参数.一：pppszP2XPClient
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出地址列表
 参数.二：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_GetWList(XCHAR * **pppszP2XPClient, int* pInt_ListCount);
/********************************************************************
函数名称：ModuleHelp_P2PClient_Delete
函数功能：删除一个指定的节点
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要删除的节点地址
返回值
  类型：逻辑型
  意思：是否成功删除
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol);
/********************************************************************
函数名称：ModuleHelp_P2PClient_DelAll
函数功能：清空节点列表数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_DelAll();
/********************************************************************
函数名称：ModuleHelp_P2PClient_Heart
函数功能：触发一次心跳
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要操作的节点地址
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_P2PClient_Heart(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol);
/************************************************************************/
/*                       分布式锁导出函数                               */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_Locker_Create
函数功能：创建锁
 参数.一：pxhToken
  In/Out：Out
  类型：句柄
  可空：N
  意思：输出创建的锁句柄,并且会打开这个锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_Create(XNETHANDLE* pxhToken);
/********************************************************************
函数名称：ModuleHelp_Locker_OPen
函数功能：打开一个锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_OPen(XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleHelp_Locker_ReadLock
函数功能：读加锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_ReadLock(XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleHelp_Locker_ReadUNLock
函数功能：读解锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_ReadUNLock(XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleHelp_Locker_WriteLock
函数功能：写加锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_WriteLock(XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleHelp_Locker_WriteUNLock
函数功能：写解锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_WriteUNLock(XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleHelp_Locker_Close
函数功能：关闭锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_Locker_Close(XNETHANDLE xhToken);
/************************************************************************/
/*                       二维码导出函数                                 */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_QRCode_QREncodecFile
函数功能：二维码生成器
 参数.一：lpszFileName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要生成的图片位置
 参数.二：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要编码的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_QRCode_QREncodecFile(LPCXSTR lpszFileName, LPCXSTR lpszMsgBuffer);
/********************************************************************
函数名称：ModuleHelp_QRCode_QREncodecMemory
函数功能：编码数据为二维码格式PNG图片
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要编码的数据
 参数.二：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出编码的数据
 参数.三：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出数据大小
  意思：输出数据大小
 参数.四：lpszFmt
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入文件格式.png
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_QRCode_QREncodecMemory(LPCXSTR lpszMsgBuffer, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszFmt);
/********************************************************************
函数名称：ModuleHelp_QRCode_QRDecodecFile
函数功能：从文件解码二维码
 参数.一：lpszFileName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的图片地址
 参数.二：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出识别到的内容
 参数.三：lpszDetectProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.四：lpszDetectModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.五：lpszSrProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.六：lpszSrModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_QRCode_QRDecodecFile(LPCXSTR lpszFileName, XCHAR* ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel);
/********************************************************************
函数名称：ModuleHelp_QRCode_QRDecodecMemory
函数功能：从内存解析二维码
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的图片缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出识别到的内容
 参数.四：lpszDetectProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.五：lpszDetectModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.六：lpszSrProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.七：lpszSrModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_QRCode_QRDecodecMemory(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel);
/************************************************************************/
/*                       网络测试导出函数                               */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_SocketTest_StartConnect
函数功能：测试连接
 参数.一：pxhToken
  In/Out：Out
  类型：句柄
  可空：N
  意思：导出句柄
 参数.二：pSt_ReConnect
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要测试的属性
 参数.三：fpCall_ReConnect
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：测试回调信息
 参数.四：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数自定义参数
返回值
  类型：句柄型
  意思：成功返回连接的句柄,失败返回NULL
备注：链接测试函数，链接一次后就关闭
*********************************************************************/
extern "C" bool ModuleHelp_SocketTest_StartConnect(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_RECONNECT* pSt_ReConnect, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_ReConnect, XPVOID lParam = NULL);
/********************************************************************
函数名称：ModuleHelp_SocketTest_GetConnect
函数功能：获取是否在处理中
 参数.一：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入操作的句柄
 参数.二：pbRun
  In/Out：Out
  类型：逻辑型指针
  可空：N
  意思：输出是否在运行
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_SocketTest_GetConnect(XNETHANDLE xhToken, bool* pbRun);
/********************************************************************
函数名称：ModuleHelp_SocketTest_StopConnect
函数功能：停止短连接测试
 参数.一：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入测试的句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_SocketTest_StopConnect(XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleHelp_SocketTest_StartDatas
函数功能：数据包测试函数
 参数.一：pxhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输出创建的句柄
 参数.二：pSt_SocketDatas
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要测试的属性
 参数.三：fpCall_DataTest
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：测试回调信息
 参数.四：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_SocketTest_StartDatas(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_DATAS* pSt_SocketDatas, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_DataTest, bool bTCP = true, XPVOID lParam = NULL);
/********************************************************************
函数名称：ModuleHelp_SocketTest_GetDatas
函数功能：获取是否在处理中
 参数.一：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入操作的句柄
 参数.二：pbRun
  In/Out：Out
  类型：逻辑型指针
  可空：N
  意思：输出是否在运行
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_SocketTest_GetDatas(XNETHANDLE xhToken, bool* pbRun);
/************************************************************************
函数名称：ModuleHelp_SocketTest_DatasStop
函数功能：停止大数据包测试
  参数.一：xhToken
   In/Out：In
   类型：句柄
   可空：N
   意思：输入测试的句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
************************************************************************/
extern "C" bool ModuleHelp_SocketTest_StopDatas(XNETHANDLE xhToken);
/************************************************************************/
/*                       图像处理导出函数                               */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_ImageGet_Attr
函数功能：获取图像属性
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入图像内存
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入图像大小
 参数.三：pSt_BaseInfo
  In/Out：Out
  类型：数据结构指针
  可空：Y
  意思：输出图像基本信息
 参数.四：pSt_ExtAttr
  In/Out：Out
  类型：数据结构指针
  可空：Y
  意思：输出图像扩展信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageGet_Attr(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_IMGBASEATTR* pSt_BaseInfo = NULL, XENGINE_IMGEXTATTR* pSt_ExtAttr = NULL);
/********************************************************************
函数名称：ModuleHelp_ImageGet_TextInit
函数功能：初始化图像文字转换
 参数.一：lpszPath
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入文本语言数据路径
 参数.二：lpszLanguage
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入加载的语言数据.通过+连接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageGet_TextInit(LPCXSTR lpszPath, LPCXSTR lpszLanguage);
/********************************************************************
函数名称：ModuleHelp_ImageGet_TextGet
函数功能：获取图像文本内容
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入图像内存
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入图像大小
 参数.三：ppptszListStr
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出获取到的内容列表
 参数.四：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageGet_TextGet(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR*** ppptszListStr, int* pInt_ListCount);
/********************************************************************
函数名称：ModuleHelp_ImageGet_TextDestory
函数功能：销毁文本提取功能
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageGet_TextDestory();
/********************************************************************
函数名称：ModuleHelp_ImageSet_Resolution
函数功能：分辨率调整
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nWidth
  In/Out：In
  类型：整数型
  可空：N
  意思：输入调整后的宽
 参数.七：nHeight
  In/Out：In
  类型：整数型
  可空：N
  意思：输入调整后的高
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageSet_Resolution(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nWidth, int nHeight);
/********************************************************************
函数名称：ModuleHelp_ImageSet_Flip
函数功能：图像翻转
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nOPMethod
  In/Out：In
  类型：整数型
  可空：N
  意思：输入图像翻转方式,0:上下,1:左右,-1:上下左右同时
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageSet_Flip(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nOPMethod);
/********************************************************************
函数名称：ModuleHelp_ImageSet_ColorCvt
函数功能：色彩空间转换
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：enColorInfo
  In/Out：In
  类型：整数型
  可空：N
  意思：输入要转换的类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageSet_ColorCvt(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, ENUM_XENGINE_IMAGE_COLOR_INFO enColorInfo);
/********************************************************************
函数名称：ModuleHelp_ImageSet_Ligth
函数功能：亮度与对比度调整
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nGamma
  In/Out：In
  类型：整数型
  可空：N
  意思：输入要调整的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageSet_Ligth(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nGamma);
/********************************************************************
函数名称：ModuleHelp_ImageSet_Level
函数功能：图像压缩级别调整
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .jpeg .webp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nLevel
  In/Out：In
  类型：整数型
  可空：N
  意思：输入压缩后者质量级别.根据类型不同,此值作用不同
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_ImageSet_Level(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nLevel);