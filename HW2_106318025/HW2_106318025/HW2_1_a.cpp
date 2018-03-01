/************************************************************/
/*  �{���W�١G�v���⭿��j                                    */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                      */
/*  �q�l�l��Gt106318025@ntut.org.tw                         */
/*                                                          */
/*  ���D�y�z�G�Q��row-column replication �h��j�v��            */
/*                                                          */
/*  ��J�ɮסGlena_256.raw				                    */
/*  ��X�ɮסGHW2_1_a.raw                                    */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein = fopen("lena_256.raw", "rb");//�ŧi��J�ɮ�
	FILE *fileout = fopen("HW2_1_a.raw", "wb");//�ŧi��X�ɮ�

	Mat image(256, 256, CV_8UC1, Scalar(0));
	Mat zoomim(512, 512, CV_8UC1, Scalar(0));
	/*----------------------------Ū��.RAW��-------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image.data[j + i*256] = fgetc(filein);
		}
	}
	/*-----------------Zooming2:1(row-column replication)-----------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			zoomim.data[2 * (512 * i + j)] = image.data[j + 256 * i];
			zoomim.data[2 * (512 * i + j) + 1] = image.data[j + 256 * i];
			zoomim.data[512 * (2 * i + 1) + 2 * j] = image.data[j + 256 * i];
			zoomim.data[512 * (2 * i + 1) + 2 * j + 1] = image.data[j + 256 * i];
		}
	}
	/*-------------------------�g.RAW��/��ܼv��---------------------------*/
	fwrite(zoomim.data,1,512*512,fileout);
	imshow("lena_out", zoomim);
	fclose(fileout);
	fclose(filein);
	waitKey(0);
}