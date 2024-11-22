#include "../include/rental_system.h"
#include <sstream>

RentalSystem::RentalSystem() : currentUser(nullptr) {}

bool RentalSystem::registerUser(const std::string& name, const std::string& email,
	const std::string& password, bool isAdmin) {
	return userManager.registerUser(name, email, password);
}

bool RentalSystem::login(const std::string& email, const std::string& password) {
	currentUser = userManager.loginUser(email, password);
	return currentUser != nullptr;
}

void RentalSystem::logout() {
	currentUser = nullptr;
}

bool RentalSystem::isLoggedIn() const {
	return currentUser != nullptr;
}

bool RentalSystem::addCar(const std::string& brand, const std::string& model,
	int hourlyRate, int seats) {
	carManager.addCar(brand, model, hourlyRate, seats);
	return true;
}

bool RentalSystem::removeCar(size_t carIndex) {
	return carManager.removeCar(carIndex);
}

std::vector<const Car*> RentalSystem::searchAvailableCars(int date, int startHour,
	int endHour) const {
	std::vector<size_t> indices = carManager.findAvailableCars(date, startHour, endHour);
	std::vector<const Car*> results;
	for (size_t idx : indices) {
		results.push_back(carManager.getCar(idx));
	}
	return results;
}

std::vector<const Car*> RentalSystem::searchCarsByBrand(const std::string& brand) const {
	std::vector<size_t> indices = carManager.findCarsByBrand(brand);
	std::vector<const Car*> results;
	for (size_t idx : indices) {
		results.push_back(carManager.getCar(idx));
	}
	return results;
}

std::vector<const Car*> RentalSystem::searchCarsBySeats(int seats) const {
	std::vector<size_t> indices = carManager.findCarsBySeats(seats);
	std::vector<const Car*> results;
	for (size_t idx : indices) {
		results.push_back(carManager.getCar(idx));
	}
	return results;
}

bool RentalSystem::isCurrentUserAdmin() const {
	if (!currentUser) {
		return false;
	}
	// Check if the current user has the admin email
	return currentUser->getEmail() == "admin@rental.com";
}

bool RentalSystem::createBooking(size_t carIndex, int date, int startHour,
	int endHour, const std::string& paymentMethod) {
	if (!isLoggedIn()) {
		return false;
	}

	const Car* car = carManager.getCar(carIndex);
	if (!car || !car->isAvailable(date, startHour, endHour)) {
		return false;
	}

	return bookingManager.createBooking(currentUser, car, date, startHour, endHour, paymentMethod);
}

bool RentalSystem::cancelBooking(size_t bookingId) {
	if (!isLoggedIn()) {
		return false;
	}
	return bookingManager.cancelBooking(bookingId);
}

std::vector<const Booking*> RentalSystem::getCurrentUserBookings() const {
	if (!isLoggedIn()) {
		return std::vector<const Booking*>();
	}
	return bookingManager.getUserBookings(currentUser);
}

std::string RentalSystem::generateSystemReport() const {
	std::stringstream ss;
	ss << "=== System Report ===\n"
		<< "Users: " << getUserCount() << "\n"
		<< "Cars: " << getCarCount() << "\n"
		<< "Bookings: " << getBookingCount() << "\n";
	return ss.str();
}

size_t RentalSystem::getCarCount() const {
	return carManager.getCarCount();
}

size_t RentalSystem::getUserCount() const {
	return userManager.getUserCount();
}

size_t RentalSystem::getBookingCount() const {
	return bookingManager.getBookingCount();
}