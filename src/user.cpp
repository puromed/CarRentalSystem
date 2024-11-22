#include "../include/user.h"
#include <regex>

User::User(const std::string& name, const std::string& email, const std::string& password, bool isAdmin)
	: name(name), email(email), password(password), isAdmin(isAdmin) {}

std::string User::getName() const {
	return name;
}

std::string User::getEmail() const {
	return email;
}

bool User::getIsAdmin() const {
	return isAdmin;
}

bool User::validatePassword(const std::string& inputPassword) const {
	return password == inputPassword;
}

bool User::validateEmail() const {
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, pattern);

}