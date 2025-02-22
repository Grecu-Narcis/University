#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

// Karatsuba Polynomial Multiplication Function
void karatsuba(const vector<int>& A, const vector<int>& B, vector<int>& result, int n) {
    if (n == 1) {
        result[0] = A[0] * B[0];
        return;
    }

    int m = n / 2;
    vector<int> A0(m), A1(m), B0(m), B1(m);
    vector<int> A0B0(m), A1B1(m), cross(m);

    // Split the polynomials into two parts
    for (int i = 0; i < m; i++) {
        A0[i] = A[i];
        A1[i] = A[i + m];
        B0[i] = B[i];
        B1[i] = B[i + m];
    }

    // Step 1: Recursively calculate A0 * B0 and A1 * B1
    karatsuba(A0, B0, A0B0, m);
    karatsuba(A1, B1, A1B1, m);

    // Step 2: Calculate cross product (A0 + A1) * (B0 + B1) - A0 * B0 - A1 * B1
    vector<int> A0A1_B0B1(m);
    for (int i = 0; i < m; i++) {
        A0A1_B0B1[i] = A0[i] + A1[i] + B0[i] + B1[i];
    }
    karatsuba(A0A1_B0B1, A0A1_B0B1, cross, m);

    // Step 3: Combine the results
    for (int i = 0; i < m; i++) {
        result[i] += A0B0[i];
        result[i + m] += A1B1[i];
        result[i + m] += cross[i] - A0B0[i] - A1B1[i];
    }
}

// Parallel Karatsuba Multiplication using MPI
void mpiKaratsuba(const vector<int>& A, const vector<int>& B, vector<int>& result, int n, int rank, int size) {
    int m = n / 2;

    // Each process works on one part of the polynomial multiplication
    vector<int> local_result(n, 0);

    if (rank == 0) {
        // Step 1: Split work among MPI processes
        for (int i = 0; i < m; i++) {
            result[i] = A[i] * B[i];
        }

        // Broadcast parts of the polynomial
        for (int i = 1; i < size; i++) {
            MPI_Send(A.data(), m, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(B.data(), m, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

    }
    else {
        // Each process computes its assigned part of the Karatsuba multiplication
        vector<int> A_part(m), B_part(m);

        // Receive the split data
        MPI_Recv(A_part.data(), m, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B_part.data(), m, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        karatsuba(A_part, B_part, local_result, m);

        // Gather all results in the root process
        MPI_Gather(local_result.data(), m, MPI_INT, result.data(), m, MPI_INT, 0, MPI_COMM_WORLD);
    }
}
