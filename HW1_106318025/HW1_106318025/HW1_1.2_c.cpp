/************************************************************/
/*  �{���W�١G���.raw�ɹϹ�	    						    */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                       */
/*  �q�l�l��Gt106318025@ntut.org.tw                         */
/*                                                          */
/*  ���D�y�z�G�o�ӵ{���N��ܿ�J��.raw�ɦǶ��Ϲ�                */
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
	Mat figure(256, 256, CV_8UC1, Scalar(0));//�Q��OpenCV��ܮw�ŧi�@��256*256���x�}�Ŷ�
	FILE *filein;//�Q��C++��ܮw�ŧi�@��filein�H�s��}���ɮ׫᪺��}
	int col = 256;//�]�w�n��V�q�n���y�X��pixel
	int row = 256;//�]�w�n�C�V�q�n���y�X��pixel
	int i, j;

	filein = fopen("lena256.raw", "rb");//fopen()�|�Ǧ^�@��FILE��Ҫ���}�Ȩ�filein�A"rb"��uŪ���@�ӤG�i����
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			figure.data[i + j*row] = fgetc(filein);//fgetc()�ǤJFILE��Ҫ���}�ȡA�C����@���N�|�q�ɮפ�Ū���@�Ӧr���A����Ū���ɧ�(End of File, EOF)����
		}
	}

	imshow("lena256.raw", figure);//��ܼv��
	waitKey(0);
	fclose(filein);//�� fclose() ��ƨӱN�}�Ҫ��ɮ������A�o�˸�Ƥ~�|�u���g�J
}
