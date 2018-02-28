/************************************************************/
/*  �{���W�١G����Ϲ�    	    						    */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                       */
/*  �q�l�l��Gt106318025@ntut.org.tw                         */
/*                                                          */
/*  ���D�y�z�G�o�ӵ{���N��J��.raw�ɦǶ��Ϲ���90�ת�����         */
/*                                                          */
/*  ��J�ɮסGlena256.raw					                    */
/*  ��X�ɮסG�Q��imshow��ܤ@�ӤG���x�}(�Ƕ��Ϲ�)              */
/*  �ݨD���ءG�L                                             */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein;
	Mat figure(256, 256, CV_8UC1, Scalar(0));
	int col = 256;//�]�w�n��V�q�n���y�X��pixel
	int row = 256;//�]�w�n�C�V�q�n���y�X��pixel
	int i, j;

	filein = fopen("lena256.raw","rb");
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			figure.data[256 * i+j] = fgetc(filein);
		}
	}
	fclose(filein);
	imshow("lena256_retate.raw", figure);
	waitKey(0);
}