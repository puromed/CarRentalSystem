#include "../include/car_manager.h"
#include <algorithm>

CarManager::CarManager() {}

void CarManager::addCar(const std::string& brand, const std::string& model, int hourlyRate, int seats) {
	cars.push_back(std::make_unique<Car>(brand, model, hourlyRate, seats));
}

bool CarManager::removeCar(size_t index) {
	if (index < cars.size()) {
		cars.erase(cars.begin() + index);
		return true;
	}
	return false;
}

std::vector<size_t> CarManager::findCarsByBrand(const std::string& brand) const {
	std::vector<size_t> result;
	for (size_t i = 0; i < cars.size(); ++i) {
		if (cars[i]->getBrand() == brand) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<size_t> CarManager::findCarsBySeats(int seats) const {
	std::vector<size_t> result;
	for (size_t i = 0; i < cars.size(); ++i) {
		if (cars[i]->getSeats() == seats) {
			result.push_back(i);
		}
	}
	return result;
}

std::vector<size_t> CarManager::findAvailableCars(int date, int startHour, int endHour) const {
	std::vector<size_t> result;
	for (size_t i = 0; i < cars.size(); ++i) {
		if (cars[i]->isAvailable(date, startHour, endHour)) {
			result.push_back(i);
		}
	}
	return result;
}

size_t CarManager::getCarCount() const {
	return cars.size();
}

const Car* CarManager::getCar(size_t index) const {
	if (index < cars.size()) {
		return cars[index].get();
	}
	return nullptr;
}

bool CarManager::bookCar(size_t index, int date, int startHour, int endHour) {
	if (index < cars.size()) {
		return cars[index]->addBooking(date, startHour, endHour);
	}
	return false;
}

double CarManager::calculateBookingCost(size_t index, int startHour, int endHour) const {
	if (index < cars.size()) {
		return cars[index]->calculateCost(startHour, endHour);
	}
	return 0.0;
}