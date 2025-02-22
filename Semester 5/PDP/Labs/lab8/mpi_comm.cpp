#include "mpi_comm.h"

void sendSubscribe(char varName, int who, int to) {
    int which = 0;
    if (varName == 'a')
        which = 0;
    else if (varName == 'b')
        which = 1;

    int arr[3] = { 1, which, who }; // 1 for subscribe
    std::stringstream ss;
    ss << "sending " << arr[0] << " " << arr[1] << " " << arr[2] << " to " << to;
    std::cout << ss.str() << std::endl;

    MPI_Bsend(arr, 3, MPI_INT, to, 0, MPI_COMM_WORLD);
}

void sendUpdate(char varName, int newValue, int to) {
    int which = varName == 'a' ? 0 : 1;

    int arr[3] = { 0, which, newValue };

    MPI_Bsend(arr, 3, MPI_INT, to, 0, MPI_COMM_WORLD);
    
    std::stringstream ss;
    ss << "sent " << arr[0] << " " << arr[1] << " " << arr[2] << " to " << to;
    //std::cout << ss.str() << std::endl;
}

int* getMessage() {
    int* message = new int[3];

    MPI_Recv(message, 3, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    return message;
}