#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>
#include <map>
#include <utility>

class Car {
private:
	std::string brand;
	std::string model;
	int hourlyRate;
	int seats;
	std::map<int, std::vector<std::pair<int, int>>> schedule; // date -> vector of  <start, end> times

public:
 //constructor
	Car(const std::string& brand, const std::string& model, int hourlyRate, int seats);

 // Getters
	std::string getBrand() const;
	std::string getModel() const;
	int getHourlyRate() const;
	int getSeats() const;

	// Booking methods
	bool isAvailable(int date, int startHour, int endHour) const;
	bool addBooking(int date, int startHour, int endHour);
	double calculateCost(int startHour, int endHour) const;
};

#endif // CAR_H