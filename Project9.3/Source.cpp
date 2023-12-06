#include <iostream>
#include <fstream>
#include <string>

// Максимальна кількість офісів
const int MAX_OFFICES = 100;

// Максимальна кількість працівників у кожному офісі
const int MAX_EMPLOYEES_PER_OFFICE = 4;

// Структура для представлення працівника
struct Employee {
    std::string lastName; // Прізвище працівника
    std::string phoneNumber; // Номер телефону працівника
};

// Структура для представлення офісу
struct Office {
    int roomNumber; // Номер кімнати офісу
    Employee employees[MAX_EMPLOYEES_PER_OFFICE]; // Масив працівників в офісі
    int employeeCount; // Поточна кількість працівників в офісі

    // Конструктор за замовчуванням
    Office() {
        roomNumber = 0;
        employeeCount = 0;
    }

    // Конструктор з параметром для задання номеру кімнати
    Office(int room) {
        roomNumber = room;
        employeeCount = 0;
    }

    // Метод для додавання працівника до офісу
    void addEmployee(const std::string& phoneNumber, const std::string& lastName) {
        if (employeeCount < MAX_EMPLOYEES_PER_OFFICE) {
            employees[employeeCount].phoneNumber = phoneNumber;
            employees[employeeCount].lastName = lastName;
            employeeCount++;
        }
        else {
            std::cout << "Office is full. Cannot add more employees.\n";
        }
    }

    // Метод для знаходження працівника за номером телефону
    int findEmployeeByPhoneNumber(const std::string& phoneNumber, Employee& foundEmployee) const {
        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i].phoneNumber == phoneNumber) {
                foundEmployee = employees[i];
                return 1; // Успішне знаходження працівника
            }
        }
        return 0; // Невдача у знаходженні працівника
    }
};

// Функція для додавання працівника до офісу за заданим номером
void addEmployee(Office* offices, int& officeCount, const std::string& phoneNumber, const std::string& lastName, int roomNumber) {
    if (roomNumber < 1 || roomNumber > 99) {
        std::cout << "Invalid room number. Room number must be between 1 and 99.\n";
        return;
    }

    int index = -1;
    for (int i = 0; i < officeCount; ++i) {
        if (offices[i].roomNumber == roomNumber) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        offices[officeCount].roomNumber = roomNumber;
        offices[officeCount].employeeCount = 0;
        index = officeCount;
        officeCount++;
    }

    offices[index].addEmployee(phoneNumber, lastName);
}

// Функція для знаходження працівника за номером телефону у всіх офісах
int findEmployeeByPhoneNumber(const Office* offices, int officeCount, const std::string& phoneNumber, Employee& foundEmployee) {
    for (int i = 0; i < officeCount; ++i) {
        if (offices[i].findEmployeeByPhoneNumber(phoneNumber, foundEmployee)) {
            return 1; // Успішне знаходження працівника
        }
    }
    return 0; // Невдача у знаходженні працівника
}

// Функція для видалення працівника за номером телефону
void removeEmployee(Office* offices, int officeCount, const std::string& phoneNumber) {
    for (int i = 0; i < officeCount; ++i) {
        for (int j = 0; j < offices[i].employeeCount; ++j) {
            if (offices[i].employees[j].phoneNumber == phoneNumber) {
                // Замінюємо знайденого працівника останнім працівником
                offices[i].employees[j] = offices[i].employees[offices[i].employeeCount - 1];
                offices[i].employeeCount--;
                return;
            }
        }
    }
    std::cout << "Employee with the given phone number not found.\n";
}

// Функція для редагування інформації про працівника
void editEmployee(Office* offices, int officeCount, const std::string& phoneNumber, const std::string& newLastName, int newRoomNumber) {
    Employee foundEmployee;
    if (findEmployeeByPhoneNumber(offices, officeCount, phoneNumber, foundEmployee)) {
        for (int i = 0; i < officeCount; ++i) {
            if (offices[i].findEmployeeByPhoneNumber(phoneNumber, foundEmployee)) {
                offices[i].employees[i].lastName = newLastName;
                if (newRoomNumber != -1) {
                    addEmployee(offices, officeCount, phoneNumber, newLastName, newRoomNumber);
                }
                return;
            }
        }
    }
    else {
        std::cout << "Employee with the given phone number not found.\n";
    }
}

