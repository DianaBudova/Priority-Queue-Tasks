#pragma once
bool LessOrEqual(Task date);
bool Equal(Task date);

class TaskController
{
private:
	PriorityQueue<Task> queue;
	void ShowRefactoring(const Task* result, const size_t& count)
	{
		for (size_t i = 0; i < count; i++)
			std::cout << "[ " << result[i] << "]" << std::endl;
		std::cout << std::endl;
	}
public:
	void Add(const Task& current, unsigned int d, unsigned int m, unsigned int y, std::string name, std::string description)
	{
		Task temp(d, m, y, name, description);
		queue.Add(temp, temp.DaysLeft(current));
	}
	void Add(const Task& current)
	{
		Task temp;
		std::string name, description;
		std::cout << "name: ";
		std::cin >> name;
		temp.SetName(name);
		std::cout << "description: ";
		std::cin >> description;
		temp.SetDescription(description);
		unsigned int d, m, y;
		std::cout << "day: ";
		std::cin >> d;
		temp.GetDeadline().SetDay(d);
		std::cout << "month: ";
		std::cin >> m;
		temp.GetDeadline().SetMonth(m);
		std::cout << "year: ";
		std::cin >> y;
		temp.GetDeadline().SetYear(y);
		queue.Add(temp, temp.DaysLeft(current));
	}
	void Remove(Task& obj)
	{
		queue.Remove(obj);
	}
	void Edit(const Task& current, Task& obj)
	{
		queue.Remove(obj);
		Add(current);
	}
	void ShowAll()
	{
		std::cout << queue << std::endl;
	}
	void ShowDate(const Task& date)
	{
		Task* result = nullptr;
		size_t count = queue.All(result, Equal);
		ShowRefactoring(result, count);
	}
	void ShowAllToDate(const Task& date)
	{
		Task* result = nullptr;
		size_t count = queue.All(result, LessOrEqual);
		ShowRefactoring(result, count);
	}
	void ShowToday(const Task& date)
	{
		Task* result = nullptr;
		size_t count = queue.All(result, Equal);
		std::cout << "[" << std::setw(2) << result[0] << "]" << std::endl;
		std::cout << std::endl;
	}
};

bool LessOrEqual(Task date)
{
	Date toDate(1, 9, 2022);
	return (toDate.GetDay() <= date.GetDeadline().GetDay() && toDate.GetMonth() <= date.GetDeadline().GetMonth() && toDate.GetYear() <= date.GetDeadline().GetYear());
}
bool Equal(Task date)
{
	Date today(29, 8, 2022);
	return (today.GetDay() == date.GetDeadline().GetDay() && today.GetMonth() == date.GetDeadline().GetMonth() && today.GetYear() == date.GetDeadline().GetYear());
}