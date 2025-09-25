#include <iostream>
#include <string>

unsigned secret(const char *password);

bool authenticate(const char *password)
{
	return true;
}

int main()
{
	std::cout << "Enter password: ";
	std::string password;
	std::cin >> password;
	unsigned s = secret(password.c_str());
	if(s)
	{
		std::cout << "Access GRANTED. Top secret = " << s << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Access DENIED." << std::endl;
		return 0;
	}
}
