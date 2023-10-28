

# File Encryption using libsodium in C

This is a C program that demonstrates file encryption using the libsodium library. The program encrypts a plaintext file with a user-provided password using the XChaCha20-Poly1305 encryption algorithm.

## Prerequisites

Before running the code, you need to have the [libsodium](https://libsodium.gitbook.io/doc/installation) library installed on your system.

## Code Structure

The code consists of two primary functions: `display_error_message` and `encrypt_file`, and a `main` function for user interaction.

### `display_error_message`

This function is responsible for displaying error messages on the standard error output. It is used to report errors encountered during initialization, file operations, and encryption.

### `encrypt_file`

This function handles the core file encryption process:

1. It initializes the libsodium library using `sodium_init()` to ensure it's ready for cryptographic operations.

2. Generates a random salt to be used for key derivation using `randombytes_buf`. The salt is also written to the beginning of the output file.

3. Opens the input and output files in binary mode, checks if they opened successfully, and reports an error if not.

4. Derives an encryption key from the user-provided password and the generated salt using `crypto_pwhash`.

5. Initializes a `crypto_secretstream_xchacha20poly1305` state for encryption with a random nonce.

6. Reads data from the input file in chunks, encrypts each chunk, and writes the encrypted data to the output file. It uses `crypto_secretstream_xchacha20poly1305_push` for encryption.

### `main`

The `main` function is responsible for user interaction. It does the following:

1. Defines the input and output filenames and a password buffer.

2. Prompts the user to enter their password securely. It reads the password using `fgets` and removes the newline character.

3. Calls the `encrypt_file` function to perform file encryption with the provided password.

4. Displays a success message if the encryption process is completed successfully.

5. Handles any errors that may occur during the process by calling `display_error_message`.

## Running the Code

Before running the code, make sure you have the `libsodium` library installed. After compilation, execute the program. You'll be prompted to enter a password, and the plaintext file will be encrypted using XChaCha20-Poly1305.

