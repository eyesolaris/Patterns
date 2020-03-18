#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class Colleague;

class Mediator
{
public:
	virtual ~Mediator() = 0;
	virtual void finishedWork(Colleague* colleague) = 0;
};

class Colleague
{
public:
	Colleague(Mediator* mediator)
		: mediator{ mediator }
	{
	}

	void finishedWork()
	{
		mediator->finishedWork(this);
	}

private:
	Mediator* mediator;
};

Mediator::~Mediator() { }

class Architect : public Colleague
{
public:
	void architect()
	{
		std::this_thread::sleep_for(1s);
		std::cout << "Проектировщик создал архитектуру. Пора писать код!\n";
		finishedWork();
	}
};

class Developer : public Colleague
{
public:
	void develop()
	{
		std::this_thread::sleep_for(1s);
		std::cout << "Разработчик написал код. Пора отправлять на тестирование\n";
		finishedWork();
	}
};

class Tester : public Colleague
{
public:
	void test()
	{
		std::this_thread::sleep_for(1s);
		std::cout << "Тестировщик закончил тестирование.\n";
		finishedWork();
	}
};

class SoftwareDevelopmentMediator : public Mediator
{
public:
	SoftwareDevelopmentMediator()
		: architect{ this },
		dev{ this },
		tester{ this }
	{
	}

	virtual void finishedWork(Colleague* colleague) override
	{
		if (colleague == &architect)
		{
			dev.develop();
		}
		else if (colleague == &dev)
		{
			tester.test();
		}
		else if (colleague == &tester)
		{
			std::this_thread::sleep_for(1s);
			std::cout << "Разработка ПО завершена. Получите отличный продукт!\n";
		}
		else
		{
			std::cout << "Данный работник не участвует в разработке ПО\n";
		}
	}

	void startDevelopment()
	{
		architect.architect();
	}

private:
	Architect architect;
	Developer dev;
	Tester tester;
};

int main()
{
	std::locale::global(std::locale(""));
	SoftwareDevelopmentMediator mediator;
	mediator.startDevelopment();
	std::system("pause");
}

