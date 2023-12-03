#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;

void convertToGrayscale(Mat& image) {
    #pragma omp parallel for
    for (int r = 0; r < image.rows; ++r) {
        for (int c = 0; c < image.cols; ++c) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            // Convierte a escala de grises utilizando el método de luminosidad
            uchar grayValue = 0.299 * p->x + 0.587 * p->y + 0.114 * p->z;
            p->x = p->y = p->z = grayValue;
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <imagen_color> <imagen_gris> <num_hebras>" << endl;
        return -1;
    }

    Mat image = imread(argv[1], IMREAD_COLOR);
    if (image.empty()) {
        cerr << "Error al leer la imagen de entrada." << endl;
        return -1;
    }

    int numThreads = stoi(argv[3]);
    omp_set_num_threads(numThreads);

    auto start_time = chrono::high_resolution_clock::now();

    convertToGrayscale(image);

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;

    // Guardar la imagen en escala de grises
    imwrite(argv[2], image);

    cout << "Total time spent in seconds is " << elapsed_seconds.count() << endl;

    return 0;
}
