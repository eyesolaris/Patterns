#include <iostream>
#include <cstdint>
#include <string>
#include <map>
#include <memory>
#include <sstream>

/*interface*/ class BreadProduct
{
public:
	virtual ~BreadProduct() = 0;

	virtual std::int32_t weight() const = 0;
	virtual std::wstring toString() const = 0;
};

BreadProduct::~BreadProduct() { }

class Pizza final : public BreadProduct
{
public:
	Pizza(std::int32_t weight, std::int32_t diameter)
		: _weight{ weight }, diameter{ diameter }
	{
	}

	virtual std::int32_t weight() const override final
	{
		return _weight;
	}

	virtual std::wstring toString() const override final
	{
		return L"Pizza, diameter: " + std::to_wstring(getDiameter())
			+ L", weight: " + std::to_wstring(weight());
	}

	std::int32_t getDiameter() const { return diameter; }

private:
	std::int32_t _weight;
	std::int32_t diameter;
};

enum class BreadType
{
	Black,
	Wheed,
};

class Bread final : public BreadProduct
{
public:
	Bread(BreadType type)
		: type{ type }
	{
	}

	virtual std::int32_t weight() const override final
	{
		return 1;
	}

	virtual std::wstring toString() const override final
	{
		std::wstring ret;
		switch (type)
		{
		case BreadType::Black:
			ret = L"Black";
			break;
		case BreadType::Wheed:
			ret = L"Wheed";
			break;
		}
		ret += L" bread, weight: " + std::to_wstring(weight());
		return ret;
	}

	BreadType getBreadType() const
	{
		return type;
	}

private:
	BreadType type;
};

/*interface*/ class BreadCreator
{
public:
	virtual ~BreadCreator() = 0;
	virtual std::shared_ptr<BreadProduct> create(const std::map<std::wstring, std::wstring>& args) const = 0;
};

BreadCreator::~BreadCreator() { }

class BreadConcreteCreator final : public BreadCreator
{
public:
	BreadConcreteCreator() { }

	virtual std::shared_ptr<BreadProduct> create(const std::map<std::wstring, std::wstring>& args) const override final
	{
		auto type = args.at(L"BreadType");
		BreadType type2;
		if (type == L"Wheed")
		{
			type2 = BreadType::Wheed;
		}
		else if (type == L"Black")
		{
			type2 = BreadType::Black;
		}
		return std::make_shared<Bread>(type2);
	}
};

class PizzaCreator final : public BreadCreator
{
public:
	PizzaCreator() { }

	virtual std::shared_ptr<BreadProduct> create(const std::map<std::wstring, std::wstring>& args) const override final
	{
		auto weight = args.at(L"Weight");
		std::wstringstream stream{ weight };
		std::int32_t weightNum;
		stream >> weightNum;
		auto diameter = args.at(L"Diameter");
		stream = std::wstringstream{ diameter };
		std::int32_t diameterNum;
		stream >> diameterNum;
		return std::make_shared<Pizza>(weightNum, diameterNum);
	}
};

int main()
{
	std::unique_ptr<BreadCreator> creator{ std::make_unique<BreadConcreteCreator>() };
	auto bread = creator->create({ { L"BreadType", L"Wheed" } });
	std::wcout << bread->toString();

	std::wcout << std::endl;

	creator = std::make_unique<PizzaCreator>();
	bread = creator->create({ { L"Diameter", L"32" }, { L"Weight", L"7" } });
	std::wcout << bread->toString();
}