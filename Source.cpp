#include <iostream>
#include "PriorityQueue.h"
#include "Data.h"
#include "Controller.h"

int main()
{
	Task current(24, 8, 2022);
	TaskController controller1;

	controller1.Add(current, 29, 8, 2022, "Eat", "InKitchen");
	controller1.Add(current, 1, 9, 2022, "Go", "ToSchool");
	controller1.Add(current, 27, 8, 2022, "Clean", "CleanHome");

	controller1.ShowAll();
	
	Task date(29, 8, 2022);
	controller1.ShowDate(date);

	controller1.ShowAllToDate(date);

	controller1.ShowToday(date);

}