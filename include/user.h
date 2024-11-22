#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
	std::string name;
	std::string email;
	std::string password;
	bool isAdmin;

public:
	//constructor
	User(const std::string& name, const std::string& email, const std::string& password, bool isAdmin = false);

	//Getters
	std::string getName() const;
	std::string getEmail() const;
	bool getIsAdmin() const;

	//methods
	bool validatePassword(const std::string& inputPassword) const;
	bool validateEmail() const;
};

#endif // User_H