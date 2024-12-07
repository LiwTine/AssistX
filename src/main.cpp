#include "core/Assistant.h"
#include "windows.h"

std::atomic<bool> isRunning(true);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Assistant assistant;

    assistant.Run();

    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Пауза, чтобы не перегружать процессор
    }

    return 0;
}
