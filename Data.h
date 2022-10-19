#pragma once
#include <iomanip>
#include <ctime>
class Date
{
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date() : Date(0, 0, 0)
	{}
	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	void SetDay(int d)
	{
		this->day = d;
	}
	int GetDay() const
	{
		return day;
	}
	void SetMonth(int m)
	{
		this->month = m;
	}
	int GetMonth() const
	{
		return month;
	}
	void SetYear(int y)
	{
		this->year = y;
	}
	int GetYear() const
	{
		return year;
	}
};
class Task
{
private:
	Date deadline;
	std::string name;
	std::string description;
public:
	Task() : Task(0, 0, 0, "", "")
	{}
	Task(int d, int m, int y) : Task(d, m, y, "", "")
	{}
	Task(int d, int m, int y, std::string name, std::string description)
	{
		this->deadline.SetDay(d);
		this->deadline.SetMonth(m);
		this->deadline.SetYear(y);
		this->name = name;
		this->description = description;
	}
	unsigned int DaysLeft(const Task& date) const
	{
		const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		long int n1 = date.deadline.GetYear() * 365 + date.deadline.GetDay();
		for (size_t i = 0; i < date.deadline.GetMonth() - 1; i++)
			n1 += monthDays[i];
		long int n2 = deadline.GetYear() * 365 + deadline.GetDay();
		for (size_t i = 0; i < deadline.GetMonth() - 1; i++)
			n2 += monthDays[i];
		return n2 - n1;
	}
	Date& GetDeadline()
	{
		return this->deadline;
	}
	void SetName(std::string name)
	{
		this->name = name;
	}
	std::string GetName() const
	{
		return this->name;
	}
	void SetDescription(std::string description)
	{
		this->description = description;
	}
	std::string GetDescription() const
	{
		return this->description;
	}
	friend std::ostream& operator<<(std::ostream& out, const Task& obj)
	{
		tm now;
		time_t timeObject = time(0);
		localtime_s(&now, &timeObject);
		Task temp((int)now.tm_mday, (int)now.tm_mon + 1, (int)now.tm_year + 1900);
		out << obj.DaysLeft(temp)
			<< ":" << std::setw(2) << obj.deadline.GetDay() << "/" << std::setw(2) << obj.deadline.GetMonth() << "/" << obj.deadline.GetYear() << ":"
			<< obj.name << ":"
			<< obj.description;
		return out;
	}
	bool operator==(const Task& lho)
	{
		if (this->deadline.GetDay() == lho.deadline.GetDay() &&
			this->deadline.GetMonth() == lho.deadline.GetMonth() &&
			this->deadline.GetYear() == lho.deadline.GetYear() &&
			this->name == name &&
			this->description == description)
			return true;
		return false;
	}
};