#pragma once
#include <iostream>

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class FireCommand : public Command
{
public:
	void Execute() override
	{
		std::cout << "yep" << std::endl;
	};
};