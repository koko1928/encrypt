err.c
#include <stdio.h>

void display_error_message() {
    printf("You do not have the necessary permissions to run this program.\n");
    printf("This action may have legal and ethical implications.\n");
    printf("Please contact your system administrator for assistance.\n");
}

int main() {
    display_error_message();
    return 0;
}
