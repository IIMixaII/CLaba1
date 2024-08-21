#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
int main() {
    std::map<std::string, int> flights;
    setlocale(LC_ALL, "rus");

    // Чтение содержимого файла и заполнение словаря данными о рейсах
    std::ifstream file("flights.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::size_t pos = line.find("-");
            if (pos != std::string::npos) {
                std::string flight = line.substr(0, pos);
                int seats = std::stoi(line.substr(pos + 1));
                flights[flight] = seats;
            }
        }
        file.close();
    }

    // Вывод информации о свободных местах по запросу пользователя
    std::string flightNumber;
    std::cout << "Введите номер рейса: ";
    std::cin >> flightNumber;

    if (flights.count(flightNumber) > 0) {
        int seatsAvailable = flights[flightNumber];
        std::cout << "Свободных мест на рейсе " << flightNumber << ": " << seatsAvailable << std::endl;

        //"Продажа" одного билета на рейс
        std::cout << "Если хотите купить билеты на данный рейснажмите 'y'" << endl;
        char answer;
        cin >> answer;
        if (answer == 'y') {
            if (seatsAvailable > 0) {
                flights[flightNumber]--;
                std::cout << "Билет продан." << std::endl;
            }
            else {
                std::cout << "Нет свободных мест." << std::endl;
            }
        }
        else {
            cout << "exit";
        }

    }
    else {
        std::cout << "Рейс с таким номером не найден." << std::endl;
    }

    // Обновление содержимого файла с новыми данными о рейсах
    std::ofstream outfile("flights.txt");
    if (outfile.is_open()) {
        for (const auto& pair : flights) {
            outfile << pair.first << " - " << pair.second << std::endl;
        }
        outfile.close();
    }

    std::ofstream files("flights.txt", std::ios::app); // Открываем файл для дозаписи

    if (!files.is_open()) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    // Добавляем произвольные числа (положительные и отрицательные)
    files << 10 << std::endl;
    files << -5 << std::endl;
    files << 20 << std::endl;
    files << -8 << std::endl;
    files << 15 << std::endl;

    files.close(); // Закрываем файл

    std::ifstream files1("flights.txt"); // Открываем файл для чтения
    if (!files1.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    int negative_count = 0;
    double number;

    // Построчное чтение файла и анализ чисел
    while (files1 >> number) {
        if (number < 0) {
            negative_count++;
        }
    }

    file.close(); // Закрываем файл

    std::cout << "Количество отрицательных чисел в файле: " << negative_count << std::endl;

    return 0;
}
