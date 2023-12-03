#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void convertirAByN(Mat& imagenEntrada, Mat& imagenSalida, int inicioFila, int finFila) {
    for (int r = inicioFila; r < finFila; r++) {
        for (int c = 0; c < imagenEntrada.cols; c++) {
            Point3_<uchar>* p = imagenEntrada.ptr<Point3_<uchar>>(r, c);

            uchar valorGris = static_cast<uchar>(0.299 * p->x + 0.587 * p->y + 0.114 * p->z);

            imagenSalida.at<uchar>(r, c) = valorGris;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <imagen_entrada> <imagen_salida>" << endl;
        return 1;
    }

    Mat imagenEntrada = imread(argv[1], IMREAD_COLOR);

    if (imagenEntrada.empty()) {
        cerr << "No se ha podido leer la imagen" << endl;
        return 1;
    }

    // Imagen de salida en escala de grises
    Mat imagenSalida(imagenEntrada.rows, imagenEntrada.cols, CV_8UC1);

    // Tiempo de ejecucion
    auto inicio = chrono::high_resolution_clock::now();

    // Conversion escala de grises con OpenMP
    #pragma omp parallel for
    for (int r = 0; r < imagenEntrada.rows; r++) {
        convertirAByN(imagenEntrada, imagenSalida, r, r + 1);
    }

    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

    cout << "La conversion OpenMP fue completada en " << duracion.count() << " milisegundos." << endl;

    // Guardar imagen en escala de grises
    imwrite(argv[2], imagenSalida);

    return 0;
}

