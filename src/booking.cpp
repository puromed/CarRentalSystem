#include "../include/booking.h"
#include <sstream>

size_t Booking::nextBookingId = 1; // Initialize static member

Booking::Booking(const User* user, const Car* car, int date, int startHour, int endHour, const std::string& paymentMethod)
	: bookingId(nextBookingId++),
	  user(user),
	  car(car),
	  date(date),
	  startHour(startHour),
	  endHour(endHour),
	  paymentMethod(paymentMethod),
	  isPaid(false)
{
	totalCost = car->calculateCost(startHour, endHour);
}

size_t Booking::getBookingId() const {
	return bookingId;
}

const User* Booking::getUser() const {
	return user;
}

const Car* Booking::getCar() const {
	return car;
}

int Booking::getDate() const {
	return date;
}

int Booking::getStartHour() const {
	return startHour;
}

int Booking::getEndHour() const {
	return endHour;
}

double Booking::getTotalCost() const {
	return totalCost;
}

bool Booking::getIsPaid() const {
	return isPaid;
}

std::string Booking::getPaymentMethod() const {
	return paymentMethod;
}

bool Booking::processPayment() {
	isPaid = true;
	return true;
}

void Booking::cancelBooking() {
	isPaid = false;
}

std::string Booking::getBookingDetails() const {
	std::stringstream ss;
	ss << "Booking ID: " << bookingId << "\n"
		<< "User: " << user->getName() << "\n"
		<< "Car: " << car->getBrand() << " " << car->getModel() << "\n"
		<< "Date: " << date << "\n"
		<< "Time: " << startHour << ":00 - " << endHour << ":00\n"
		<< "Total Cost: $" << totalCost << "\n"
		<< "Payment Status: " << (isPaid ? "Paid" : "Pending") << "\n"
		<< "Payment Method: " << paymentMethod;
	return ss.str();
}