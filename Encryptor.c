#include <stdio.h>
#include <stdlib.h>

// Function to find the modular inverse of a number 'a' under modulo 'm'
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to encrypt a character using the Affine Cipher formula
char affine_encrypt_char(char ch, int a, int b) {
    // Assuming input characters are ASCII values between 0 and 255
    return (a * ch + b) % 256;
}

// Function to decrypt a character using the Affine Cipher formula
char affine_decrypt_char(char ch, int a_inv, int b) {
    // Assuming input characters are ASCII values between 0 and 255
    return (a_inv * (ch - b + 256)) % 256;
}

void affine_encrypt(const char *input_filename, const char *output_filename, int a, int b) {
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");

    if (input_file == NULL) {
        printf("Error: Could not open input file: %s\n", input_filename);
        exit(1);
    }

    if (output_file == NULL) {
        printf("Error: Could not open output file: %s\n", output_filename);
        fclose(input_file);
        exit(1);
    }

    int ch;
    while ((ch = fgetc(input_file)) != EOF) {
        fputc(affine_encrypt_char((unsigned char)ch, a, b), output_file);
    }

    fclose(input_file);
    fclose(output_file);
}

void affine_decrypt(const char *input_filename, const char *output_filename, int a, int b) {
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");

    if (input_file == NULL) {
        printf("Error: Could not open input file: %s\n", input_filename);
        exit(1);
    }

    if (output_file == NULL) {
        printf("Error: Could not open output file: %s\n", output_filename);
        fclose(input_file);
        exit(1);
    }

    int a_inv = mod_inverse(a, 256);
    if (a_inv == -1) {
        printf("Error: 'a' has no modular inverse under 256.\n");
        fclose(input_file);
        fclose(output_file);
        exit(1);
    }

    int ch;
    while ((ch = fgetc(input_file)) != EOF) {
        fputc(affine_decrypt_char((unsigned char)ch, a_inv, b), output_file);
    }

    fclose(input_file);
    fclose(output_file);
}

void display_menu() {
    printf("Affine Cipher Menu\n");
    printf("1. Encrypt a file\n");
    printf("2. Decrypt a file\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char input_filename[256], output_filename[256];
    int a = 5;  // Multiplier (must be coprime with 256)
    int b = 8;  // Additive key

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter the input file path: ");
                scanf("%255s", input_filename); // Use length specifier to avoid buffer overflow
                printf("Enter the output file path: ");
                scanf("%255s", output_filename); // Use length specifier to avoid buffer overflow
                affine_encrypt(input_filename, output_filename, a, b);
                printf("File encrypted successfully.\n");
                break;
            case 2:
                printf("Enter the input file path: ");
                scanf("%255s", input_filename); // Use length specifier to avoid buffer overflow
                printf("Enter the output file path: ");
                scanf("%255s", output_filename); // Use length specifier to avoid buffer overflow
                affine_decrypt(input_filename, output_filename, a, b);
                printf("File decrypted successfully.\n");
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
//C:\Users\dudlu\OneDrive\Desktop\abcdefg.txt
//C:\Users\dudlu\OneDrive\Desktop\ABCD.txt
//C:\Users\dudlu\OneDrive\Desktop\ABCD(UNENCRYPTED).txt