/*class AddressAndName
{
public:
	AddressAndName(const std::string& name, const std::string& address)
		: name{ name },
		address{ address }
	{
	}

	const std::string& getName() const { return name; }
	const std::string& getAddress() const { return address; }

	std::string as_string() const
	{
		return "Имя: " + name + ", адрес: " + address;
	}

private:
	std::string name;
	std::string address;
};

class LetterWasMoved : public std::runtime_error
{
public:
	LetterWasMoved()
		: std::runtime_error{ "Невозможно получить доступ к письму, переданному в другое место" }
	{
	}
};

class Letter
{
public:
	Letter(AddressAndName addressee, AddressAndName sender, std::string content)
		: addressee{ addressee },
		sender{ sender },
		content{ content }
	{
	}

	// Заставляем пользователей класса использовать семантику перемещения
	// как симуляцию передачи письма из рук в руки.
	// После перемещения объект больше не принадлежит передававшему
	Letter(const Letter&) = delete;

	// Запрет брать указатель на объект
	Letter* operator&() = delete;

	Letter& operator=(Letter&& other)
	{
		other.checkIsMoved();
		addressee = std::move(other.addressee);
		sender = std::move(other.sender);
		content = std::move(other.content);
		other.isMovedVal = true;
		isMovedVal = false;
		return *this;
	}

	Letter(Letter&& other)
		: addressee{ (other.checkIsMoved(), std::move(other.addressee)) },
		sender{ std::move(other.sender) },
		content{ std::move(other.content) }
	{
		other.isMovedVal = true;
	}

	const AddressAndName& getAddressee() const
	{
		checkIsMoved();
		return addressee;
	}

	const AddressAndName& getSender() const
	{
		checkIsMoved();
		return sender;
	}

	const std::string& getContent() const
	{
		checkIsMoved();
		return content;
	}

	bool isMoved() const
	{
		return isMovedVal;
	}

private:
	void checkIsMoved() const
	{
		if (isMovedVal)
		{
			throw LetterWasMoved();
		}
	}

	AddressAndName addressee, sender;
	std::string content;
	bool isMovedVal = false;
};

class AddresseeException : public std::runtime_error
{
public:
	AddresseeException(const std::string& message, Letter&& letter)
		: std::runtime_error{ message },
		letter{ std::move(letter) }
	{
	}

	const AddressAndName& getAddressee() const { return letter.getAddressee(); }
	Letter takeLetterBack() { return std::move(letter); }
	const Letter& showLetter() const { return letter; }

private:
	Letter letter;
};

class AddresseeNotFound : public AddresseeException
{
public:
	AddresseeNotFound(Letter&& letter)
		: AddresseeException{ "Не найден адресат. " + letter.getAddressee().as_string(), std::move(letter) }
	{
	}
};

class AddresseeDidntProceessedLetter : public AddresseeException
{
public:
	AddresseeDidntProceessedLetter(Letter&& letter)
		: AddresseeException{ "Адресат " + letter.getAddressee().as_string() + " не смог обработать сообщение", std::move(letter) }
	{
	}
};

class Subscriber;

// Почтовая служба
class MailService
{
public:
	MailService()
	{
	}

	void registerSubscriber(std::shared_ptr<Subscriber> subscriber, const std::string& address)
	{
		subscribers.insert({ address, subscriber });
	}

	void sendLetter(Letter letter);

private:
	// Возможно проживание нескольких человек по одному адресу
	std::multimap<std::string /*address*//*, std::shared_ptr<Subscriber>> subscribers;
};

/*abstract*//* class Subscriber
{
public:
	virtual ~Subscriber() = 0;

	const std::string& getName() const
	{
		return name;
	}

	virtual void receiveLetter(Letter letter) = 0;

	void sendLetter(Letter letter)
	{
		service->sendLetter(std::move(letter));
	}

	void changeMailService(MailService service)
	{
		this->service = &service;
	}

protected:
	Subscriber(const std::string& name, MailService& service)
		: name{ name },
		service{ &service }
	{
	}

private:
	std::string name;
	MailService* service;
};

Subscriber::~Subscriber() { }

void MailService::sendLetter(Letter letter)
{
	std::cout << "В почтовое отделение пришло письмо от \"" << letter.getSender().as_string()
		<< "\" для \"" << letter.getAddressee().as_string() << '\"' << std::endl;
	auto subscriberIter = subscribers.find(letter.getAddressee().getAddress());
	if (subscriberIter == subscribers.end())
	{
		throw AddresseeNotFound{ std::move(letter) };
	}
	for (auto iter = subscriberIter; iter != subscribers.end(); iter++)
	{
		auto& somebody = iter->second;
		if (somebody->getName() == letter.getAddressee().getName())
		{
			try
			{
				somebody->receiveLetter(std::move(letter));
				return;
			}
			catch (AddresseeDidntProceessedLetter& ex)
			{
				std::cout << "Адресат c адресом: \"" << ex.showLetter().getAddressee().as_string() << "\" не смог обработать сообщение" << std::endl;
				throw;
			}
		}
	}
	throw AddresseeNotFound(std::move(letter));
}

// Подписчики с облачным хранилищем. Сохраняют свои письма в облаке
class SubscriberWithCloudStorage : public Subscriber
{
public:
	SubscriberWithCloudStorage(const std::string& name, MailService& service)
		: Subscriber{ name, service }
	{
	}

	virtual void receiveLetter(Letter letter) override
	{
		std::cout << getName() << " получил письмо по почте, отсканировал и отправил в своё облако.\nСодержание письма:\n\"" << letter.getContent() << '\"' << std::endl;
	}
};

// Консервативные подписчики, не пользующиеся облаком
class ConservativeSubscriber : public Subscriber
{
public:
	ConservativeSubscriber(const std::string& name, MailService& service)
		: Subscriber{ name, service }
	{
	}

	virtual void receiveLetter(Letter letter) override
	{
		std::cout << getName() << " получил письмо по почте, но не оцифровал его. Не удаётся отобразить содержание..." << std::endl;
	}
};

// Подписчики, которые не хотят получать письма, а только отправлять
class RejectSubscriber : public Subscriber
{
public:
	RejectSubscriber(const std::string& name, MailService& service)
		: Subscriber{ name, service }
	{
	}

	virtual void receiveLetter(Letter letter) override
	{
		std::cout << "Клиент " << getName() << " возмутился: \"Хоть я и зарегистрировался на почте, но получать письма не хочу! Только отправлять! Возвращаю письмо назад.\"" << std::endl;
		throw AddresseeDidntProceessedLetter(std::move(letter));
	}
};

int main()
{
	std::locale::global(std::locale(""));

	// Создаём почтовую службу
	MailService mailService;

	constexpr char borovaya7[] = "ул. Боровая, д. 7";
	constexpr char borovaya8[] = "ул. Боровая, д. 8";

	constexpr char peterName[] = "Петров Пётр Петрович";
	constexpr char ivanName[] = "Иванов Иван Иванович";
	constexpr char sidrName[] = "Сидоров Сидр Сидорович";

	AddressAndName peterAddress{ peterName, borovaya7 };
	AddressAndName ivanAddress{ ivanName, borovaya7 };
	AddressAndName sidrAddress{ sidrName, borovaya8 };

	//Создаём пользователей почты и регистрируем их на почте
	std::shared_ptr<Subscriber> peter = std::make_shared<SubscriberWithCloudStorage>(peterName, mailService);
	mailService.registerSubscriber(peter, peterAddress.getAddress());
	std::shared_ptr<Subscriber> ivan = std::make_shared<ConservativeSubscriber>(ivanName, mailService);
	mailService.registerSubscriber(ivan, ivanAddress.getAddress());
	std::shared_ptr<Subscriber> sidr = std::make_shared<RejectSubscriber>(sidrName, mailService);
	mailService.registerSubscriber(sidr, sidrAddress.getAddress());

	// Иван шлёт письмо Петру
	Letter peterLetter{ peterAddress, ivanAddress, "Привет, Пётр! От Ивана." };
	peter->sendLetter(std::move(peterLetter));

	std::cout << std::endl;

	// Иван шлёт письмо Сидру
	Letter sidrLetter{ sidrAddress, ivanAddress, "Привет, Сидр! Жаль, что ты не получишь сообщение" };
	try
	{
		peter->sendLetter(std::move(sidrLetter));
	}
	catch (AddresseeDidntProceessedLetter& ex)
	{
		sidrLetter = std::move(ex.takeLetterBack());
		std::cout << "Сидр отправил письмо обратно.\nСодежание письма: " << sidrLetter.getContent() << std::endl;
	}

	std::cout << std::endl;

	// Сидр шлёт письмо Ивану
	Letter ivanLetter{ ivanAddress, sidrAddress, "Привет, Иван! Давно не виделись!" };
	sidr->sendLetter(std::move(ivanLetter));

	std::cout << std::endl;

	std::system("pause");
	/*std::vector<std::shared_ptr<Subscriber>> subscribers;
	subscribers.push_back(peter);
	subscribers.push_back(ivan);
	subscribers.push_back(sidr);*//*
}*/