#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp> // highguiのヘッダーをインクルード
#include <iostream>

int main(int argc, const char* argv[])
{
	// （1）DirectShowを使ってカメラキャプチャを行う。
	// また、IDがcamera_id番のカメラについてキャプチャの準備を行う
	int camera_id = 0;
	cv::VideoCapture cap(CV_CAP_DSHOW + camera_id);

	// （2）IDがcamera_id番のカメラが正しくオープンできているかをチェックする（正しくオープンできていなければエラー終了する）
	if(!cap.isOpened())
		return -1;

	// （3）カメラキャプチャのフレームレートを30.0に指定する
	cap.set(CV_CAP_PROP_FPS, 30.0);

	// 画像表示用のウィンドウを生成する
	cv::namedWindow("image", cv::WINDOW_AUTOSIZE);

	// 画像データを格納するための変数を宣言する
	cv::Mat inframe;
	// 出力画像データのための変数
	cv::Mat outframe;

	for(;;)
	{
		// （4）カメラから1フレーム分の画像データを取得して、変数inframeに格納する
		cap >> inframe;
		// 画像データ取得に失敗したらループを抜ける
		if (inframe.empty()) break;


		// <エッジ検出>
		//cvtColor(inframe, outframe, CV_BGR2GRAY);
		//GaussianBlur(outframe, outframe, cv::Size(7,7), 1.5, 1.5);
		//Canny(outframe, outframe, 0, 30, 3);	
		//cv::imshow("image", outframe);


		// <モノクロ出力>
		//cvtColor(inframe, outframe, CV_BGR2GRAY);
		//cv::imshow("image", outframe);


		// //<二極化>
		//cv::Mat src_img = inframe.clone();
		//cv::Mat tmp_img1 = src_img.clone();
		//   cv::Mat tmp_img2 = src_img.clone();
		//cv::Mat tmp_img3 = src_img.clone();
		//   cv::Mat src_img_gray = src_img.clone();
		//cv::cvtColor (src_img, src_img_gray, CV_BGR2GRAY);

		//try{
		//	// ガウシアンフィルタで平滑化を行う
		//	cv::GaussianBlur (src_img_gray, src_img_gray, cv::Size(19,19), 2, 2);

		//	// (1)二値化:threshold
		//	cv::threshold (src_img_gray, tmp_img1, 60, 255, CV_THRESH_BINARY);
		//
		//	// (2)二値化:cvAdaptiveThreshold
		//	cv::adaptiveThreshold (src_img_gray, tmp_img2, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 17, 5);

		//	// (3)二つの二値化画像の論理積
		//	cv::bitwise_and (tmp_img1, tmp_img2, tmp_img3);
		//	cv::cvtColor (tmp_img3, outframe, CV_GRAY2BGR);

		//	// (4)元画像と二値画像の論理積
		//	cv::GaussianBlur (src_img, src_img, cv::Size(5,5), 2, 2);
		//	cv::bitwise_and (outframe, src_img, outframe);
		//
		//	/*cv::cvtColor (tmp_img2, tmp_img2, CV_GRAY2BGR);
		//	cv::bitwise_and (tmp_img2, inframe, outframe);*/
		//	cv::imshow("image", outframe);

		//}catch(cv::Exception& e){
		//  const char* err_msg = e.what();
		//  std::cerr << err_msg << std::endl;
		//}

		// <画素値（R,G,B）を取得し，変更する>
		int x, y;
		cv::Mat img = inframe.clone();
		for (y = 0; y < img.rows; y++) {
			cv::Vec3b* ptr = img.ptr<cv::Vec3b>( y );
			for (x = 0; x < img.cols; x++) {
				cv::Vec3b bgr = ptr[x];

				bgr[0] = cvRound (bgr[0] * 1.0);
				bgr[1] = cvRound (bgr[1] * 0.1);
				bgr[2] = cvRound (bgr[2] * 0.1);

				ptr[x] = cv::Vec3b(bgr[0], bgr[1], bgr[2]);
			}
		}
		cv::imshow("image", img);


		if(cv::waitKey(30) >= 0) break;
	}
	return 0;
}