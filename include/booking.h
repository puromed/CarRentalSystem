#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "user.h"
#include "car.h"

class Booking {
private:
	// Booking details
	size_t bookingId;
	const User* user;
	const Car* car;
	int date;
	int startHour;
	int endHour;

	//payment information
	double totalCost;
	bool isPaid;

	//static members
	std::string paymentMethod;
	static size_t nextBookingId; // To generate unique booking IDs

public:
	// Constructor
	Booking(const User* user, const Car* car, int date, int startHour, int endHour, const std::string& paymentMethod);

	// Getters
	size_t getBookingId() const;
	const User* getUser() const;
	const Car* getCar() const;
	int getDate() const;
	int getStartHour() const;
	int getEndHour() const;
	double getTotalCost() const;
	bool getIsPaid() const;
	std::string getPaymentMethod() const;

	// Methods
	bool processPayment();
	void cancelBooking();
	std::string getBookingDetails() const;
};

#endif // BOOKING_H
