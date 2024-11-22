#ifndef CAR_MANAGER_H
#define CAR_MANAGER_H

#include <vector>
#include <memory>
#include "car.h"

class CarManager {
private:
	std::vector<std::unique_ptr<Car>> cars;

public:
	//constructor
	CarManager();

	// Car management methods
	void addCar(const std::string& brand, const std::string& model, int hourlyRate, int seats);
	bool removeCar(size_t index);

	// Search and filter methods
	std::vector<size_t> findCarsByBrand(const std::string& brand) const;
	std::vector<size_t> findCarsBySeats(int seats) const;
	std::vector<size_t> findAvailableCars(int date, int startHour, int endHour) const;

	// Getters

	size_t getCarCount() const;
	const Car* getCar(size_t index) const;

	// Booking methods
	bool bookCar(size_t index, int date, int startHour, int endHour);
	double calculateBookingCost(size_t index, int startHour, int endHour) const;
};

#endif // CAR_MANAGER_H