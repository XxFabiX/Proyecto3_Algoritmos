#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// FUNCIONES PARA GENERACION ARREGLOS
vector<int> generarAleatorio(int n) {
    vector<int> arreglo(n);
    iota(arreglo.begin(), arreglo.end(), 0);
    random_shuffle(arreglo.begin(), arreglo.end());
    return arreglo;
}

vector<int> generarAleatorioConDuplicados(int n) {
    vector<int> arreglo(n);
    generate(arreglo.begin(), arreglo.end(), [&n]() { return rand() % n; });
    return arreglo;
}

vector<int> generarOrdenado(int n) {
    vector<int> arreglo(n);
    iota(arreglo.begin(), arreglo.end(), 0);
    return arreglo;
}

vector<int> generarInversamenteOrdenado(int n) {
    vector<int> arreglo(n);
    iota(arreglo.begin(), arreglo.end(), 0);
    reverse(arreglo.begin(), arreglo.end());
    return arreglo;
}



// FUNCIONES PARA ORDENAMINETO
void selectionSort(vector<int> &arreglo) {
    int n = arreglo.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arreglo[j] < arreglo[minIndex]) {
                minIndex = j;
            }
        }
        swap(arreglo[i], arreglo[minIndex]);
    }
}

void bubbleSort(vector<int> &arreglo) {
    int n = arreglo.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arreglo[j] > arreglo[j + 1]) {
                swap(arreglo[j], arreglo[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int> &arreglo) {
    int n = arreglo.size();
    for (int i = 1; i < n; ++i) {
        int key = arreglo[i];
        int j = i - 1;
        while (j >= 0 && arreglo[j] > key) {
            arreglo[j + 1] = arreglo[j];
            --j;
        }
        arreglo[j + 1] = key;
    }
}

void shellSort(vector<int> &arreglo) {
    int n = arreglo.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arreglo[i];
            int j;
            for (j = i; j >= gap && arreglo[j - gap] > temp; j -= gap) {
                arreglo[j] = arreglo[j - gap];
            }
            arreglo[j] = temp;
        }
    }
}

void merge(vector<int> &arreglo, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arreglo[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arreglo[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arreglo[k] = L[i];
            ++i;
        } else {
            arreglo[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arreglo[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arreglo[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int> &arreglo, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arreglo, l, m);
        mergeSort(arreglo, m + 1, r);

        merge(arreglo, l, m, r);
    }
}

int partition(vector<int>& arreglo, int low, int high) {
    int pivot = arreglo[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arreglo[j] < pivot) {
            ++i;
            swap(arreglo[i], arreglo[j]);
        }
    }
    swap(arreglo[i + 1], arreglo[high]);
    return i + 1;
}

// Funcion Quick Sort RECURSIVA
void quickSortRecursive(vector<int>& arreglo, int low, int high) {
    if (low < high) {
        int pivot = partition(arreglo, low, high);

        quickSortRecursive(arreglo, low, pivot - 1);
        quickSortRecursive(arreglo, pivot + 1, high);
    }
}

void quickSort(vector<int>& arreglo, int low, int high) {
    quickSortRecursive(arreglo, low, high);
}

void heapify(vector<int> &arreglo, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arreglo[left] > arreglo[largest]) {
        largest = left;
    }

    if (right < n && arreglo[right] > arreglo[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arreglo[i], arreglo[largest]);

        heapify(arreglo, n, largest);
    }
}

void heapSort(vector<int> &arreglo) {
    int n = arreglo.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arreglo, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(arreglo[0], arreglo[i]);
        heapify(arreglo, i, 0);
    }
}

void imprimirTiempo(const string& nombreAlgoritmo, vector<int>& arreglo) {
    auto inicio = high_resolution_clock::now();

    if (nombreAlgoritmo == "Selection Sort") {
        selectionSort(arreglo);
    } else if (nombreAlgoritmo == "Bubble Sort") {
        bubbleSort(arreglo);
    } else if (nombreAlgoritmo == "Insertion Sort") {
        insertionSort(arreglo);
    } else if (nombreAlgoritmo == "Shell Sort") {
        shellSort(arreglo);
    } else if (nombreAlgoritmo == "Merge Sort") {
        mergeSort(arreglo, 0, arreglo.size() - 1);
    } else if (nombreAlgoritmo == "Quick Sort") {
        quickSort(arreglo, 0, arreglo.size() - 1);
    } else if (nombreAlgoritmo == "Heap Sort") {
        heapSort(arreglo);
    }

    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<nanoseconds>(fin - inicio);

    // Convertir ns a decimales
    double duracionSegundos = duracion.count() / 1e9;

    cout << nombreAlgoritmo << ": " << fixed << setprecision(15) << duracionSegundos << " s\n";
}

