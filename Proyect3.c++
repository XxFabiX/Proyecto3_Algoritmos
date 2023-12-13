#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <stack>

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
    auto inicio = high_resolution_clock::now();

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

void quickSortIterative(vector<int>& arreglo, int low, int high) {
    // Creamos una pila auxiliar para la implementacion iterativa de quick PD:profe nose si esta bien asi :(
    stack<int> pila;

    // Hacemos push de los valores iniciales de low y high en la pila
    pila.push(low);
    pila.push(high);

    // Mientras la pila no este vacia
    while (!pila.empty()) {
        // Pop de high y low
        high = pila.top();
        pila.pop();
        low = pila.top();
        pila.pop();

        // Obtener el indice del pivote
        int pivotIndex = partition(arreglo, low, high);

        // Si hay elementos a la izquierda del pivote, agregarlos a la pila
        if (pivotIndex - 1 > low) {
            pila.push(low);
            pila.push(pivotIndex - 1);
        }

        // Si hay elementos a la derecha del pivote, agregarlos a la pila
        if (pivotIndex + 1 < high) {
            pila.push(pivotIndex + 1);
            pila.push(high);
        }
    }
}


void quickSort(vector<int>& arreglo, int low, int high) {
    quickSortIterative(arreglo, low, high);
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
        try {
            quickSortIterative(arreglo, 0, arreglo.size() - 1);
        } catch (const exception& e) {
            cerr << "Excepción en Quick Sort: " << e.what() << endl;
            return;
        }
    } else if (nombreAlgoritmo == "Heap Sort") {
        heapSort(arreglo);
    }

    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<nanoseconds>(fin - inicio);

    // Convertir ns a decimales
    double duracionSegundos = duracion.count() / 1e9;

    cout << nombreAlgoritmo << ": " << fixed << setprecision(15) << duracionSegundos << " s\n";
}

void ejecutarAlgoritmo(const string& nombreAlgoritmo, vector<int>& arreglo) {
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
        try {
            quickSortIterative(arreglo, 0, arreglo.size() - 1);
        } catch (const exception& e) {
            cerr << "Excepcion en Quick Sort: " << e.what() << endl;
            return;
        }
    } else if (nombreAlgoritmo == "Heap Sort") {
        heapSort(arreglo);
    }

    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<nanoseconds>(fin - inicio);

    // Convertir ns a decimales
    double duracionSegundos = duracion.count() / 1e9;

    cout << nombreAlgoritmo << ": " << fixed << setprecision(15) << duracionSegundos << " s\n";
}

void mostrarGanadorCarrera(const string& nombreAlgoritmo, double tiempo) {
    cout << "El ganador de la carrera es " << nombreAlgoritmo << "\n";
}


void ejecutarCarrera(const string& modo, vector<int>& arreglo) {
    cout << "Generando arreglo " << modo << "....\n";
    
    vector<string> algoritmos = {"Quick Sort", "Heap Sort", "Shell Sort", "Merge Sort", "Selection Sort", "Bubble Sort", "Insertion Sort"};
    vector<double> tiempos;

    for (const auto& algoritmo : algoritmos) {
        auto inicio = high_resolution_clock::now();
        ejecutarAlgoritmo(algoritmo, arreglo);
        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio);
        double duracionSegundos = duracion.count() / 1e9;
        tiempos.push_back(duracionSegundos);
    }

    // Encontrar el indice del minimo tiempo
    auto ganadorIndex = min_element(tiempos.begin(), tiempos.end()) - tiempos.begin();

    // Mostrar el ganador
    mostrarGanadorCarrera(algoritmos[ganadorIndex], tiempos[ganadorIndex]);
}

