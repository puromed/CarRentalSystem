#include "../include/booking_manager.h"
#include <sstream>
#include <algorithm>

BookingManager::BookingManager() {}

bool BookingManager::createBooking(const User* user, const Car* car, int date,
	int startHour, int endHour, const std::string& paymentMethod) {

	if (!user || !car) {
		return false;
	}

	// Check if car is available for the requested time
	if (!car->isAvailable(date, startHour, endHour)) {
		return false;
	}

    // Update the car's schedule first
    if (!const_cast<Car*>(car)->addBooking(date, startHour, endHour)) {
        return false;
    }

	// Create and store the booking
	bookings.push_back(std::make_unique<Booking>(user, car, date, startHour, endHour, paymentMethod));
	return true;
}

bool BookingManager::cancelBooking(size_t bookingId) {
	auto it = std::find_if(bookings.begin(), bookings.end(),
		[bookingId](const std::unique_ptr<Booking>& booking) {
			return booking->getBookingId() == bookingId;
		});

	if (it != bookings.end()) {
		(*it)->cancelBooking();
        bookings.erase(it);
		return true;
	}
	return false;
}

const Booking* BookingManager::getBooking(size_t bookingId) const {
    auto it = std::find_if(bookings.begin(), bookings.end(),
        [bookingId](const std::unique_ptr<Booking>& booking) {
            return booking->getBookingId() == bookingId;
        });

    return (it != bookings.end()) ? it->get() : nullptr;
}

std::vector<const Booking*> BookingManager::getUserBookings(const User* user) const {
    std::vector<const Booking*> result;
    for (const auto& booking : bookings) {
        if (booking->getUser() == user) {
            result.push_back(booking.get());
        }
    }
    return result;
}

std::vector<const Booking*> BookingManager::getCarBookings(const Car* car) const {
    std::vector<const Booking*> result;
    for (const auto& booking : bookings) {
        if (booking->getCar() == car) {
            result.push_back(booking.get());
        }
    }
    return result;
}

std::vector<const Booking*> BookingManager::getActiveBookings() const {
    std::vector<const Booking*> result;
    for (const auto& booking : bookings) {
        if (booking->getIsPaid()) {
            result.push_back(booking.get());
        }
    }
    return result;
}

bool BookingManager::processPayment(size_t bookingId) {
    auto it = std::find_if(bookings.begin(), bookings.end(),
        [bookingId](const std::unique_ptr<Booking>& booking) {
            return booking->getBookingId() == bookingId;
        });

    if (it != bookings.end()) {
        return (*it)->processPayment();
    }
    return false;
}

size_t BookingManager::getBookingCount() const {
    return bookings.size();
}

std::string BookingManager::generateBookingReport() const {
    std::stringstream ss;
    ss << "=== Booking Report ===\n"
       << "Total Bookings: " << bookings.size() << "\n\n";

    for (const auto& booking : bookings) {
        ss << booking->getBookingDetails() << "\n"
            << "----------------------\n";
    }

    return ss.str();
}
