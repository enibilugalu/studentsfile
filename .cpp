#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Student {
	string name;
	string surname;
	string group;
	int age;
};

Student* students = nullptr;
int studentCount = 0;
int capacity = 0;
const string FILE_OF_DATA = "students.txt";

void resizeArray() {
	int newCapacity = (capacity == 0) ? 2 : capacity * 2;
	Student* newArray = new Student[newCapacity];
	for (int i = 0; i < studentCount; i++) {
		newArray[i] = students[i];
	}
	delete[] students;
	students = newArray;
	capacity = newCapacity;
}

void saveToFile() {
	ofstream fout(FILE_OF_DATA);
	if (!fout) {
		cout << "Oshibka pri otkrytii faila dlya zapisi.\n";
		return;
	}
	fout << studentCount << endl;
	for (int i = 0; i < studentCount; i++) {
		fout << students[i].name << " " << students[i].surname << " "
			<< students[i].group << " " << students[i].age << endl;
	}
	fout.close();
	cout << "Dannye sohraneny v fail.\n";
}

void loadFile() {
	ifstream fin(FILE_OF_DATA);
	if (!fin) {
		cout << "Fail ne naiden.\n";
		return;
	}
	fin >> studentCount;
	capacity = studentCount;
	delete[] students;
	students = new Student[capacity];
	for (int i = 0; i < studentCount; i++) {
		fin >> students[i].name >> students[i].surname >> students[i].group >> students[i].age;
	}
	fin.close();
	cout << "Zagruzheno " << studentCount << " studentov iz faila.\n";
}

void showMenu() {
	cout << "\nMenu:\n";
	cout << "1. Pokazat vsekh studentov\n";
	cout << "2. Dobavit studenta\n";
	cout << "3. Redaktirovat studenta\n";
	cout << "4. Udalit studenta\n";
	cout << "5. Vvesti neskol'ko studentov\n";
	cout << "6. Sohranit studentov v fail\n";
	cout << "7. Zagruzit studentov iz faila\n";
	cout << "8. Poisk studenta po familii\n";
	cout << "0. Vyiti\n";
	cout << "Vash vybor: ";
}

void showStudents() {
	if (studentCount == 0) {
		cout << "Spisok studentov pust.\n";
		return;
	}
	for (int i = 0; i < studentCount; i++) {
		cout << i + 1 << ". " << students[i].name << " " << students[i].surname
			<< ", gruppa: " << students[i].group << ", vozrast: " << students[i].age << "\n";
	}
}

bool isNumberRangeCorrect(int number, int left_range, int right_range) {
	return number >= left_range && number <= right_range;
}

bool isNumberNumeric() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
	return true;
}

int inputNumber(string error_message, int left_range, int right_range) {
	int number;
	while (true) {
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range))
			return number;
		else
			cout << error_message;
	}
}

int inputNumber(string error_message) {
	int number;
	while (true) {
		cin >> number;
		if (isNumberNumeric())
			return number;
		else
			cout << error_message;
	}
}

void addStudent() {
	if (studentCount >= capacity) {
		resizeArray();
	}
	Student add;
	cout << "Vvedite imya: ";
	cin >> add.name;
	cout << "Vvedite familiyu: ";
	cin >> add.surname;
	cout << "Vvedite nomer gruppy: ";
	cin >> add.group;
	cout << "Vvedite vozrast (ot 1 do 120): ";
	add.age = inputNumber("Nekorrektnyy vozrast. Povtorite: ", 1, 120);
	students[studentCount++] = add;
}

void changeStudent() {
	if (studentCount == 0) {
		cout << "Net studentov dlya redaktirovaniya.\n";
		return;
	}
	showStudents();
	cout << "Vvedite nomer studenta dlya redaktirovaniya: ";
	int index = inputNumber("Nekorrektnyy nomer. Povtorite: ", 1, studentCount);
	index--;
	cout << "Novoe imya: ";
	cin >> students[index].name;
	cout << "Novaya familiya: ";
	cin >> students[index].surname;
	cout << "Novyy nomer gruppy: ";
	cin >> students[index].group;
	cout << "Novyy vozrast (1–120): ";
	students[index].age = inputNumber("Nekorrektnyy vozrast. Povtorite: ", 1, 120);
}

void deleteStudent() {
	if (studentCount == 0) {
		cout << "Net studentov dlya udaleniya.\n";
		return;
	}
	showStudents();
	cout << "Vvedite nomer studenta dlya udaleniya: ";
	int index = inputNumber("Nekorrektnyy nomer. Povtorite: ", 1, studentCount);
	index--;
	for (int i = index; i < studentCount - 1; i++) {
		students[i] = students[i + 1];
	}
	studentCount--;
	cout << "Student udalen.\n";
}

void inputStudents() {
	cout << "Skol'ko studentov vvesti: ";
	int count = inputNumber("Nekorrektnoe chislo. Povtorite: ", 1, 1000);
	for (int i = 0; i < count; i++) {
		if (studentCount >= capacity) {
			resizeArray();
		}
		Student add;
		cout << "Imya: ";
		cin >> add.name;
		cout << "Familiya: ";
		cin >> add.surname;
		cout << "Nomer gruppy: ";
		cin >> add.group;
		cout << "Vozrast (1–120): ";
		add.age = inputNumber("Nekorrektnyy vozrast. Povtorite: ", 1, 120);
		students[studentCount++] = add;
	}
	cout << count << " studentov dobavleno.\n";
}

void searchBySurname() {
	if (studentCount == 0) {
		cout << "Spisok studentov pust.\n";
		return;
	}
	cout << "Vvedite familiyu dlya poiska: ";
	string targetSurname;
	cin >> targetSurname;
	bool found = false;
	for (int i = 0; i < studentCount; i++) {
		if (students[i].surname == targetSurname) {
			cout << i + 1 << ". " << students[i].name << " " << students[i].surname << ", gruppa: " << students[i].group << ", vozrast: " << students[i].age << "\n";
			found = true;
		}
	}
	if (!found) {
		cout << "Student s takoy familiyey ne naiden.\n";
	}
}

int main() {
	loadFile();
	while (true) {
		showMenu();
		int choice = inputNumber("Nekorrektnyy vybor. Povtorite: ", 0, 8);
		switch (choice) {
		case 1: showStudents(); break;
		case 2: addStudent(); break;
		case 3: changeStudent(); break;
		case 4: deleteStudent(); break;
		case 5: inputStudents(); break;
		case 6: saveToFile(); break;
		case 7: loadFile(); break;
		case 8: searchBySurname(); break;
		case 0:
			cout << "Vyhod iz programmy.\n";
			delete[] students;
			return 0;
		}
	}
}
