#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <functional>

class Pass
{
public:
	Pass(std::string series, std::string number)
		: series{ series },
		number{ number }
	{
	}

	const std::string& getSeries() const
	{
		return series;
	}

	const std::string& getNumber() const
	{
		return number;
	}

private:
	std::string series;
	std::string number;
};

class PassValidatorContext
{
public:
	PassValidatorContext() = default;

	PassValidatorContext(const std::string& problem)
	{
		addProblem(problem);
	}

	void addProblemAtBegin(const std::string& problem)
	{
		problems.insert(std::begin(problems), problem);
	}

	void addProblem(const std::string& problem)
	{
		problems.push_back(problem);
	}

	const std::vector<std::string>& getProblems() const
	{
		return problems;
	}

	bool isEmpty() const { return problems.empty(); }

private:
	std::vector<std::string> problems;
};

/*interface*/ class IPassValidator
{
public:
	virtual ~IPassValidator() = 0;

	virtual PassValidatorContext validate(const Pass& pass) const = 0;
	virtual void setNext(std::shared_ptr<IPassValidator>) = 0;
};

class AbstractPassValidator : public IPassValidator
{
public:
	virtual PassValidatorContext validate(const Pass& pass) const override
	{
		PassValidatorContext ctx{};
		if (next != nullptr)
		{
			ctx = next->validate(pass);
		}
		auto problem = actualValidate(pass);
		if (problem != nullptr)
		{
			ctx.addProblemAtBegin(*problem);
		}
		return std::move(ctx);
	}

	virtual void setNext(std::shared_ptr<IPassValidator> next) override
	{
		this->next = next;
	}

protected:
	AbstractPassValidator() = default;

	virtual std::unique_ptr<std::string> actualValidate(const Pass& pass) const = 0;

private:
	std::shared_ptr<IPassValidator> next;
};

IPassValidator::~IPassValidator() { }

class MaskValidator : public AbstractPassValidator
{
public:
	MaskValidator(const std::string& mask, std::function<const std::string&(const Pass&)> func)
		: regex{ mask },
		func{ func }
	{
		if (!func)
		{
			throw 0;
		}
	}

protected:
	virtual std::unique_ptr<std::string> actualValidate(const Pass& pass) const override
	{
		auto str = func(pass);
		if (!std::regex_match(str, regex))
		{
			return std::make_unique<std::string>("Invalid number");
		}
		return nullptr;
	}

private:
	std::regex regex;
	std::function<const std::string&(const Pass&)> func;
};

void showContext(const PassValidatorContext& ctx)
{
	std::cout << "Validation finished.\n";
	for (auto& problem : ctx.getProblems())
	{
		std::cout << problem << std::endl;
	}
}

int main()
{
	std::shared_ptr<IPassValidator> validator
		= std::make_shared<MaskValidator>("^[0-9]{6}$",
			[](const Pass& pass) -> decltype(auto) {
				return pass.getNumber(); 
			});
	validator->setNext(std::make_shared<MaskValidator>("^[0-9]{4}$",
		[](const Pass& pass) -> decltype(auto) {
			return pass.getSeries();
		}));

	Pass pass{ "1234", "123456" };
	auto ctx = validator->validate(pass);
	showContext(ctx);
	pass = Pass{ "dfgl", "43ghg" };
	ctx = validator->validate(pass);
	showContext(ctx);
}