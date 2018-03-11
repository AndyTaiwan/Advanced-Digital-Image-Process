#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;
double total=0;
int main()
{
	unsigned char image_char_lena[256 * 256];
	unsigned char image_char_lena_7[256 * 256];
	unsigned char image_char_lena_6[256 * 256];
	unsigned char image_char_lena_5[256 * 256];
	unsigned char image_char_lena_4[256 * 256];
	unsigned char image_char_lena_3[256 * 256];
	unsigned char image_char_lena_2[256 * 256];
	unsigned char image_char_lena_1[256 * 256];
	unsigned char image_char_lena_0[256 * 256];
	unsigned char image_char_baboon[256 * 256];
	unsigned char image_char_baboon_7[256 * 256];
	unsigned char image_char_baboon_7_change[256 * 256];
	unsigned char image_char_baboon_6[256 * 256];
	unsigned char image_char_baboon_5[256 * 256];
	unsigned char image_char_baboon_4[256 * 256];
	unsigned char image_char_baboon_3[256 * 256];
	unsigned char image_char_baboon_2[256 * 256];
	unsigned char image_char_baboon_1[256 * 256];
	unsigned char image_char_baboon_0[256 * 256];
	unsigned char baboon_LSB_changed[256 * 256];
	int binary[8];

	FILE *filein;
	FILE *fileout;
	Mat image_in_lena;
	Mat image_in_baboon;

	/*************************************讀檔*************************************/
	filein = fopen("lenaQ_256.raw", "rb");
	fread(image_char_lena, sizeof(image_char_lena), 1, filein);//將影像資訊讀入char
	fclose(filein);
	filein = fopen("baboon_256.raw", "rb");
	fread(image_char_baboon, sizeof(image_char_baboon), 1, filein);//將影像資訊讀入char
	fclose(filein);
	/************************slice bit-planes from lena************************/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int dec_lena = image_char_lena[j + i * 256];
			for (int a = 7; a >= 0; a--)
			{
				binary[a] = dec_lena % 2;
				dec_lena = dec_lena / 2;
			}
			if (binary[7] && 1)
				image_char_lena_0[j + i * 256] = 255;
			else 
				image_char_lena_0[j + i * 256] = 0;
			if (binary[6] && 1)
				image_char_lena_1[j + i * 256] = 255;
			else
				image_char_lena_1[j + i * 256] = 0;
			if (binary[5] && 1)
				image_char_lena_2[j + i * 256] = 255;
			else
				image_char_lena_2[j + i * 256] = 0;
			if (binary[4] && 1)
				image_char_lena_3[j + i * 256] = 255;
			else
				image_char_lena_3[j + i * 256] = 0;
			if (binary[3] && 1)
				image_char_lena_4[j + i * 256] = 255;
			else
				image_char_lena_4[j + i * 256] = 0;
			if (binary[2] && 1)
				image_char_lena_5[j + i * 256] = 255;
			else
				image_char_lena_5[j + i * 256] = 0;
			if (binary[1] && 1)
				image_char_lena_6[j + i * 256] = 255;
			else
				image_char_lena_6[j + i * 256] = 0;
			if (binary[0] && 1)
				image_char_lena_7[j + i * 256] = 255;
			else
				image_char_lena_7[j + i * 256] = 0;
		}
	}
	/**********************slice bit-planes from baboon**********************/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int dec_baboon = image_char_baboon[j + i * 256];
			for (int a = 7; a >= 0; a--)
			{
				binary[a] = dec_baboon % 2;
				dec_baboon = dec_baboon / 2;
			}
			if (binary[7] && 1)
				image_char_baboon_0[j + i * 256] = 255;
			else
				image_char_baboon_0[j + i * 256] = 0;
			if (binary[6] && 1)
				image_char_baboon_1[j + i * 256] = 255;
			else
				image_char_baboon_1[j + i * 256] = 0;
			if (binary[5] && 1)
				image_char_baboon_2[j + i * 256] = 255;
			else
				image_char_baboon_2[j + i * 256] = 0;
			if (binary[4] && 1)
				image_char_baboon_3[j + i * 256] = 255;
			else
				image_char_baboon_3[j + i * 256] = 0;
			if (binary[3] && 1)
				image_char_baboon_4[j + i * 256] = 255;
			else
				image_char_baboon_4[j + i * 256] = 0;
			if (binary[2] && 1)
				image_char_baboon_5[j + i * 256] = 255;
			else
				image_char_baboon_5[j + i * 256] = 0;
			if (binary[1] && 1)
				image_char_baboon_6[j + i * 256] = 255;
			else
				image_char_baboon_6[j + i * 256] = 0;
			if (binary[0] && 1)
				image_char_baboon_7[j + i * 256] = 255;
			else
				image_char_baboon_7[j + i * 256] = 0;
		}
	}

	Mat image_baboon_LSB = Mat(256, 256, CV_8UC1, image_char_baboon_0);//將char轉成Mat
	putText(image_baboon_LSB, string("Andy Cho"), Point(10, 40), 0, 1, Scalar(0, 0, 0), 3);
	putText(image_baboon_LSB, string("106318025"), Point(30, 140), 0, 1, Scalar(0, 0, 0), 3);
	imshow("image_baboon_LSB", image_baboon_LSB);
	waitKey();

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image_char_baboon_7_change[j + 256 * i] = image_baboon_LSB.data[j + 256 * i];
		}
	}
	//double bin[8];
	//for (int i = 0; i < 256; i++)
	//{
	//	for (int j = 0; j < 256; j++)
	//	{
	//		if (image_char_baboon_7_change[j + 256 * i] == 255)
	//			bin[0] = pow(2, 7);
	//		else
	//			bin[0] = 0;
	//		if (image_char_baboon_6[j + 256 * i] == 255)
	//			bin[1] = pow(2, 6);
	//		else
	//			bin[1] = 0;
	//		if (image_char_baboon_5[j + 256 * i] == 255)
	//			bin[2] = pow(2, 5);
	//		else
	//			bin[2] = 0;
	//		if (image_char_baboon_4[j + 256 * i] == 255)
	//			bin[3] = pow(2, 4);
	//		else
	//			bin[3] = 0;
	//		if (image_char_baboon_3[j + 256 * i] == 255)
	//			bin[4] = pow(2, 3);
	//		else
	//			bin[4] = 0;
	//		if (image_char_baboon_2[j + 256 * i] == 255)
	//			bin[5] = pow(2, 2);
	//		else
	//			bin[5] = 0;
	//		if (image_char_baboon_1[j + 256 * i] == 255)
	//			bin[6] = pow(2, 1);
	//		else
	//			bin[6] = 0;
	//		if (image_char_baboon_0[j + 256 * i] == 255)
	//			bin[7] = pow(2, 0);
	//		else
	//			bin[7] = 0;
	//		unsigned char o, p, q, r, s, t, u, v;
	//		o = bin[0]; p = bin[1]; q = bin[2]; r = bin[3]; s = bin[4]; t = bin[5]; u = bin[6]; v = bin[7];
	//		printf("[%d %d %d %d %d %d %d]", bin[0], bin[1], bin[2], bin[3], bin[4], bin[5], bin[6], bin[7]);
	//		system("pause");
	//		//image_char_baboon_7_change[j + 256 * i] = o + p + q + r + s + t + u + v;
	//	}
	//}
	/*fileout = fopen("HW4_2_a_lena0.raw", "wb");
	fwrite(image_char_lena_7, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena1.raw", "wb");
	fwrite(image_char_lena_6, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena2.raw", "wb");
	fwrite(image_char_lena_5, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena3.raw", "wb");
	fwrite(image_char_lena_4, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena4.raw", "wb");
	fwrite(image_char_lena_3, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena5.raw", "wb");
	fwrite(image_char_lena_2, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena6.raw", "wb");
	fwrite(image_char_lena_1, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_lena7.raw", "wb");
	fwrite(image_char_lena_0, 1, 256 * 256, fileout);
	fclose(fileout);*/
	fileout = fopen("HW4_2_a_baboon0.raw", "wb");
	fwrite(image_char_baboon_7, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon1.raw", "wb");
	fwrite(image_char_baboon_6, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon2.raw", "wb");
	fwrite(image_char_baboon_5, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon3.raw", "wb");
	fwrite(image_char_baboon_4, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon4.raw", "wb");
	fwrite(image_char_baboon_3, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon5.raw", "wb");
	fwrite(image_char_baboon_2, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon6.raw", "wb");
	fwrite(image_char_baboon_1, 1, 256 * 256, fileout);
	fclose(fileout);
	fileout = fopen("HW4_2_a_baboon7.raw", "wb");
	fwrite(image_char_baboon_7_change, 1, 256 * 256, fileout);
	fclose(fileout);
	
}