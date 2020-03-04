#include <iostream>
#include <string>
#include <memory>
#include <locale>

using schar = signed char;

// При переопределении виртуальных функций-членов
// вызывать функции-члены базового класса!
class Device
{
public:
	virtual ~Device() = 0;

	Device(schar defaultVol)
		: volume{ defaultVol }
	{
	}

	Device() = delete;

	virtual void setVolume(schar volume)
	{
		this->volume = volume;
	}

	virtual schar getVolume() const
	{
		return volume;
	}

private:
	schar volume;
};

class TV : public Device
{
public:
	TV(schar defaultVol)
		: Device(defaultVol)
	{
	}

	virtual void setVolume(schar volume) override
	{
		if (volume > 100)
		{
			volume = 100;
		}
		else if (volume < 0)
		{
			volume = 0;
		}
		Device::setVolume(volume);
		showAtScreen("Громкость: " + std::to_string(volume));
	}

	void showAtScreen(const std::string& str)
	{
		std::cout << str << std::endl;
	}
};

Device::~Device() { }

class RemoteController
{
public:
	virtual ~RemoteController() = 0;

	RemoteController(std::shared_ptr<Device> device)
		: dev{ device }
	{
	}

	virtual void up()
	{
		auto prevVolume = dev->getVolume();
		dev->setVolume(prevVolume + 1);
	}

	virtual void down()
	{
		auto prevVolume = dev->getVolume();
		dev->setVolume(prevVolume - 1);
	}

protected:
	std::shared_ptr<Device> dev;
};

class RemoteControllerWithMute : public RemoteController
{
public:
	using RemoteController::RemoteController;

	void mute()
	{
		if (!muted)
		{
			prevState = dev->getVolume();
			dev->setVolume(0);
			muted = true;
		}
	}

	void unmute()
	{
		if (muted)
		{
			dev->setVolume(prevState);
			muted = false;
		}
	}

private:
	schar prevState;
	bool muted = false;
};

RemoteController::~RemoteController() { }

int main()
{
	std::locale::global(std::locale(""));
	std::shared_ptr<Device> dev = std::make_shared<TV>(0);
	std::unique_ptr<RemoteController> controller = std::make_unique<RemoteControllerWithMute>(dev);
	controller->up();
	controller->up();
	controller->down();
	RemoteControllerWithMute* withMute = dynamic_cast<RemoteControllerWithMute*>(controller.get());
	withMute->mute();
	withMute->mute();
	withMute->unmute();
}