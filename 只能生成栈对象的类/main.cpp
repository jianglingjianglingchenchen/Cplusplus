#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Student
{
public:
	Student(std::string name = "", int num = 0)
		:name(name), num(num) {
	}

	Student(const Student& rhs)
		:name(rhs.name), num(rhs.num) {
		std::cout << "copied" << "\n";
	}
private:
	static void* operator new(size_t size);
	static void operator delete(void*);
	std::string name;
	int num;
};

int main(void) {
	Student std1;
	//Student* std2 = new Student;
	return 0;
}

