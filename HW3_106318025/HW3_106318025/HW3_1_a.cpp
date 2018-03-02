/************************************************************/
/*  �{���W�١GNegative the image								*/
/*  �@�̩m�W�G����											*/
/*	    �Ǹ�:106318025										*/
/*  ���ɱб¡GDr.������										*/
/*  �q�l�l��Gt106318025@ntut.org.tw							*/
/*                                                          */
/*  ���D�y�z�G�Nlena512.raw ���t���ĪG						*/
/*                                                          */
/*  ��J�ɮסGlena512.raw				                    */
/*  ��X�ɮסGHW3_1_a.raw                                    */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	FILE *filein = fopen("lena512.raw", "rb");//�ŧi��J�ɮ�
	FILE *fileout = fopen("HW3_1_a.raw", "wb");//�ŧi��X�ɮ�
	Mat image(512, 512, CV_8UC1, Scalar(0));
	/*----------------------------Ū��.RAW��-------------------------------*/
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			image.data[j + i * 512] = 255 - fgetc(filein); //�t���ĪG
		}
	}
	fwrite(image.data,1,512*512,fileout);
	imshow("HW3_1_a",image);
	waitKey();
	fclose(filein);
	fclose(fileout);
}
