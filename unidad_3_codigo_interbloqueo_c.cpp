/*
  Simulación simple de asignación de recursos (memoria, CPU y dispositivos de entrada/salida) para 5 procesos utilizando la técnica de asignación preventiva para evitar el interbloqueo
*/

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

const int NUM_PROCESSES = 5;
const int TOTAL_MEMORY = 10;
const int TOTAL_CPU = 4;
const int TOTAL_IO_DEVICES = 2;

int available_memory = TOTAL_MEMORY;
int available_cpu = TOTAL_CPU;
int available_io_devices = TOTAL_IO_DEVICES;

vector<int> process_memory = {10, 20, 30, 40, 50};
vector<int> process_cpu = {1, 2, 3, 2, 4};
vector<int> process_io_devices = {1, 1, 2, 2, 1};

mutex mtx;

void assignResources(int process_id) {
    while (true) {
        // Intenta adquirir los recursos necesarios para el proceso
        bool has_resources = false;
        mtx.lock();
        if (available_memory >= process_memory[process_id] && 
            available_cpu >= process_cpu[process_id] && 
            available_io_devices >= process_io_devices[process_id]) {
            available_memory -= process_memory[process_id];
            available_cpu -= process_cpu[process_id];
            available_io_devices -= process_io_devices[process_id];
            has_resources = true;
        }
        mtx.unlock();

        if (has_resources) {
            // Ejecuta el proceso con los recursos asignados
            cout << "Proceso " << process_id << " ejecutando..." << endl;
            cout << "  -> Utilizando Memoria (Mb): " << process_memory[process_id] << endl;
            cout << "  -> Utilizando CPU (s)     : " << process_cpu[process_id] << endl;
            cout << "  -> Utilizando Disp E/S    : " << process_io_devices[process_id] << endl << endl;
          
            // Simula el tiempo de ejecución del proceso
            this_thread::sleep_for(chrono::milliseconds(2000));

            // Libera los recursos al terminar
            mtx.lock();
            available_memory += process_memory[process_id];
            available_cpu += process_cpu[process_id];
            available_io_devices += process_io_devices[process_id];
            mtx.unlock();
            break;
        } else {
            // Espera a que haya suficientes recursos disponibles
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < NUM_PROCESSES; i++) {
        threads.push_back(thread(assignResources, i));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
