#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>

#define FILE_CHUNK_SIZE 4096

void display_error_message(const char *message) {
    printf("Error: %s\n", message);
}

void encrypt_file(const char *input_filename, const char *output_filename, const char *password) {
    if (sodium_init() < 0) {
        display_error_message("libsodium initialization failed");
        return;
    }

    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char nonce[crypto_secretstream_xchacha20poly1305_NONCEBYTES];

    randombytes_buf(salt, sizeof(salt));

    FILE *input_file = fopen(input_filename, "rb");
    FILE *output_file = fopen(output_filename, "wb");

    if (!input_file || !output_file) {
        display_error_message("Failed to open files");
        if (input_file) fclose(input_file);
        if (output_file) fclose(output_file);
        return;
    }

    if (crypto_pwhash(key, sizeof(key), password, strlen(password), salt, crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE, crypto_pwhash_ALG_DEFAULT) != 0) {
        display_error_message("Key derivation failed");
        fclose(input_file);
        fclose(output_file);
        return;
    }

    fwrite(salt, sizeof(salt), 1, output_file);

    crypto_secretstream_xchacha20poly1305_state state;
    crypto_secretstream_xchacha20poly1305_init_push(&state, nonce, key);

    unsigned char in[FILE_CHUNK_SIZE];
    unsigned char out[FILE_CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    size_t read_bytes;

    while ((read_bytes = fread(in, 1, sizeof(in), input_file)) > 0) {
        unsigned char tag = crypto_secretstream_xchacha20poly1305_TAG_MESSAGE;
        crypto_secretstream_xchacha20poly1305_push(&state, out, NULL, in, read_bytes, NULL, 0, tag);
        fwrite(out, 1, crypto_secretstream_xchacha20poly1305_ABYTES + read_bytes, output_file);
    }

    fclose(input_file);
    fclose(output_file);
}

int main() {
    const char *input_filename = "plaintext.txt";
    const char *encrypted_filename = "encrypted.bin";
    const char *decrypted_filename = "decrypted.txt";
    char password[64]; 

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0';

        encrypt_file(input_filename, encrypted_filename, password);
        printf("File encrypted.\n");
    } else {
        display_error_message("Failed to read password");
    }

    return 0;
}