int main() {
    srand(time(0));

    int opcion;
    do {
        // Menu
        cout << "Menu Principal\n";
        cout << "1. Colas de espera\n";
        cout << "2. Trazabilidad de objetos\n";
        cout << "3. Eventos de cada escenario\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int n = rand() % 11001 + 100000; // Aleatorio entre 100,000 y 110,000
                cout << "Largo del arreglo: " << n << "\n";

                // Modo Ordenado
                vector<int> ordenado = generarOrdenado(n);
                vector<int> ordenado_copy = ordenado;
                cout << "Generando arreglo ordenado....\n";
                cout << "Carrera Cola de espera, Modo Ordenado\n";
                imprimirTiempo("Selection Sort", ordenado_copy);
                imprimirTiempo("Bubble Sort", ordenado_copy);
                imprimirTiempo("Insertion Sort", ordenado_copy);
                imprimirTiempo("Shell Sort", ordenado_copy);
                imprimirTiempo("Merge Sort", ordenado_copy);
                imprimirTiempo("Quick Sort", ordenado_copy);
                imprimirTiempo("Heap Sort", ordenado_copy);

                // Modo Inversamente Ordenado
                vector<int> inversamenteOrdenado = generarInversamenteOrdenado(n);
                vector<int> inversamenteOrdenado_copy = inversamenteOrdenado;
                cout << "Generando arreglo Inversamente Ordenado....\n";
                cout << "\nCarrera Cola de espera, Modo Inversamente Ordenado\n";
                imprimirTiempo("Selection Sort", inversamenteOrdenado_copy);
                imprimirTiempo("Bubble Sort", inversamenteOrdenado_copy);
                imprimirTiempo("Insertion Sort", inversamenteOrdenado_copy);
                imprimirTiempo("Shell Sort", inversamenteOrdenado_copy);
                imprimirTiempo("Merge Sort", inversamenteOrdenado_copy);
                imprimirTiempo("Quick Sort", inversamenteOrdenado_copy);
                imprimirTiempo("Heap Sort", inversamenteOrdenado_copy);

                // Modo Aleatorio
                vector<int> aleatorio = generarAleatorio(n);
                vector<int> aleatorio_copy = aleatorio;
                cout << "Generando arreglo aleatorio....\n";
                cout << "\nCarrera Cola de espera, Modo Aleatorio\n";
                imprimirTiempo("Selection Sort", aleatorio_copy);
                imprimirTiempo("Bubble Sort", aleatorio_copy);
                imprimirTiempo("Insertion Sort", aleatorio_copy);
                imprimirTiempo("Shell Sort", aleatorio_copy);
                imprimirTiempo("Merge Sort", aleatorio_copy);
                imprimirTiempo("Quick Sort", aleatorio_copy);
                imprimirTiempo("Heap Sort", aleatorio_copy);

                // Modo Aleatorio con Duplicados
                vector<int> aleatorioConDuplicados = generarAleatorioConDuplicados(n);
                vector<int> aleatorioConDuplicados_copy = aleatorioConDuplicados;
                cout << "Generando arreglo aleatorio con duplicados....\n";
                cout << "\nCarrera Cola de espera, Modo Aleatorio con duplicados\n";
                imprimirTiempo("Selection Sort", aleatorioConDuplicados_copy);
                imprimirTiempo("Bubble Sort", aleatorioConDuplicados_copy);
                imprimirTiempo("Insertion Sort", aleatorioConDuplicados_copy);
                imprimirTiempo("Shell Sort", aleatorioConDuplicados_copy);
                imprimirTiempo("Merge Sort", aleatorioConDuplicados_copy);
                imprimirTiempo("Quick Sort", aleatorioConDuplicados_copy);
                imprimirTiempo("Heap Sort", aleatorioConDuplicados_copy);

                break;
            }
            
        }
        
    } while (opcion != 4);

    return 0;
}




