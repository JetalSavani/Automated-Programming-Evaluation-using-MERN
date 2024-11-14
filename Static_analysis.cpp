#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class Employee {
public:
    string name;
    int id;
    double salary;

    Employee(string n, int i, double s) : name(n), id(i), salary(s) {}
};

class EmployeeManager {
private:
    vector<Employee> employees;
    unordered_map<int, Employee> employeeMap;

public:
    void addEmployee(const string &name, int id, double salary) {
        if (id <= 0 || salary < 0) {
            throw invalid_argument("Invalid ID or salary.");
        }
        Employee emp(name, id, salary);
        employees.push_back(emp);
        employeeMap[id] = emp;
    }

    void printAllEmployees() const {
        if (employees.empty()) {
            cout << "No employees to display." << endl;
            return;
        }
        for (const auto &e : employees) {
            cout << "Name: " << e.name << ", ID: " << e.id << ", Salary: $" << e.salary << endl;
        }
    }

    void updateSalary(int id, double newSalary) {
        if (employeeMap.find(id) == employeeMap.end()) {
            cout << "Employee not found." << endl;
            return;
        }
        if (newSalary < 0) {
            throw invalid_argument("Salary cannot be negative.");
        }
        employeeMap[id].salary = newSalary;
        cout << "Updated salary for ID: " << id << " to $" << newSalary << endl;
    }

    double calculateAverageSalary() const {
        if (employees.empty()) {
            throw runtime_error("No employees to calculate average salary.");
        }
        double total = 0;
        for (const auto &e : employees) {
            total += e.salary;
        }
        return total / employees.size();
    }

    void removeEmployee(int id) {
        auto it = remove_if(employees.begin(), employees.end(), [&](const Employee &e) {
            return e.id == id;
        });
        if (it != employees.end()) {
            employees.erase(it, employees.end());
            employeeMap.erase(id);
            cout << "Employee with ID " << id << " removed." << endl;
        } else {
            cout << "Employee not found." << endl;
        }
    }

    void displayTopSalaries(int n) const {
        if (n <= 0) {
            cout << "Invalid number of top salaries requested." << endl;
            return;
        }
        vector<Employee> sortedEmployees = employees;
        sort(sortedEmployees.begin(), sortedEmployees.end(), [](const Employee &a, const Employee &b) {
            return a.salary > b.salary;
        });
        for (int i = 0; i < min(n, (int)sortedEmployees.size()); ++i) {
            cout << i + 1 << ". " << sortedEmployees[i].name << ": $" << sortedEmployees[i].salary << endl;
        }
    }

    void findEmployeeById(int id) const {
        if (employeeMap.find(id) != employeeMap.end()) {
            const auto &e = employeeMap.at(id);
            cout << "Employee Found - Name: " << e.name << ", ID: " << e.id << ", Salary: $" << e.salary << endl;
        } else {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }
};

int main() {
    EmployeeManager manager;
    try {
        manager.addEmployee("Alice", 101, 5000.0);
        manager.addEmployee("Bob", 102, 6000.0);
        manager.addEmployee("Charlie", 103, 5500.0);
        manager.addEmployee("David", 104, 5200.0);
        manager.addEmployee("Eve", 105, 5800.0);

        cout << "\nAll Employees:" << endl;
        manager.printAllEmployees();

        cout << "\nAverage Salary: $" << manager.calculateAverageSalary() << endl;

        cout << "\nUpdating salary for Bob..." << endl;
        manager.updateSalary(102, 6200.0);

        cout << "\nDisplaying top 3 salaries:" << endl;
        manager.displayTopSalaries(3);

        cout << "\nFinding Employee with ID 103:" << endl;
        manager.findEmployeeById(103);

        cout << "\nRemoving Employee with ID 104:" << endl;
        manager.removeEmployee(104);

        cout << "\nAll Employees after removal:" << endl;
        manager.printAllEmployees();
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
