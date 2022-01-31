#include<iostream>
#include<exception>

struct Node
{
	int day, month, year;
	std::string text;
	Node* next;
	Node* prev;
	Node(int day, int month, int year, std::string text, Node* next, Node* prev) : day(day), month(month), year(year), text(text), next(next), prev(prev) {}
};

class OrganizerExcept : std::exception
{
private:
	const char* error;
public:
	OrganizerExcept(const char* error) : error(error) {}
	const char* what() const noexcept override
	{
		return error;
	}
};

class Organizer
{
private:
	Node* head;
public:
	Organizer()
	{
		this->head = nullptr;
	}
	void add(int day, int month, int year, std::string text)
	{
		if (day > 31 || month > 12 || day < 1 || month < 1) throw OrganizerExcept("wrong date");
		if (this->head == nullptr)
		{
			this->head = new Node(day, month, year, text, nullptr, nullptr);
			return;
		}
		Node* iter = this->head;
		while (iter->next != nullptr)
		{
			iter = iter->next;
		}
		iter->next = new Node(day, month, year, text, nullptr, iter);
	}
};

int main()
{
	Organizer org;
	try
	{
		org.add(0, 123, 42387, "text");
	}
	catch (OrganizerExcept except)
	{
		std::cout << except.what() << "\n";
	}
}