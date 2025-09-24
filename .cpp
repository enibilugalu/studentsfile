#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Struktura dlya predstavleniya studenta
struct Student {
	string name;     // Imya studenta
	string surname;  // Familiya studenta
	int age;         // Vozrast studenta
};

// Global'nye peremennye
Student* students = nullptr; // Ukazatel' na massiv studentov
int studentCount = 0;        // Tekushchee kolichestvo studentov
int capacity = 0;            // Maksimal'naya vmeschaemost' massiva
const string FILE_OF_DATA = "students.txt"; // Imya faila dlya hraneniya dannykh

// Uvelichenie razmera massiva pri neobkhodimosti
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

// Sohranenie dannykh v fail
void saveToFile() {
	ofstream fout(FILE_OF_DATA);
	if (!fout) {
		cout << "Oshibka pri otkrytii faila dlya zapisi.\n";
		return;
	}
	fout << studentCount << endl;
	for (int i = 0; i < studentCount; i++) {
		fout << students[i].name << " "
			<< students[i].surname << " "
			<< students[i].age << endl;
	}
	fout.close();
	cout << "Dannye sohraneny v fail.\n";
}

// Zagruzka dannykh iz faila
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
		fin >> students[i].name >> students[i].surname >> students[i].age;
	}
	fin.close();
	cout << "Zagruzheno " << studentCount << " studentov iz faila.\n";
}

// Vyvod menyu v konsol
void showMenu() {
	cout << "\nMenu:\n";
	cout << "1. Pokazat vsekh studentov\n";
	cout << "2. Dobavit studenta\n";
	cout << "3. Redaktirovat studenta\n";
	cout << "4. Udalit studenta\n";
	cout << "5. Vvesti neskol'ko studentov\n";
	cout << "6. Sohranit studentov v fail\n";
	cout << "7. Zagruzit studentov iz faila\n";
	cout << "0. Vyiti\n";
	cout << "Vash vybor: ";
}

// Vyvod spiska studentov
void showStudents() {
	if (studentCount == 0) {
		cout << "Spisok studentov pust.\n";
		return;
	}
	for (int i = 0; i < studentCount; i++) {
		cout << i + 1 << ". " << students[i].name << " "
			<< students[i].surname << ", vozrast: " << students[i].age << "\n";
	}
}

// Dobavlenie odnogo studenta
void addStudent() {
	if (studentCount >= capacity) {
		resizeArray();
	}
	Student add;
	cout << "Vvedite imya: ";
	cin >> add.name;
	cout << "Vvedite familiyu: ";
	cin >> add.surname;
	cout << "Vvedite vozrast: ";
	cin >> add.age;
	students[studentCount++] = add;
	cout << "Student dobavlen.\n";
}

// Redaktirovanie dannykh studenta
void changeStudent() {
	if (studentCount == 0) {
		cout << "Net studentov dlya redaktirovaniya.\n";
		return;
	}
	showStudents();
	cout << "Vvedite nomer studenta dlya redaktirovaniya: ";
	int index;
	cin >> index;
	if (index <= 0 || index > studentCount) {
		cout << "Nekorrektnyy nomer.\n";
		return;
	}
	index--;
	cout << "Novoe imya: ";
	cin >> students[index].name;
	cout << "Novaya familiya: ";
	cin >> students[index].surname;
	cout << "Novyy vozrast: ";
	cin >> students[index].age;
	cout << "Dannye studenta obnovleny.\n";
}

// Udaleniye studenta iz spiska
void deleteStudent() {
	if (studentCount == 0) {
		cout << "Net studentov dlya udaleniya.\n";
		return;
	}
	showStudents();
	cout << "Vvedite nomer studenta dlya udaleniya: ";
	int index;
	cin >> index;
	if (index <= 0 || index > studentCount) {
		cout << "Nekorrektnyy nomer.\n";
		return;
	}
	index--;
	for (int i = index; i < studentCount - 1; i++) {
		students[i] = students[i + 1];
	}
	studentCount--;
	cout << "Student udalën.\n";
}

// Vvod neskol'kikh studentov
void inputStudents() {
	int count;
	cout << "Skol'ko studentov vvesti: ";
	cin >> count;
	if (count <= 0) {
		cout << "Nekorrektnoe chislo.\n";
		return;
	}
	for (int i = 0; i < count; i++) {
		if (studentCount >= capacity) {
			resizeArray();
		}
		Student add;
		cout << "Student " << i + 1 << ":\n";
		cout << "Imya: ";
		cin >> add.name;
		cout << "Familiya: ";
		cin >> add.surname;
		cout << "Vozrast: ";
		cin >> add.age;
		students[studentCount++] = add;
	}
	cout << count << " studentov dobavleno.\n";
}

// Glavnaya funktsiya programmy
int main() {
	loadFile(); // Zagruzka dannykh pri zapuske
	while (true) {
		showMenu(); // Vyvod menyu
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			showStudents();
			break;
		case 2:
			addStudent();
			break;
		case 3:
			changeStudent();
			break;
		case 4:
			deleteStudent();
			break;
		case 5:
			inputStudents();
			break;
		case 6:
			saveToFile();
			break;
		case 7:
			loadFile();
			break;
		case 0:
			cout << "Vyhod iz programmy.\n";
			delete[] students;
			return 0;
		default:
			cout << "Nekorrektnyy vybor, povtorite.\n";
		}
	}
}
