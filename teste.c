#include <stdio.h>

int main() {

#ifdef _WIN32
    printf("Sistema operacional: Windows\n");
#elif __APPLE__
    printf("Sistema operacional: macOS\n");
#elif __linux__
    printf("Sistema operacional: Linux\n");
#else
    printf("Sistema operacional desconhecido\n");
#endif

    return 0;
}