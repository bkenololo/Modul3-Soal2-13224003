/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
*   Modul               : Graph and Tree
*   Hari dan Tanggal    : Rabu, 18 November 2026
*   Nama (NIM)          : Benedictus Kenneth Setiadi (13224003)
*   Nama File           : soal2.c
*   Deskripsi           : Program menentukan langkah minimum untuk mengisi gelas sebanyak X liter dengan menggunakan hanya 2 gelas ukuran A dan B
*/

/*
Referensi:
https://www.geeksforgeeks.org/dsa/two-water-jug-puzzle/
*/

#include <stdio.h>
#include <stdbool.h>

int minimum_steps(int size_a, int size_b, int target) {
  
    if (target > size_a && target > size_b) return -1; 
	
    int q[10000][3], front = 0, rear = 0; // queue BFS

    bool visited[size_a + 1][size_b + 1];
    for (int i = 0; i <= size_a; i++) {
        for (int j = 0; j <= size_b; j++) {
            visited[i][j] = false;
        }
    }

    // state (0, 0, 0) 
    q[rear][0] = 0;
    q[rear][1] = 0;
    q[rear][2] = 0;
    rear++;
    visited[0][0] = true;

    while (front != rear) {
      
        // front
        int bucket_a = q[front][0];
        int bucket_b = q[front][1];
        int steps = q[front][2];
        front++;

        if (bucket_a == target || bucket_b == target) return steps;

        // fill 1
        if (!visited[size_a][bucket_b]) {
            visited[size_a][bucket_b] = true;
            q[rear][0] = size_a;
            q[rear][1] = bucket_b;
            q[rear][2] = steps + 1;
            rear++;
        }

        // fill 2
        if (!visited[bucket_a][size_b]) {
            visited[bucket_a][size_b] = true;
            q[rear][0] = bucket_a;
            q[rear][1] = size_b;
            q[rear][2] = steps + 1;
            rear++;
        }

        // empty 1
        if (!visited[0][bucket_b]) {
            visited[0][bucket_b] = true;
            q[rear][0] = 0;
            q[rear][1] = bucket_b;
            q[rear][2] = steps + 1;
            rear++;
        }

        // empty 2
        if (!visited[bucket_a][0]) {
            visited[bucket_a][0] = true;
            q[rear][0] = bucket_a;
            q[rear][1] = 0;
            q[rear][2] = steps + 1;
            rear++;
        }

        // pour 1to2
        int pour1to2 = bucket_a < (size_b - bucket_b) ? bucket_a : (size_b - bucket_b);
        if (!visited[bucket_a - pour1to2][bucket_b + pour1to2]) {
            visited[bucket_a - pour1to2][bucket_b + pour1to2] = true;
            q[rear][0] = bucket_a - pour1to2;
            q[rear][1] = bucket_b + pour1to2;
            q[rear][2] = steps + 1;
            rear++;
        }

        // pour 2to1
        int pour2to1 = bucket_b < (size_a - bucket_a) ? bucket_b : (size_a - bucket_a);
        if (!visited[bucket_a + pour2to1][bucket_b - pour2to1]) {
            visited[bucket_a + pour2to1][bucket_b - pour2to1] = true;
            q[rear][0] = bucket_a + pour2to1;
            q[rear][1] = bucket_b - pour2to1;
            q[rear][2] = steps + 1;
            rear++;
        }
    }

    return -1;
}

int main() {
    int size_a, size_b, target;
    scanf("%d %d %d", &size_a, &size_b, &target);
    int result = minimum_steps(size_a, size_b, target);
    

    printf("%d\n", result);
    return 0;
}
