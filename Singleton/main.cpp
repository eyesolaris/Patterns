#include <iostream>
#include <string>
#include <map>
#include <any>
#include <stdexcept>

std::map<int, std::any> database;

class Database
{
public:
	static Database DatabaseInstance;

	std::any* GetRecord(int id)
	{
		auto found = database.find(id);
		if (found != std::end(database))
		{
			return &found->second;
		}
		else
		{
			return nullptr;
		}
	}

	std::any& PutRecord(int id, std::any data)
	{
		auto found = database.find(id);
		if (found != std::end(database))
		{
			std::cerr << "¬нимание: данные уже записаны в €чейке " << id << " \n";
			return found->second;
		}
		return database[id] = data;
	}

private:
	Database& operator=(const Database&) = default;
	Database& operator=(Database&&) = default;

	Database(const Database&) = delete;
	Database(Database&&) = delete;

	Database()
	{
	}

	static void connectionError()
	{
		std::cerr << "Database connection failed\n";
	}
};

Database Database::DatabaseInstance;


int main()
{
	std::any& data = Database::DatabaseInstance.PutRecord(0, 100);
	std::cout << std::any_cast<int>(data) << std::endl;
}