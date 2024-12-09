#include "core/Assistant.h"
#include "windows.h"

std::atomic<bool> isRunning(true);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Assistant assistant;

    assistant.Run();

    std::cout << "Нажмите Enter для завершения...\n";
    std::cin.get();

    return 0;
}
