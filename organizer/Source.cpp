#include<iostream>
#include<exception>
#include<conio.h>
struct Node
{
	int day, month, year;
	std::string text;
	Node* next;
	Node* prev;
	Node(int day, int month, int year, std::string text, Node* next, Node* prev) : day(day), month(month), year(year), text(text), next(next), prev(prev) {}
};

class OrganizerExcept : public std::exception
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

	Node* find(int day, int month, int year)
	{
		if (this->head == nullptr) throw OrganizerExcept("no elements\n");
		Node* iter = this->head;
		while (iter != nullptr)
		{
			if (iter->day == day && iter->month == month && iter->year == year) break;
			iter = iter->next;
		}
		if (iter == nullptr) throw OrganizerExcept("no such date\n");
		return iter;
	}

public:
	Organizer()
	{
		this->head = nullptr;
	}
	void add(int day, int month, int year, std::string text)
	{
		if (day > 31 || month > 12 || day < 1 || month < 1) throw OrganizerExcept("wrong date\n");
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
	void deleteElement(int day, int month, int year)
	{
		Node* toDelete = find(day, month, year);

		toDelete->prev->next = toDelete->next;
		if (toDelete->next != nullptr) toDelete->next->prev = toDelete->prev;
		delete toDelete;
	}
	void redact(int day, int month, int year, std::string str)
	{
		Node* toRedact = this->find(day, month, year);
		toRedact->text = str;
	}
	void print()
	{
		if (this->head == nullptr) throw OrganizerExcept("no elements\n");
		Node* iter = this->head;
		while (iter != nullptr)
		{
			std::cout << iter->day << "." << iter->month << "." << iter->year << "\t" << iter->text << "\n";
			iter = iter->next;
		}
	}
};

int main()
{
	Organizer org;
	while (true)
	{
		try
		{
			system("cls");
			std::cout << "1 - add\n"
				<< "2 - delete\n"
				<< "3 - redact\n"
				<< "4 - print\n"
				<< "Esc - exit\n";
			switch (_getch())
			{
				std::cin.ignore();
			case '1':
			{
				std::cout << "enter date and text:\n";
				int d, m, y;
				std::string str;
				std::cin >> d >> m >> y;
				std::cin >> str;

				org.add(d, m, y, str);
				break;
			}
			case '2':
			{
				std::cout << "enter date:\n";
				int d, m, y;
				std::cin >> d >> m >> y;
				org.deleteElement(d, m, y);
				break;
			}
			case '3':
			{
				std::cout << "enter date:\n";
				int d, m, y;
				std::cin >> d >> m >> y;
				std::cout << "enter new text:\n";
				std::string str;
				std::cin >> str;
				org.redact(d, m, y, str);
				break;
			}
			case '4':
				org.print();
				break;

			case 27: return 0;
			}
		}
		catch (std::exception& error)
		{
			std::cout << error.what();
		}
		system("pause");
	}
}