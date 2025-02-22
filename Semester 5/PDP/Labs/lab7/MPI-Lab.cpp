// MPI-Lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "mpi.h"
#include <vector>

using namespace std;

void printVector(vector<int> v, int id) {
    cout << "Process " << id << " has: ";
    for (auto item : v)
        cout << item << " ";

    cout << endl;
}

int sumRec(int myId, int nrProc, int chunkSize, int const* v) {
	std::vector<int> vv(chunkSize);
	MPI_Scatter(v, chunkSize, MPI_INT, vv.data(), chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	printVector(vv, myId);
	int sum = 0;
	for (int value : vv) {
		sum += value;
	}
	int t = 0;
	if (2 * myId + 1 < nrProc) {
		MPI_Recv(&t, 1, MPI_INT, 2 * myId + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sum += t;
	}
	if (2 * myId + 2 < nrProc) {
		MPI_Recv(&t, 1, MPI_INT, 2 * myId + 2, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sum += t;
	}
	if (myId != 0) {
		MPI_Send(&sum, 1, MPI_INT, (myId - 1) / 2, 1, MPI_COMM_WORLD);
	}
	return sum;
}

int product(int nrProc, std::vector<int> const& v) {
	/*vector<int> vv(v);
	int pad = nrProc - v.size() % nrProc;
	vv.resize(v.size() + pad, 0);*/
	int chunkSize = v.size() / nrProc;
	MPI_Bcast(&chunkSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int leftElementsSum = 0;

	for (int i = chunkSize * nrProc; i < v.size(); i++)
		leftElementsSum += v[i];

	return leftElementsSum + sumRec(0, nrProc, chunkSize, v.data());
}

void worker(int myId, int nrProc) {
	int chunkSize;
	MPI_Bcast(&chunkSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	sumRec(myId, nrProc, chunkSize, nullptr);
}

void printVector(int a[], int len, int id) {
    for (int i = 0; i < len; i++)
        cout << a[i] << " ";
}


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        printf("At least two processes are expected!");
        MPI_Finalize();

        return -1;
    }

    vector<int> a = { 1, 2, 3, 4, 5 };
    vector<int> b = { 1, 2, 3, 4, 5 };


	if (rank == 0)
		cout << product(size, a);

    else
        worker(rank, size);

    MPI_Finalize();
    return 0;
}

