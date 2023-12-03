#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	if(argc != 3){
		cout << "Usage: " << argv[0] << " <input_image> <output_image>" << endl;
		return -1;
	}

	Mat img = imread(argv[1], IMREAD_COLOR);
	if(img.empty()){
		cout << "La imagen no puede ser leida" << endl;
		return -1;
	}

	auto start = chrono::high_resolution_clock::now();

	// grayscale conversion method
	for(int row=0; row<img.rows; row++){
		for(int col=0; col<img.cols; col++){
			Vec3b px = img.at<Vec3b>(row, col);
			int gray_val = 0.299*px[2] + 0.587*px[1] + 0.114*px[0];

			px[0] = px[1] = px[2] = gray_val;

			img.at<Vec3b>(row, col) = px;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

	cout << "La conversion secuencial fue completada en " << duration.count() << " milisegundos" << endl;

	imwrite(argv[2], img);
	return 0;
}
