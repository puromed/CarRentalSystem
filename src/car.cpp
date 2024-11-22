#include "../include/car.h"

Car::Car(const std::string& brand, const std::string& model, int hourlyRate, int seats)
	: brand(brand), model(model), hourlyRate(hourlyRate), seats(seats) {}

std::string Car::getBrand() const {
	return brand;
}

std::string Car::getModel() const {
	return model;
}

int Car::getHourlyRate() const {
	return hourlyRate;
}

int Car::getSeats() const {
	return seats;
}

bool Car::isAvailable(int date, int startHour, int endHour) const {
		if (schedule.find(date) == schedule.end()) {
			return true;
		}
		
		for (const auto& booking : schedule.at(date)) {
			if (!(endHour <= booking.first || startHour >= booking.second)) {
				return false;
			}
			
		}
		return true;
}

bool Car::addBooking(int date, int startHour, int endHour) {
	if (!isAvailable(date, startHour, endHour)) {
		return false;
	}
	schedule[date].push_back(std::make_pair(startHour, endHour));
	return true;
}

double Car::calculateCost(int startHour, int endHour) const {
	return hourlyRate * (endHour - startHour);
}