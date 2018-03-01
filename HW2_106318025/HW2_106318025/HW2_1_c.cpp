/************************************************************/
/*  �{���W�١G�v���⭿�Y�p                                    */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                      */
/*  �q�l�l��Gt106318025@ntut.org.tw                        */
/*                                                         */
/*  ���D�y�z�G�Q��row-column replication                     */
/*           1.����Y�p�v���A                                */
/*           2.�Q��XnView�N�v���ҽk�ƫ�A�Y�p�A               */ 
/*           ��̤���C                                      */
/*                                                          */
/*  ��J�ɮסGlena_256.raw				                    */
/*           lena_256_blurring.raw                          */
/*  ��X�ɮסGHW2_1_c_with blurring.raw                      */
/*           HW2_1_c_without blurring.raw                   */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein_1 = fopen("lena_256.raw", "rb");//�ŧi��J�ɮ�
	FILE *filein_2 = fopen("lena_256_blurring.raw", "rb");//�gXnView�ҽk�ƿ�X���v��
	FILE *fileout_1 = fopen("HW2_1_c_with blurring.raw", "wb");//�ŧi��X�ɮ�
	FILE *fileout_2 = fopen("HW2_1_c_without blurring.raw", "wb");

	Mat image_1(256, 256, CV_8UC1, Scalar(0));
	Mat image_2(256, 256, CV_8UC1, Scalar(0));
	Mat shrinkim_1(128, 128, CV_8UC1, Scalar(0));
	Mat shrinkim_2(128, 128, CV_8UC1, Scalar(0));
	/*----------------------------Ū��.RAW��-------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image_1.data[j + i * 256] = fgetc(filein_1);
		}
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image_2.data[j + i * 256] = fgetc(filein_2);
		}
	}
	/*-----------------Shrinking1:2(row-column replication)-----------------*/
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			shrinkim_1.data[j + 128 * i] = image_1.data[j * 2 + 256 * 2 * i];
		}
	}
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			shrinkim_2.data[j + 128 * i] = image_2.data[j * 2 + 256 * 2 * i];
		}
	}
	/*-------------------------�g.RAW��/��ܼv��---------------------------*/
	fwrite(shrinkim_1.data, 1, 128 * 128, fileout_1);
	fwrite(shrinkim_2.data, 1, 128 * 128, fileout_2);
	imshow("lena_out_1", shrinkim_1);
	imshow("lena_out_2", shrinkim_2);
	fclose(fileout_1);
	fclose(filein_1);
	fclose(fileout_2);
	fclose(filein_2);
	waitKey(0);
}