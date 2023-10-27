err.c
#include <stdio.h>

// エラーメッセージの表示を行う関数
void display_error_message() {
    printf("You do not have the necessary permissions to run this program.\n");
    printf("This action may have legal and ethical implications.\n");
    printf("Please contact your system administrator for assistance.\n");
}

int main() {
    // エラーメッセージの表示を呼び出す
    display_error_message();
    return 0;
}
