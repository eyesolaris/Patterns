#include <iostream>
#include <locale>
#include <vector>
#include <memory>
#include <map>

/*interface*/ class ICommand
{
public:
	virtual ~ICommand() = 0;

	virtual void exec() = 0;
};

ICommand::~ICommand() { }

class HelloCommand : public ICommand
{
public:
	virtual void exec() override
	{
		std::cout << "Hello Command!\n";
	}
};

template <typename T>
class ShowVectorCommand : public ICommand
{
public:
	ShowVectorCommand(const std::vector<T>& vec)
		: vectorToShow{ vec }
	{
	}

	virtual void exec() override
	{
		std::cout << "Вывод вектора:\n";
		for (auto& v : vectorToShow)
		{
			std::cout << v << std::endl;
		}
	}

private:
	const std::vector<T>& vectorToShow;
};

template <typename T>
class AddToVectorCommand : public ICommand
{
public:
	AddToVectorCommand(std::vector<T>& vec, T&& object)
		: object{ std::move(object) },
		vector{ vec }
	{
	}

	virtual void exec() override
	{
		std::cout << "Добавляется объект " << object << std::endl;
		vector.push_back(object);
	}

private:
	T object;
	std::vector<T>& vector;
};

class Invoker
{
public:
	void addCommand(std::shared_ptr<ICommand> command)
	{
		commands.push_back(command);
	}

	void invoke()
	{
		for (auto& command : commands)
		{
			command->exec();
		}
	}

private:
	std::vector<std::shared_ptr<ICommand>> commands;
};

int main()
{
	std::locale::global(std::locale(""));

	std::vector<std::string> vec;

	Invoker invoker;
	auto show = std::make_shared<ShowVectorCommand<std::string>>(vec);

	invoker.addCommand(std::make_shared<HelloCommand>());
	invoker.addCommand(show);
	invoker.addCommand(std::make_shared<AddToVectorCommand<std::string>>(vec, "First object"));
	invoker.addCommand(std::make_shared<AddToVectorCommand<std::string>>(vec, "Second phrase"));
	invoker.addCommand(show);
	invoker.invoke();
}