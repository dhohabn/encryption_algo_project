#include <stdio.h>

// Function to calculate (base^exponent) % modulus
int calculate_modulo(int base, int exponent, int modulus) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result = (result * base) % modulus; // Multiply and take remainder
    }
    return result;
}

int main() {
    int P, G;  // Public values: Prime modulus and Primitive root
    int privateKeyAlice, privateKeyBob;  // Private keys for Alice and Bob
    int publicKeyAlice, publicKeyBob;    // Public keys for Alice and Bob
    int sharedSecretAlice, sharedSecretBob; // Shared secret keys

    // Input the prime modulus (P) and primitive root (G)
    printf("Enter a prime number (P): ");
    scanf("%d", &P);
    printf("Enter a primitive root (G): ");
    scanf("%d", &G);

    // Input private keys for Alice and Bob
    printf("Enter Alice's private key: ");
    scanf("%d", &privateKeyAlice);
    printf("Enter Bob's private key: ");
    scanf("%d", &privateKeyBob);

    // Calculate public keys
    publicKeyAlice = calculate_modulo(G, privateKeyAlice, P);
    publicKeyBob = calculate_modulo(G, privateKeyBob, P);

    // Calculate shared secret keys
    sharedSecretAlice = calculate_modulo(publicKeyBob, privateKeyAlice, P);
    sharedSecretBob = calculate_modulo(publicKeyAlice, privateKeyBob, P);

    // Display results
    printf("Alice's Public Key: %d\n", publicKeyAlice);
    printf("Bob's Public Key: %d\n", publicKeyBob);
    printf("Shared Secret Key (Alice): %d\n", sharedSecretAlice);
    printf("Shared Secret Key (Bob): %d\n", sharedSecretBob);

    if (sharedSecretAlice == sharedSecretBob) {
        printf("Key exchange successful! Shared secret key is: %d\n", sharedSecretAlice);
    } else {
        printf("Key exchange failed. Secrets do not match.\n");
    }

    return 0;
