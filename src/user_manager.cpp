#include "../include/user_manager.h"
#include <algorithm>

UserManager::UserManager() {}

bool UserManager::registerUser(const std::string& name, const std::string& email,
	const std::string& password) {

	// Check if email already exists
	if (emailExists(email)) {
		return false;
	}

	// Create and store new user
	users.push_back(std::make_unique<User>(name, email, password));
	return true;
}

bool UserManager::removeUser(const std::string& email) {
	auto it = std::find_if(users.begin(), users.end(),
		[&email](const std::unique_ptr<User>& user) {
			return user->getEmail() == email;
		});

	if (it != users.end()) {
		users.erase(it);
		return true;
	}
	return false;
}

const User* UserManager::loginUser(const std::string& email, const std::string& password) const {
	//admin credential
	if (email == "admin@rental.com" && password == "admin123") {
		static std::unique_ptr<User> adminUser = std::make_unique<User>("Administrator", "admin@rental.com", "admin123");
		return adminUser.get();
	}

	//normal credential
	auto it = std::find_if(users.begin(), users.end(),
		[&email, &password](const std::unique_ptr<User>& user) {
			return user->getEmail() == email && user->validatePassword(password);
		});

	return (it != users.end()) ? it->get() : nullptr;
}

const User* UserManager::getUserByEmail(const std::string& email) const {
	auto it = std::find_if(users.begin(), users.end(),
		[&email](const std::unique_ptr<User>& user) {
			return user->getEmail() == email;
		});

	return (it != users.end()) ? it->get() : nullptr;
}

std::vector<const User*> UserManager::getAllUsers() const {
	std::vector<const User*> result;
	result.reserve(users.size());
	for (const auto& user : users) {
		result.push_back(user.get());
	}
	return result;
}

size_t UserManager::getUserCount() const {
	return users.size();
}

bool UserManager::emailExists(const std::string& email) const {
	return std::any_of(users.begin(), users.end(),
		[&email](const std::unique_ptr<User>& user) {
			return user->getEmail() == email;
		});
}