// Функція для виведення інформації про всі офіси та їх працівників
void displayInfo(const Office* offices, int officeCount) {
    for (int i = 0; i < officeCount; ++i) {
        std::cout << "Room Number: " << offices[i].roomNumber << "\n";
        std::cout << "Employees in the Room:\n";
        for (int j = 0; j < offices[i].employeeCount; ++j) {
            std::cout << "  Last Name: " << offices[i].employees[j].lastName << "\n";
            std::cout << "  Phone Number: " << offices[i].employees[j].phoneNumber << "\n";
            std::cout << "-------------------------\n";
        }
    }
}

// Функція для виведення інформації про працівника за номером телефону
int displayRoomInfo(const Office* offices, int officeCount, const std::string& phoneNumber) {
    Employee foundEmployee;
    if (findEmployeeByPhoneNumber   (offices, officeCount, phoneNumber, foundEmployee)) {
        std::cout << "Employee Found:\n";
        std::cout << "  Last Name: " << foundEmployee.lastName << "\n";
        std::cout << "  Phone Number: " << foundEmployee.phoneNumber << "\n";
        return 1; // Успішне знаходження працівника
    }
    else {
        std::cout << "No information found for the given phone number.\n";
        return 0; // Невдача у знаходженні працівника
    }
}

// Головна функція програми
int main() {
    // Виділення пам'яті для масиву офісів
    Office* offices = new Office[MAX_OFFICES];
    int officeCount = 0; // Початкова кількість офісів

    // Головний цикл програми
    do {
        std::cout << "\nTelephone Directory Menu:\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. Remove Employee\n";
        std::cout << "3. Edit Employee\n";
        std::cout << "4. Display Directory Info\n";
        std::cout << "5. Display Room Info\n";
        std::cout << "0. Exit\n";

        int choice;
        std::cout << "Enter your choice (0-5): ";
        std::cin >> choice;

        // Обробка вибору користувача
        switch (choice) {
        case 1: {
            std::string phoneNumber, lastName;
            int roomNumber;
            std::cout << "Enter phone number: ";
            std::cin >> phoneNumber;
            std::cout << "Enter last name: ";
            std::cin >> lastName;
            std::cout << "Enter room number: ";
            std::cin >> roomNumber;
            addEmployee(offices, officeCount, phoneNumber, lastName, roomNumber);
            break;
        }
        case 2: {
            std::string phoneNumber;
            std::cout << "Enter phone number to remove: ";
            std::cin >> phoneNumber;
            removeEmployee(offices, officeCount, phoneNumber);
            break;
        }
        case 3: {
            std::string phoneNumber, newLastName;
            int newRoomNumber;
            std::cout << "Enter phone number to edit: ";
            std::cin >> phoneNumber;
            std::cout << "Enter new last name: ";
            std::cin >> newLastName;
            std::cout << "Enter new room number (-1 to keep the same): ";
            std::cin >> newRoomNumber;
            editEmployee(offices, officeCount, phoneNumber, newLastName, newRoomNumber);
            break;
        }
        case 4:
            displayInfo(offices, officeCount);
            break;
        case 5: {
            std::string phoneNumber;
            std::cout << "Enter phone number to display room info: ";
            std::cin >> phoneNumber;
            displayRoomInfo(offices, officeCount, phoneNumber);
            break;
        }
        case 0:
            std::cout << "Exiting the program. Goodbye!\n";
            delete[] offices; // Звільнення виділеної пам'яті
            return 0;
        default:
            std::cout << "Invalid choice. Please enter a number between 0 and 5.\n";
        }
    } while (true);

    // Звільнення виділеної пам'яті перед завершенням програми
    delete[] offices;
    return 0;
}
