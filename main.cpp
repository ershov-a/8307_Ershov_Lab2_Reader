#include <iostream>
#include <windows.h>

int main() {
    char data[1024];

    // Открываем проецируемый файл
    HANDLE fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "mappedFile");
    if (fileHandle != INVALID_HANDLE_VALUE) {
        std::cout << "*** Mapping was opened successfully ***" << std::endl;
    }

    // Получаем стартовый адрес региона
    PVOID mapAddress = MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (mapAddress == nullptr){
        std::cerr << "*** Can not open MapView of file ***" << std::endl;
        return 1;
    }

    // Получаем данные из проекции
    memcpy(data, (char*)mapAddress, 1024);

    // Выводим адрес и данные
    std::cout << "Value at "<< mapAddress <<" is " << data << std::endl;

    char answer;
    std::cout << "Close Mapping? (y/n) " << std::endl;
    std::cin >> answer;
    // "Разрушаем" связь спроецированного региона и его ресурсом
    if (answer == 'y') {
        UnmapViewOfFile(mapAddress);
    }

    // Закрываем HANDLE'ы
    CloseHandle(fileHandle);

    return 0;
}
