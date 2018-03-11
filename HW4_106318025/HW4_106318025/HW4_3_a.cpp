#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	FILE *filein;
	FILE *fileout;
	Mat image_in;
	Mat image_out;
	unsigned char image_char[512 * 512];

	/*************************************Ū��*************************************/
	filein = fopen("lena512.raw","rb");
	fread(image_char, sizeof(image_char),1, filein);//�N�v����TŪ�Jchar
	image_in = Mat(512, 512, CV_8UC1, image_char);//�Nchar�নMat
	/******************************************************************************/

	/*******************************�P�_Ū�ɬO�_���~********************************/
	if (!image_in.data)
	{ 
		cout << "Ū�J�Ϥ����~�I" << endl; 
		system("pause"); 
		return -1; 
	}
	/******************************************************************************/

	/********************************�[�J�������T**********************************/
	Mat noise = Mat(image_in.size(), image_in.type());//���ͤ@�ӻP��Ϯ榡�ۦP���ܼ�
	randn(noise, 0, 50);//�ͦ��������T
	add(image_in,noise,image_out);//�N��ϻP�������T�ۥ[
	/******************************************************************************/

	/*************************************�g��*************************************/
	fileout = fopen("HW4_3_a.raw","wb");
	fwrite(image_out.data, image_out.rows*image_out.cols, 1, fileout);
	/******************************************************************************/

	/***********************************��ܼv��***********************************/
	imshow("original", image_in);
	imshow("GaussianNoise", image_out);
	waitKey();
	/******************************************************************************/
}
