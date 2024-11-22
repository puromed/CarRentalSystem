#include "../include/rental_system.h"
#include <iostream>
#include <limits>
#include <iomanip>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pauseConsole() {
    std::cout << "\nPress Enter to continue...";
    clearInputBuffer();
}

class CarRentalApp {
private:
    RentalSystem system;

    void displayMainMenu() {
        std::cout << "\n=== Car Rental System ===\n"
            << "1. Login\n"
            << "2. Register\n"
            << "3. Exit\n"
            << "Choose an option: ";
    }

    void displayUserMenu() {
        std::cout << "\n=== Car Rental System - User Menu ===\n"
            << "1. View Available Cars\n"
            << "2. Search Cars by Brand\n"
            << "3. Search Cars by Seats\n"
            << "4. Create Booking\n"
            << "5. View My Bookings\n"
            << "6. Cancel Booking\n"
            << "7. Logout\n"
            << "Choose an option: ";
    }

    void displayAdminMenu() {
        std::cout << "\n=== Car Rental System - Admin Menu ===\n"
            << "1. Add Car\n"
            << "2. Remove Car\n"
            << "3. View System Report\n"
            << "4. Logout\n"
            << "Choose an option: ";
    }

    void registerUser() {
        std::string name, email, password;

        std::cout << "\n=== User Registration ===\n";

        while (true) {
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            if (name.empty()) {
                std::cout << "Name cannot be empty.\n";
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter email: ";
            std::getline(std::cin, email);
            if (email.empty()) {
                std::cout << "Email cannot be empty.\n";
                continue;
            }
            // Basic email format validation
            if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
                std::cout << "Invalid email format. Must contain '@' and '.'.\n";
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            if (password.length() < 6) {
                std::cout << "Password must be at least 6 characters long.\n";
                continue;
            }
            break;
        }

        if (system.registerUser(name, email, password)) {
            std::cout << "\nRegistration successful!\n";
        }
        else {
            std::cout << "\nRegistration failed. Email might already be in use.\n";
        }
        pauseConsole();
    }

    bool loginUser() {
        std::string email, password;

        std::cout << "\n=== User Login ===\n";

        while (true) {
            std::cout << "Enter email: ";
            std::getline(std::cin, email);
            if (email.empty()) {
                std::cout << "Email cannot be empty.\n";
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            if (password.empty()) {
                std::cout << "Password cannot be empty.\n";
                continue;
            }
            break;
        }

        if (system.login(email, password)) {
            std::cout << "\nLogin successful!\n";
            pauseConsole();
            return true;
        }
        else {
            std::cout << "\nLogin failed. Invalid email or password.\n";
            pauseConsole();
            return false;
        }
    }

    void viewAvailableCars() {
        int date, startHour, endHour;

        while (true) {
            std::cout << "\nEnter date (YYYYMMDD): ";
            if (!(std::cin >> date) || date < 20230000 || date > 20301231) {
                std::cout << "Invalid date format. Please use YYYYMMDD between 2023 and 2030. \n";
                clearInputBuffer();
                continue;
            }

            std::cout << "Enter start hour (0-23): ";
            if (!(std::cin >> startHour) || startHour < 0 || startHour > 23) {
                std::cout << "Invalid hour. Please enter a number between 0 and 23.\n";
                clearInputBuffer();
                continue;
            }

            std::cout << "Enter end hour (0-23): ";
            if (!(std::cin >> endHour) || endHour < 0 || endHour > 23 || endHour <= startHour) {
                std::cout << "Invalid hour. End hour must be between " << startHour + 1 << "and 23. \n";
                clearInputBuffer();
                continue;
            }
            break;


        }
        clearInputBuffer();
       

        auto cars = system.searchAvailableCars(date, startHour, endHour);
        if (cars.empty()) {
            std::cout << "\nNo cars available for the specified time period.\n";
        }
        else {
            std::cout << "\nAvailable Cars:\n";
            for (const auto& car : cars) {
                std::cout << "Brand: " << car->getBrand()
                    << ", Model: " << car->getModel()
                    << ", Seats: " << car->getSeats()
                    << ", Rate: $" << car->getHourlyRate() << "/hour\n";
            }
        }
        pauseConsole();
    }

    void searchCarsByBrand() {
        std::string brand;
        std::cout << "\nEnter car brand: ";
        std::getline(std::cin, brand);

        auto cars = system.searchCarsByBrand(brand);
        if (cars.empty()) {
            std::cout << "\nNo cars found for brand: " << brand << "\n";
        }
        else {
            std::cout << "\nFound Cars:\n";
            for (const auto& car : cars) {
                std::cout << "Model: " << car->getModel()
                    << ", Seats: " << car->getSeats()
                    << ", Rate: $" << car->getHourlyRate() << "/hour\n";
            }
        }
        pauseConsole();
    }

    void searchCarsBySeats() {
        int seats;
        while (true) {
            std::cout << "\nEnter number of seats (1-10): ";
            if (!(std::cin >> seats) || seats <= 0 || seats > 10) {
                std::cout << "Invalid number of seats. Please enter a number between 1 and 10.\n";
                clearInputBuffer();
                continue;
            }
            break;
        }
        clearInputBuffer();

        auto cars = system.searchCarsBySeats(seats);
        if (cars.empty()) {
            std::cout << "\nNo cars found with " << seats << " seats.\n";
        }
        else {
            std::cout << "\nFound Cars:\n";
            for (const auto& car : cars) {
                std::cout << "Brand: " << car->getBrand()
                    << ", Model: " << car->getModel()
                    << ", Rate: $" << car->getHourlyRate() << "/hour\n";
            }
        }
        pauseConsole();
    }

    void createBooking() {
        size_t carIndex;
        int date, startHour, endHour;
        std::string paymentMethod;

        std::cout << "\n=== Create Booking ===\n";

        while (true) {
            std::cout << "Enter car index: ";
            if (!(std::cin >> carIndex)) {
                std::cout << "Invalid car index. Please enter a non-negative number.\n";
                clearInputBuffer();
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter date (YYYYMMDD): ";
            if (!(std::cin >> date) || date < 20230000 || date > 20301231) {
                std::cout << "Invalid date format. Please use YYYYMMDD between 2023 and 2030.\n";
                clearInputBuffer();
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter start hour (0-23): ";
            if (!(std::cin >> startHour) || startHour < 0 || startHour > 23) {
                std::cout << "Invalid hour. Please enter a number between 0 and 23.\n";
                clearInputBuffer();
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter end hour (0-23): ";
            if (!(std::cin >> endHour) || endHour < 0 || endHour > 23 || endHour <= startHour) {
                std::cout << "Invalid hour. End hour must be between " << startHour + 1 << " and 23.\n";
                clearInputBuffer();
                continue;
            }
            break;
        }
        clearInputBuffer();

        while (true) {
            std::cout << "Enter payment method: ";
            std::getline(std::cin, paymentMethod);
            if (paymentMethod.empty()) {
                std::cout << "Payment method cannot be empty.\n";
                continue;
            }
            break;
        }

        if (system.createBooking(carIndex, date, startHour, endHour, paymentMethod)) {
            std::cout << "\nBooking created successfully!\n";
        }
        else {
            std::cout << "\nBooking failed. Please check car availability and login status.\n";
        }
        pauseConsole();
    }

    void viewMyBookings() {
        auto bookings = system.getCurrentUserBookings();
        if (bookings.empty()) {
            std::cout << "\nYou have no bookings.\n";
        }
        else {
            std::cout << "\nYour Bookings:\n";
            for (const auto& booking : bookings) {
                std::cout << "Booking ID: " << booking->getBookingId()
                    << "\nCar: " << booking->getCar()->getBrand() << " " << booking->getCar()->getModel()
                    << "\nDate: " << booking->getDate()
                    << "\nTime: " << booking->getStartHour() << ":00 - " << booking->getEndHour() << ":00"
                    << "\nStatus: " << (booking->getIsPaid() ? "Paid" : "Pending")
                    << "\n\n";
            }
        }
        pauseConsole();
    }

    void cancelBooking() {
        size_t bookingId;
        std::cout << "\nEnter booking ID to cancel: ";
        std::cin >> bookingId;
        clearInputBuffer();

        if (system.cancelBooking(bookingId)) {
            std::cout << "\nBooking cancelled successfully!\n";
        }
        else {
            std::cout << "\nCancellation failed. Please check booking ID and login status.\n";
        }
        pauseConsole();
    }

    void addCar() {
        std::string brand, model;
        int hourlyRate, seats;

        std::cout << "\n=== Add New Car ===\n";

        std::cout << "Enter car brand: ";
        std::getline(std::cin, brand);

        std::cout << "Enter car model: ";
        std::getline(std::cin, model);

        std::cout << "Enter hourly rate: ";
        std::cin >> hourlyRate;
        clearInputBuffer();

        std::cout << "Enter number of seats: ";
        std::cin >> seats;
        clearInputBuffer();

        if (system.addCar(brand, model, hourlyRate, seats)) {
            std::cout << "\nCar added successfully!\n";
        }
        else {
            std::cout << "\nFailed to add car.\n";
        }
        pauseConsole();
    }

    void removeCar() {
        std::cout << "\n=== Remove Car ===\n";
        displayAllCars();

        std::cout << "\nEnter car index to remove: ";
        size_t index;
        std::cin >> index;
        clearInputBuffer();

        if (system.removeCar(index - 1)) {  // Convert to 0-based index
            std::cout << "\nCar removed successfully!\n";
        }
        else {
            std::cout << "\nFailed to remove car. Invalid index.\n";
        }
        pauseConsole();
    }

    void viewSystemReport() {
        std::cout << "\n=== System Report ===\n";
        std::cout << system.generateSystemReport();
        pauseConsole();
    }

    void displayAllCars() {
        std::cout << "\nAvailable Cars:\n";
        auto cars = system.searchAvailableCars(0, 0, 24);  // Show all cars
        if (cars.empty()) {
            std::cout << "No cars available.\n";
            return;
        }

        std::cout << std::setw(5) << "Index" << std::setw(15) << "Brand"
            << std::setw(15) << "Model" << std::setw(15) << "Rate/Hour"
            << std::setw(10) << "Seats" << "\n";
        std::cout << std::string(60, '-') << "\n";

        for (size_t i = 0; i < cars.size(); ++i) {
            std::cout << std::setw(5) << (i + 1)  // 1-based index for display
                << std::setw(15) << cars[i]->getBrand()
                << std::setw(15) << cars[i]->getModel()
                << std::setw(15) << cars[i]->getHourlyRate()
                << std::setw(10) << cars[i]->getSeats() << "\n";
        }
    }

   

public:
    void run() {
        bool running = true;
        while (running) {
            if (!system.isLoggedIn()) {
                clearScreen();
                displayMainMenu();
            }
           

            char choice;
            std::cin >> choice;
            clearInputBuffer();

            switch (choice) {
            case '1': {
                if (loginUser()) {
                    if (system.isCurrentUserAdmin()) {
                        runAdminMenu();
                    }
                    else {
                        runUserMenu();
                    }
                }
                break;
            }
            case '2':
                registerUser();
                break;
            case '3':
                running = false;
                break;
            default:
                std::cout << "\nInvalid option. Please try again.\n";
                pauseConsole();
            }
        }
        std::cout << "\nThank you for using Car Rental System!\n";
    }

    void runAdminMenu() {
        bool adminLoggedIn = true;
        while (adminLoggedIn) {
            clearScreen();
            displayAdminMenu();

            char choice;
            std::cin >> choice;
            clearInputBuffer();

            switch (choice) {
            case '1':
                addCar();
                break;
            case '2':
                removeCar();
                break;
            case '3':
                viewSystemReport();
                break;
            case '4':
                system.logout();
                adminLoggedIn = false;
                break;
            default:
                std::cout << "\nInvalid option. Please try again.\n";
                pauseConsole();
            }
        }
    }

    void runUserMenu() {
        bool userLoggedIn = true;
        while (userLoggedIn) {
            clearScreen();
            displayUserMenu();

            char choice;
            std::cin >> choice;
            clearInputBuffer();

            switch (choice) {
            case '1':
                viewAvailableCars();
                break;
            case '2':
                searchCarsByBrand();
                break;
            case '3':
                searchCarsBySeats();
                break;
            case '4':
                createBooking();
                break;
            case '5':
                viewMyBookings();
                break;
            case '6':
                cancelBooking();
                break;
            case '7':
                system.logout();
                userLoggedIn = false;
                break;
            default:
                std::cout << "\nInvalid option. Please try again.\n";
                pauseConsole();
            }
        }
    }
};

int main() {
    CarRentalApp app;
    app.run();
    return 0;
}