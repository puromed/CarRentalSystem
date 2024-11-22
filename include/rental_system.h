#ifndef RENTAL_SYSTEM_H
#define RENTAL_SYSTEM_H

#include <memory>
#include "user_manager.h"
#include "car_manager.h"
#include "booking_manager.h"

class RentalSystem {
private:
	UserManager userManager;
	CarManager carManager;
	BookingManager bookingManager;
	const User* currentUser; // Currently logged-in user


public:
	// Constructor
	RentalSystem();

	// User operations
	
	bool registerUser(const std::string& name, const std::string& email,
		const std::string& password, bool isAdmin = false);
	bool login(const std::string& email, const std::string& password);
	void logout();
	bool isLoggedIn() const;
	bool isCurrentUserAdmin() const;

	// Car operations
	bool addCar(const std::string& brand, const std::string& model,
		int hourlyRate, int seats);
	bool removeCar(size_t carIndex);
	std::vector<const Car*> searchAvailableCars(int date, int startHour, int endHour) const;
	std::vector<const Car*> searchCarsByBrand(const std::string& brand) const;
	std::vector<const Car*> searchCarsBySeats(int seats) const;

	// Booking operations
	bool createBooking(size_t carIndex, int date, int startHour, int endHour, const std::string& paymentMethod);
	bool cancelBooking(size_t bookingId);
	std::vector<const Booking*> getCurrentUserBookings() const;

	// System information
	std::string generateSystemReport() const;
	size_t getCarCount() const;
	size_t getUserCount() const;
	size_t getBookingCount() const;
};

#endif // RENTAL_SYSTEM_H