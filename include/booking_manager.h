#ifndef BOOKING_MANAGER_H
#define BOOKING_MANAGER_H

#include <vector>
#include <memory>
#include "booking.h"
#include "user.h"
#include "car.h"

class BookingManager {
private:
	std::vector<std::unique_ptr<Booking>> bookings;

public:
	// Constructor
	BookingManager();

	// Booking management methods
	bool createBooking(const User* user, const Car* car, int date,
					  int startHour, int endHour, const std::string& paymentMethod);
	bool cancelBooking(size_t bookingId);

	// Booking retrieval methods
	const Booking* getBooking(size_t bookingId) const;
	std::vector<const Booking*> getUserBookings(const User* user) const;
	std::vector<const Booking*> getCarBookings(const Car* car) const;
	std::vector<const Booking*> getActiveBookings() const;

	// Payment methods
	bool processPayment(size_t bookingId);

	// Utility methods
	size_t getBookingCount() const;
	std::string generateBookingReport() const;
};

#endif // BOOKING_MANAGER_H