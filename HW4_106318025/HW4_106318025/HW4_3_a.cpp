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

	/*************************************讀檔*************************************/
	filein = fopen("lena512.raw","rb");
	fread(image_char, sizeof(image_char),1, filein);//將影像資訊讀入char
	image_in = Mat(512, 512, CV_8UC1, image_char);//將char轉成Mat
	/******************************************************************************/

	/*******************************判斷讀檔是否有誤********************************/
	if (!image_in.data)
	{ 
		cout << "讀入圖片錯誤！" << endl; 
		system("pause"); 
		return -1; 
	}
	/******************************************************************************/

	/********************************加入高斯雜訊**********************************/
	Mat noise = Mat(image_in.size(), image_in.type());//產生一個與原圖格式相同的變數
	randn(noise, 0, 50);//生成高斯雜訊
	add(image_in,noise,image_out);//將原圖與高斯雜訊相加
	/******************************************************************************/

	/*************************************寫檔*************************************/
	fileout = fopen("HW4_3_a.raw","wb");
	fwrite(image_out.data, image_out.rows*image_out.cols, 1, fileout);
	/******************************************************************************/

	/***********************************顯示影像***********************************/
	imshow("original", image_in);
	imshow("GaussianNoise", image_out);
	waitKey();
	/******************************************************************************/
}
