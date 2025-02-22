#include "mpi.h"
#include "mpi_comm.h"
#include <iostream>
#include "DSM.h"

#include <thread>
#include <chrono>
#include <mutex>

int processCount, processId;
DSM dsm;
std::mutex mtx;

void dsmListener() {
	while (true) {
		std::cout << "process: " << processId << " waiting..." << endl;

		int* message = getMessage();

		std::cout << "process: " << processId << " received: ";
		std::cout << message[0] << " " << message[1] << " " << message[2] << endl << flush;

		char variableName = message[1] == 0 ? 'a' : 'b';

		if (message[0] == -1) return;

		if (message[0] == 0) { // update
			std::cout << "Process: " << processId << endl;

			std::cout << "update variable: " << variableName << " with value: " << message[2] << std::endl << flush;

			mtx.lock();
			dsm.setVariable(variableName, message[2]);
			mtx.unlock();
		}

		if (message[0] == 1) {
			std::cout << "Process: " << processId << " ";
			
			std::cout << "subscribing variable: " << variableName << " with process: " << message[2] << std::endl;

			mtx.lock();
			dsm.addSubscriber(variableName, message[2]);
			mtx.unlock();
		}
		
		delete message;
	}
}

int main() {
	MPI_Init(nullptr, nullptr);

	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &processId);

	int buffer[100];

	MPI_Buffer_attach(buffer, sizeof(buffer));

	std::thread t(dsmListener);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	
	if (processId == 0) {
		mtx.lock();
		dsm.subscribe('a', 0, processCount);
		mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(3));

		mtx.lock();
		dsm.compareAndExchange('a', 0, 5, processCount);
		mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(1));


		dsm.shutDown(processId);
	}

	if (processId == 1) {
		mtx.lock();
		dsm.subscribe('a', 1, processCount);
		mtx.unlock();

		mtx.lock();
		dsm.subscribe('b', 1, processCount);
		mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(6));

		dsm.shutDown(processId);
	}


	t.join();

	cout << "process id: " << processId << " value: " << dsm.a.value << endl;

	MPI_Finalize();
}