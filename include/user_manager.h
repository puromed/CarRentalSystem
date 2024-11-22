#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "user.h"

class UserManager {
private:
	std::vector<std::unique_ptr<User>> users;

public:
	// Constructor
	UserManager();

		// User management methods
		bool registerUser(const std::string& name, const std::string& email,
			const std::string& password);
		bool removeUser(const std::string& email);

		// User authentication

		const User* loginUser(const std::string& email, const std::string& password) const;

		// User retrieval methods
		
		const User* getUserByEmail(const std::string& email) const;
		std::vector<const User*> getAllUsers() const;

		//Utility methods

		size_t getUserCount() const;
		bool emailExists(const std::string& email) const;
};

#endif //USER_MANAGER_H