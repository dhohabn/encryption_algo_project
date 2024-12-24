#include <stdio.h>
#include <math.h>

// Function to calculate (base^exponent) % modulus using modular exponentiation
long long power(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;  // Handle base greater than modulus
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    long long p, g, a, b, A, B, shared_secret_A, shared_secret_B;

    // Prime number p and base g (these values are typically agreed upon beforehand)
    printf("Enter prime number p: ");
    scanf("%lld", &p);
    printf("Enter base g: ");
    scanf("%lld", &g);

    // Private keys for Alice and Bob (these should be kept secret)
    printf("Enter Alice's private key (a): ");
    scanf("%lld", &a);
    printf("Enter Bob's private key (b): ");
    scanf("%lld", &b);

    // Alice computes A = (g^a) % p
    A = power(g, a, p);

    // Bob computes B = (g^b) % p
    B = power(g, b, p);

    // Alice and Bob exchange their public keys A and B

    // Alice computes the shared secret using Bob's public key
    shared_secret_A = power(B, a, p);
    // Bob computes the shared secret using Alice's public key
    shared_secret_B = power(A, b, p);

    // The shared secret should be the same for both Alice and Bob
    printf("Alice's computed shared secret: %lld\n", shared_secret_A);
    printf("Bob's computed shared secret: %lld\n", shared_secret_B);

    if (shared_secret_A == shared_secret_B) {
        printf("The Diffie-Hellman key exchange was successful. Shared secret: %lld\n", shared_secret_A);
    } else {
        printf("Error in key exchange.\n");
    }

    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Function to check if a number is prime
int is_prime(long long num) {
    if (num <= 1) return 0;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Function to generate a random prime number
long long generate_prime() {
    srand(time(NULL));
    long long num;
    do {
        num = rand() % 1000 + 100; // Generate a random number between 100 and 1100
    } while (!is_prime(num));
    return num;
}

// Function to calculate (base^exponent) % modulus using modular exponentiation
long long power(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;  // Handle base greater than modulus
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    long long p, g, a, b, A, B, shared_secret_A, shared_secret_B;

    // Generate a random prime number p and base g
    p = generate_prime();
    g = 2; // A common base used in Diffie-Hellman key exchange
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Function to check if a number is prime
int is_prime(long long num) {
    if (num <= 1) return 0;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Function to generate a random prime number
long long generate_prime() {
    srand(time(NULL));
    long long num;
    do {
        num = rand() % 1000 + 100; // Generate a random number between 100 and 1100
    } while (!is_prime(num));
    return num;
}

// Function to calculate (base^exponent) % modulus using modular exponentiation
long long power(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;  // Handle base greater than modulus
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    long long p, g, a, b, A, B, shared_secret_A, shared_secret_B;

    // Generate a random prime number p and base g
    p = generate_prime();
    g = 2; // A common base used in Diffie-Hellman key exchange

    printf("Generated prime number p: %lld\n", p);
    printf("Base g: %lld\n", g);

    // Private keys for Alice and Bob (these should be kept secret)
    printf("Enter Alice's private key (a): ");
    scanf("%lld", &a);
    printf("Enter Bob's private key (b): ");
    scanf("%lld", &b);

    // Alice computes A = (g^a) % p
    A = power(g, a, p);

    // Bob computes B = (g^b) % p
    B = power(g, b, p);

    // Alice and Bob exchange their public keys A and B

    // Alice computes the shared secret using Bob's public key
    shared_secret_A = power(B, a, p);
    // Bob computes the shared secret using Alice's public key
    shared_secret_B = power(A, b, p);

    // The shared secret should be the same for both Alice and Bob
    printf("Alice's computed shared secret: %lld\n", shared_secret_A);
    printf("Bob's computed shared secret: %lld\n", shared_secret_B);

    if (shared_secret_A == shared_secret_B) {
        printf("The Diffie-Hellman key exchange was successful. Shared secret: %lld\n", shared_secret_A);
    } else {
        printf("Error in key exchange.\n");
    }

    return 0;
}rintf("Base g: %lld\n", g);

    // Private keys for Alice and Bob (these should be kept secret)
    printf("Enter Alice's private key (a): ");
    scanf("%lld", &a);
    printf("Enter Bob's private key (b): ");
    scanf("%lld", &b);

    // Alice computes A = (g^a) % p
    A = power(g, a, p);

    // Bob computes B = (g^b) % p
    B = power(g, b, p);

    // Alice and Bob exchange their public keys A and B

    // Alice computes the shared secret using Bob's public key
    shared_secret_A = power(B, a, p);
    // Bob computes the shared secret using Alice's public key
    shared_secret_B = power(A, b, p);

    // The shared secret should be the same for both Alice and Bob
    printf("Alice's computed shared secret: %lld\n", shared_secret_A);
    printf("Bob's computed shared secret: %lld\n", shared_secret_B);

    if (shared_secret_A == shared_secret_B) {
        printf("The Diffie-Hellman key exchange was successful. Shared secret: %lld\n", shared_secret_A);
    } else {
        printf("Error in key exchange.\n");
    }

    return 0;
}
    