int main() {
    srand(time(0));

    int opcion;
    do {
        // Menú principal
        cout << "Menu Principal\n";
        cout << "1. Colas de espera\n";
        cout << "2. Trazabilidad de objetos\n";
        cout << "3. Eventos de cada escenario\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int subOpcion;
                // Elegir el tipo de arreglo
                cout << "\nSeleccione el tipo de arreglo:\n";
                cout << "1. Ordenado\n";
                cout << "2. Inversamente Ordenado\n";
                cout << "3. Aleatorio\n";
                cout << "4. Aleatorio con Duplicados\n";
                cout << "Opcion: ";
                cin >> subOpcion;

                int n = rand() % 11001 + 100000; // Aleatorio entre 100,000 y 110,000

                switch (subOpcion) {
                    case 1: {
                        vector<int> ordenado = generarOrdenado(n);
                        ejecutarCarrera("Ordenado", ordenado);
                        break;
                    }
                    case 2: {
                        vector<int> inversamenteOrdenado = generarInversamenteOrdenado(n);
                        ejecutarCarrera("Inversamente Ordenado", inversamenteOrdenado);
                        break;
                    }
                    case 3: {
                        vector<int> aleatorio = generarAleatorio(n);
                        ejecutarCarrera("Aleatorio", aleatorio);
                        break;
                    }
                    case 4: {
                        vector<int> aleatorioConDuplicados = generarAleatorioConDuplicados(n);
                        ejecutarCarrera("Aleatorio con Duplicados", aleatorioConDuplicados);
                        break;
                    }
                    default:
                        cout << "Opcion no valida.\n";
                        break;
                }
                break;
            }
            case 2: {
                // Generar n para Trazabilidad de objetos
                int n = (rand() % 501 + 1000) * 15; // Aleatorio entre 1,000 y 15,000 multiplicado por 15
                cout << "Numero generado (n): " << n << endl;

                // Elegir el tipo de arreglo
                int subOpcion;
                cout << "\nSeleccione el tipo de arreglo:\n";
                cout << "1. Ordenado\n";
                cout << "2. Inversamente Ordenado\n";
                cout << "3. Aleatorio\n";
                cout << "4. Aleatorio con Duplicados\n";
                cout << "Opcion: ";
                cin >> subOpcion;

                switch (subOpcion) {
                    case 1: {
                        vector<int> ordenado = generarOrdenado(n);
                        ejecutarCarrera("Ordenado", ordenado);
                        break;
                    }
                    case 2: {
                        vector<int> inversamenteOrdenado = generarInversamenteOrdenado(n);
                        ejecutarCarrera("Inversamente Ordenado", inversamenteOrdenado);
                        break;
                    }
                    case 3: {
                        vector<int> aleatorio = generarAleatorio(n);
                        ejecutarCarrera("Aleatorio", aleatorio);
                        break;
                    }
                    case 4: {
                        vector<int> aleatorioConDuplicados = generarAleatorioConDuplicados(n);
                        ejecutarCarrera("Aleatorio con Duplicados", aleatorioConDuplicados);
                        break;
                    }
                    default:
                        cout << "Opcion no valida.\n";
                        break;
                }
                break;
            }
            case 3: {
                // Generar n para Eventos en Cada Escenario
                int n = rand() % 20001 + 60000; // Aleatorio entre 60,000 y 80,000
                cout << "Numero generado (n): " << n << endl;

                // Elegir el tipo de arreglo
                int subOpcion;
                cout << "\nSeleccione el tipo de arreglo:\n";
                cout << "1. Ordenado\n";
                cout << "2. Inversamente Ordenado\n";
                cout << "3. Aleatorio\n";
                cout << "4. Aleatorio con Duplicados\n";
                cout << "Opcion: ";
                cin >> subOpcion;

                switch (subOpcion) {
                    case 1: {
                        vector<int> ordenado = generarOrdenado(n);
                        ejecutarCarrera("Ordenado", ordenado);
                        break;
                    }
                    case 2: {
                        vector<int> inversamenteOrdenado = generarInversamenteOrdenado(n);
                        ejecutarCarrera("Inversamente Ordenado", inversamenteOrdenado);
                        break;
                    }
                    case 3: {
                        vector<int> aleatorio = generarAleatorio(n);
                        ejecutarCarrera("Aleatorio", aleatorio);
                        break;
                    }
                    case 4: {
                        vector<int> aleatorioConDuplicados = generarAleatorioConDuplicados(n);
                        ejecutarCarrera("Aleatorio con Duplicados", aleatorioConDuplicados);
                        break;
                    }
                    default:
                        cout << "Opcion no valida.\n";
                        break;
                }
                break;
            }
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}
