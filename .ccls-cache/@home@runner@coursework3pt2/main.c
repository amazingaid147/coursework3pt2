#include <stdio.h>
#include <stdbool.h>

// Structure to represent prime factors and their powers
typedef struct {
    int prime;
    int power;
} Factor;

// Function to compute the prime factorization
int prime_factorization(int n, Factor *factors) {
    int num_factors = 0;
    int i = 2;
    while (i * i <= n) {
        while (n % i == 0) {
            bool found = false;
            // Check if the prime is already in the factors array
            for (int j = 0; j < num_factors; j++) {
                if (factors[j].prime == i) {
                    factors[j].power++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                factors[num_factors].prime = i;
                factors[num_factors].power = 1;
                num_factors++;
            }
            n /= i;
        }
        i++;
    }
    if (n > 1) {
        factors[num_factors].prime = n;
        factors[num_factors].power = 1;
        num_factors++;
    }
    return num_factors;
}

// Recursive function to generate the butterfly sequence
int generate_butterfly_sequence(int dft_size, int *sequence) {
    // Base case: DFT size of 2
    if (dft_size == 2) {
        sequence[0] = 0;
        sequence[1] = 1;
        return 2; // Length of the sequence
    }

    Factor factors[32]; // Assuming a maximum of 32 prime factors
    int num_factors = prime_factorization(dft_size, factors);

    // Handle prime radices (prioritize 5, then 3)
    for (int i = 0; i < num_factors; i++) {
        if (factors[i].prime == 5 || factors[i].prime == 3) {
            int smaller_dft_size = dft_size / factors[i].prime;
            int smaller_seq[smaller_dft_size];
            int smaller_seq_len = generate_butterfly_sequence(smaller_dft_size, smaller_seq);
            int offset = smaller_dft_size;
            int seq_index = 0;
            for (int j = 0; j < factors[i].prime; j++) {
                for (int k = 0; k < smaller_seq_len; k++) {
                    sequence[seq_index++] = smaller_seq[k] + j * offset;
                }
            }
            return seq_index; // Length of the generated sequence
        }
    }

    // Handle base-2 (assuming it's always present if not prime)
    int smaller_dft_size = dft_size / 2;
    int smaller_seq[smaller_dft_size];
    int smaller_seq_len = generate_butterfly_sequence(smaller_dft_size, smaller_seq);

    // Interleave the two halves
    for (int i = 0; i < smaller_seq_len; i++) {
        sequence[i] = smaller_seq[i];
        sequence[i + smaller_seq_len] = smaller_seq[i] + smaller_dft_size;
    }
    return dft_size; // Length of the generated sequence
}

int main() {
    int dft_size = 1944;
    int sequence[dft_size / 2]; // Allocate memory for the sequence
    int seq_len = generate_butterfly_sequence(dft_size, sequence);

    printf("seq_%d = {", dft_size);
    for (int i = 0; i < seq_len; i++) {
        printf("%d, ", sequence[i]);
    }
    printf("}\n");

    return 0;
}