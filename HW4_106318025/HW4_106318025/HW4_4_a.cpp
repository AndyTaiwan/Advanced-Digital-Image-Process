#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void expand(Mat After, Mat Before);
Mat Blurring_3x3(Mat input, int times);
Mat Blurring_7x7(Mat input, int times);

int main()
{
	unsigned char image_char[512 * 512];

	FILE *filein;
	FILE *fileout;
	Mat image_in;
	Mat image_out_3x3_1time(512, 512, CV_8UC1, Scalar(0));//Blurring mask 3x3 (1 time)
	Mat image_out_3x3_5times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 3x3 (5 times)
	Mat image_out_3x3_10times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 3x3 (10 times)
	Mat image_out_3x3_50times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 3x3 (50 times)
	Mat image_out_3x3_100times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 3x3 (100 times)
	Mat image_out_7x7_1time(512, 512, CV_8UC1, Scalar(0));//Blurring mask 7x7 (1 time)
	Mat image_out_7x7_5times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 7x7 (5 times)
	Mat image_out_7x7_10times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 7x7 (10 times)
	Mat image_out_7x7_50times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 7x7 (50 times)
	Mat image_out_7x7_100times(512, 512, CV_8UC1, Scalar(0));//Blurring mask 7x7 (100 times)

	/*************************************讀檔*************************************/
	filein = fopen("lena512.raw", "rb");
	fread(image_char, sizeof(image_char), 1, filein);//將影像資訊讀入char
	fclose(filein);
	image_in = Mat(512, 512, CV_8UC1, image_char);//將char轉成Mat

	/**********************************影像模糊化*********************************/
	/*-------------------1time--------------------*/
	image_out_3x3_1time = Blurring_3x3(image_in, 1);
	image_out_7x7_1time = Blurring_7x7(image_in, 1);
	/*-------------------5times-------------------*/
	image_out_3x3_5times = Blurring_3x3(image_in, 5);
	image_out_7x7_5times = Blurring_7x7(image_in, 5);
	/*-------------------10times-------------------*/
	image_out_3x3_10times = Blurring_3x3(image_in, 10);
	image_out_7x7_10times = Blurring_7x7(image_in, 10);
	/*-------------------50times-------------------*/
	image_out_3x3_50times = Blurring_3x3(image_in, 50);
	image_out_7x7_50times = Blurring_7x7(image_in, 50);
	/*-------------------100times-------------------*/
	image_out_3x3_100times = Blurring_3x3(image_in, 100);
	image_out_7x7_100times = Blurring_7x7(image_in, 100);
	/*************************************寫檔************************************/
	fileout = fopen("HW4_4_a_3x3_1time.raw", "wb");
	fwrite(image_out_3x3_1time.data, image_out_3x3_1time.rows*image_out_3x3_1time.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_3x3_5times.raw", "wb");
	fwrite(image_out_3x3_5times.data, image_out_3x3_5times.rows*image_out_3x3_5times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_3x3_10times.raw", "wb");
	fwrite(image_out_3x3_10times.data, image_out_3x3_10times.rows*image_out_3x3_10times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_3x3_50times.raw", "wb");
	fwrite(image_out_3x3_50times.data, image_out_3x3_50times.rows*image_out_3x3_50times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_3x3_100times.raw", "wb");
	fwrite(image_out_3x3_100times.data, image_out_3x3_100times.rows*image_out_3x3_100times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_7vx7_1time.raw", "wb");
	fwrite(image_out_7x7_1time.data, image_out_7x7_1time.rows*image_out_7x7_1time.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_7x7_5times.raw", "wb");
	fwrite(image_out_7x7_5times.data, image_out_7x7_5times.rows*image_out_7x7_5times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_7x7_10times.raw", "wb");
	fwrite(image_out_7x7_10times.data, image_out_7x7_10times.rows*image_out_7x7_10times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_7x7_50times.raw", "wb");
	fwrite(image_out_7x7_50times.data, image_out_7x7_50times.rows*image_out_7x7_50times.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_4_a_7x7_100times.raw", "wb");
	fwrite(image_out_7x7_100times.data, image_out_7x7_100times.rows*image_out_7x7_100times.cols, 1, fileout);
	fclose(fileout);

	/***********************************顯示影像***********************************/
	imshow("original", image_in);
	imshow("Image Blurring_3x3_1time", image_out_3x3_1time);
	imshow("Image Blurring_3x3_5times", image_out_3x3_5times);
	imshow("Image Blurring_3x3_10times", image_out_3x3_10times);
	imshow("Image Blurring_3x3_50times", image_out_3x3_50times);
	imshow("Image Blurring_3x3_100times", image_out_3x3_100times);
	imshow("Image Blurring_7x7_1time", image_out_7x7_1time);
	imshow("Image Blurring_7x7_5times", image_out_7x7_5times);
	imshow("Image Blurring_7x7_10times", image_out_7x7_10times);
	imshow("Image Blurring_7x7_50times", image_out_7x7_50times);
	imshow("Image Blurring_7x7_100times", image_out_7x7_100times);
	waitKey();
	/******************************************************************************/
}

void expand(Mat After, Mat Before)
{
	for (int j = 0; j < Before.rows; j++)
	{
		for (int i = 0; i < Before.cols; i++)
		{
			After.data[(Before.rows + 2) + (i + 1) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//將原圖置中於擴展圖空間

			if (i == 0)
			{
				After.data[(Before.rows + 2) + i + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//填補左排空像素
				if (j == 0)
				{
					After.data[0] = Before.data[i + j*Before.rows];//填補左上空像素
				}
			}
			if (i == Before.cols - 1)
			{
				After.data[(Before.rows + 2) + (i + 2) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//填補右排空像素
				if (j == Before.rows - 1)
				{
					After.data[Before.cols + 1 + (Before.rows + 2) * (Before.cols + 1)] = Before.data[i + j*Before.rows];//填補右下空像素
				}
			}
			if (j == 0)
			{
				After.data[(i + 1) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//填補上排空像素
				if (i == Before.cols - 1)
				{
					After.data[Before.cols + 1 + (Before.rows + 2) * 0] = Before.data[i + j*Before.rows];//填補右上空像素
				}
			}
			if (j == Before.rows - 1)
			{
				After.data[(Before.rows + 3) + (i + 3) + j*(Before.rows + 3)] = Before.data[i + j*Before.rows];//填補下排空像素
				if (i == 0)
				{
					After.data[0 + (Before.rows + 2) * Before.cols + 1] = Before.data[i + j*Before.rows];//填補左下空像素
				}
			}
		}
	}
}
Mat Blurring_3x3(Mat input,int times)
{
	Mat output(input.size(), input.type());
	/**********************************Blurring Mask 3x3*********************************/
	double mask_3x3[3][3];
	mask_3x3[0][0] = (double)1 / 9; mask_3x3[0][1] = (double)1 / 9; mask_3x3[0][2] = (double)1 / 9;
	mask_3x3[1][0] = (double)1 / 9; mask_3x3[1][1] = (double)1 / 9; mask_3x3[1][2] = (double)1 / 9;
	mask_3x3[2][0] = (double)1 / 9; mask_3x3[2][1] = (double)1 / 9; mask_3x3[2][2] = (double)1 / 9;

	do
	{
		/**********************************將影像擴展*********************************/
		Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
		expand(expand1, input);
		/*******************************Mask逐行逐列掃描******************************/
		for (int i = 1; i < output.rows + 1; i++)
		{
			for (int j = 1; j < output.cols + 1; j++)
			{
				output.data[(j - 1) + output.cols*(i - 1)]
					= (double)expand1.data[(j - 1) + expand1.cols*(i - 1)] * mask_3x3[0][0]
					+ (double)expand1.data[(j)+expand1.cols*(i - 1)] * mask_3x3[0][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i - 1)] * mask_3x3[0][2]
					+ (double)expand1.data[(j - 1) + expand1.cols*(i)] * mask_3x3[1][0]
					+ (double)expand1.data[(j)+expand1.cols*(i)] * mask_3x3[1][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i)] * mask_3x3[1][2]
					+ (double)expand1.data[(j - 1) + expand1.cols*(i + 1)] * mask_3x3[2][0]
					+ (double)expand1.data[(j)+expand1.cols*(i + 1)] * mask_3x3[2][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i + 1)] * mask_3x3[2][2];
			}
		}
		times --;
		if (times > 0)//判斷若掃描次數大於0時則將輸出Mat等於輸入Mat
			input = output;
	} while (times > 0);//判斷若掃描次數大於0時則重跑while()
	return output;
}
Mat Blurring_7x7(Mat input,int times)
{
	Mat output(input.size(), input.type());
	/**********************************Blurring Mask 7x7*********************************/
	double mask_7x7[7][7];
	mask_7x7[0][0] = (double)1 / 49; mask_7x7[0][1] = (double)1 / 49; mask_7x7[0][2] = (double)1 / 49; mask_7x7[0][3] = (double)1 / 49; mask_7x7[0][4] = (double)1 / 49; mask_7x7[0][5] = (double)1 / 49; mask_7x7[0][6] = (double)1 / 49;
	mask_7x7[1][0] = (double)1 / 49; mask_7x7[1][1] = (double)1 / 49; mask_7x7[1][2] = (double)1 / 49; mask_7x7[1][3] = (double)1 / 49; mask_7x7[1][4] = (double)1 / 49; mask_7x7[1][5] = (double)1 / 49; mask_7x7[1][6] = (double)1 / 49;
	mask_7x7[2][0] = (double)1 / 49; mask_7x7[2][1] = (double)1 / 49; mask_7x7[2][2] = (double)1 / 49; mask_7x7[2][3] = (double)1 / 49; mask_7x7[2][4] = (double)1 / 49; mask_7x7[2][5] = (double)1 / 49; mask_7x7[2][6] = (double)1 / 49;
	mask_7x7[3][0] = (double)1 / 49; mask_7x7[3][1] = (double)1 / 49; mask_7x7[3][2] = (double)1 / 49; mask_7x7[3][3] = (double)1 / 49; mask_7x7[3][4] = (double)1 / 49; mask_7x7[3][5] = (double)1 / 49; mask_7x7[3][6] = (double)1 / 49;
	mask_7x7[4][0] = (double)1 / 49; mask_7x7[4][1] = (double)1 / 49; mask_7x7[4][2] = (double)1 / 49; mask_7x7[4][3] = (double)1 / 49; mask_7x7[4][4] = (double)1 / 49; mask_7x7[4][5] = (double)1 / 49; mask_7x7[4][6] = (double)1 / 49;
	mask_7x7[5][0] = (double)1 / 49; mask_7x7[5][1] = (double)1 / 49; mask_7x7[5][2] = (double)1 / 49; mask_7x7[5][3] = (double)1 / 49; mask_7x7[5][4] = (double)1 / 49; mask_7x7[5][5] = (double)1 / 49; mask_7x7[5][6] = (double)1 / 49;
	mask_7x7[6][0] = (double)1 / 49; mask_7x7[6][1] = (double)1 / 49; mask_7x7[6][2] = (double)1 / 49; mask_7x7[6][3] = (double)1 / 49; mask_7x7[6][4] = (double)1 / 49; mask_7x7[6][5] = (double)1 / 49; mask_7x7[6][6] = (double)1 / 49;
	do
	{
		/**********************************將影像擴展*********************************/
		Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
		Mat expand2(expand1.rows + 2, expand1.cols + 2, CV_8UC1, Scalar(0));
		Mat expand3(expand2.rows + 2, expand2.cols + 2, CV_8UC1, Scalar(0));
		expand(expand1, input);
		expand(expand2, expand1);
		expand(expand3, expand2);

		for (int i = 3; i < output.rows + 3; i++)
		{
			for (int j = 3; j < output.cols + 3; j++)
			{
				output.data[(j - 3) + output.cols*(i - 3)]
					= (double)expand3.data[(j - 3) + expand3.cols*(i - 3)] * mask_7x7[0][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i - 3)] * mask_7x7[0][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i - 3)] * mask_7x7[0][2]
					+ (double)expand3.data[(j)+expand3.cols*(i - 3)] * mask_7x7[0][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i - 3)] * mask_7x7[0][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i - 3)] * mask_7x7[0][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i - 3)] * mask_7x7[0][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i - 2)] * mask_7x7[1][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i - 2)] * mask_7x7[1][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i - 2)] * mask_7x7[1][2]
					+ (double)expand3.data[(j)+expand3.cols*(i - 2)] * mask_7x7[1][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i - 2)] * mask_7x7[1][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i - 2)] * mask_7x7[1][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i - 2)] * mask_7x7[1][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i - 1)] * mask_7x7[2][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i - 1)] * mask_7x7[2][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i - 1)] * mask_7x7[2][2]
					+ (double)expand3.data[(j)+expand3.cols*(i - 1)] * mask_7x7[2][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i - 1)] * mask_7x7[2][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i - 1)] * mask_7x7[2][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i - 1)] * mask_7x7[2][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i)] * mask_7x7[3][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i)] * mask_7x7[3][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i)] * mask_7x7[3][2]
					+ (double)expand3.data[(j)+expand3.cols*(i)] * mask_7x7[3][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i)] * mask_7x7[3][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i)] * mask_7x7[3][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i)] * mask_7x7[3][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i + 1)] * mask_7x7[4][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i + 1)] * mask_7x7[4][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i + 1)] * mask_7x7[4][2]
					+ (double)expand3.data[(j)+expand3.cols*(i + 1)] * mask_7x7[4][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i + 1)] * mask_7x7[4][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i + 1)] * mask_7x7[4][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i + 1)] * mask_7x7[4][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i + 2)] * mask_7x7[5][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i + 2)] * mask_7x7[5][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i + 2)] * mask_7x7[5][2]
					+ (double)expand3.data[(j)+expand3.cols*(i + 2)] * mask_7x7[5][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i + 2)] * mask_7x7[5][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i + 2)] * mask_7x7[5][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i + 2)] * mask_7x7[5][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i + 3)] * mask_7x7[6][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i + 3)] * mask_7x7[6][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i + 3)] * mask_7x7[6][2]
					+ (double)expand3.data[(j)+expand3.cols*(i + 3)] * mask_7x7[6][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i + 3)] * mask_7x7[6][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i + 3)] * mask_7x7[6][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i + 3)] * mask_7x7[6][6];
			}
		}
		times --;
		if (times > 0)//判斷若掃描次數大於0時則將輸出Mat等於輸入Mat
			input = output;
	} while (times > 0);
	return output;
}