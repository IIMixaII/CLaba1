#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
int main() {
    std::map<std::string, int> flights;
    setlocale(LC_ALL, "rus");

    // ������ ����������� ����� � ���������� ������� ������� � ������
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

    // ����� ���������� � ��������� ������ �� ������� ������������
    std::string flightNumber;
    std::cout << "������� ����� �����: ";
    std::cin >> flightNumber;

    if (flights.count(flightNumber) > 0) {
        int seatsAvailable = flights[flightNumber];
        std::cout << "��������� ���� �� ����� " << flightNumber << ": " << seatsAvailable << std::endl;

        //"�������" ������ ������ �� ����
        std::cout << "���� ������ ������ ������ �� ������ ����������� 'y'" << endl;
        char answer;
        cin >> answer;
        if (answer == 'y') {
            if (seatsAvailable > 0) {
                flights[flightNumber]--;
                std::cout << "����� ������." << std::endl;
            }
            else {
                std::cout << "��� ��������� ����." << std::endl;
            }
        }
        else {
            cout << "exit";
        }

    }
    else {
        std::cout << "���� � ����� ������� �� ������." << std::endl;
    }

    // ���������� ����������� ����� � ������ ������� � ������
    std::ofstream outfile("flights.txt");
    if (outfile.is_open()) {
        for (const auto& pair : flights) {
            outfile << pair.first << " - " << pair.second << std::endl;
        }
        outfile.close();
    }

    std::ofstream files("flights.txt", std::ios::app); // ��������� ���� ��� ��������

    if (!files.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
        return 1;
    }

    // ��������� ������������ ����� (������������� � �������������)
    files << 10 << std::endl;
    files << -5 << std::endl;
    files << 20 << std::endl;
    files << -8 << std::endl;
    files << 15 << std::endl;

    files.close(); // ��������� ����

    std::ifstream files1("flights.txt"); // ��������� ���� ��� ������
    if (!files1.is_open()) {
        std::cerr << "�� ������� ������� ����." << std::endl;
        return 1;
    }

    int negative_count = 0;
    double number;

    // ���������� ������ ����� � ������ �����
    while (files1 >> number) {
        if (number < 0) {
            negative_count++;
        }
    }

    file.close(); // ��������� ����

    std::cout << "���������� ������������� ����� � �����: " << negative_count << std::endl;

    return 0;
}
