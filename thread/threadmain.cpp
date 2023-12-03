#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

using namespace cv;
using namespace std;

// Definir una función para convertir una parte de la imagen a escala de grises
void convertToGrayscale(Mat& image, int startRow, int endRow) {
    for (int r = startRow; r < endRow; r++) {
        for (int c = 0; c < image.cols; c++) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            uchar gray = static_cast<uchar>((p->x + p->y + p->z) / 3);
            p->x = p->y = p->z = gray;
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <imagen_a_color> <imagen_grises> <num_hebras>" << endl;
        return -1;
    }

    Mat image = imread(argv[1], IMREAD_COLOR);

    if (image.empty()) {
        cout << "No es posible leer la imagen." << endl;
        return -1;
    }

    int numThreads = stoi(argv[3]);
    int rowsPerThread = image.rows / numThreads;
    vector<thread> threads;

    auto inicio = chrono::high_resolution_clock::now();
    // Crear threads
    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? image.rows : (i + 1) * rowsPerThread;
        threads.emplace_back(convertToGrayscale, ref(image), startRow, endRow);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

    cout << "La conversion con thread fue completada en " << duracion.count() << " milisegundos" << endl;

    // Guardar imagen en escala de grises
    imwrite(argv[2], image);

    return 0;
}

