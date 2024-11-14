# How to Perform Static Analysis

To perform static analysis using Cppcheck:

**Install Cppcheck:**

#### bash : 

sudo apt-get install cppcheck

# Run Cppcheck on the C++ file:

##### bash : 

cppcheck --enable=all --inconclusive employee_manager.cpp


# * Tools for Static Code Analysis : 

**Cppcheck:** A static analysis tool for C++ code that detects bugs and potential issues.
**Clang-Tidy:** Part of the LLVM project, helps in identifying modern C++ issues.
**SonarQube:** Provides in-depth analysis and metrics for C++ projects.





# Detailed Static Analysis : 

# 1. Potential Bug: Division by Zero
In the function calculateAverageSalary(), there is a risk of division by zero if the vector employees is empty:

##### Cpp

double calculateAverageSalary() const {
    if (employees.empty()) {
        throw runtime_error("No employees to calculate average salary.");
    }
    double total = 0;
    for (const auto &e : employees) {
        total += e.salary;
    }
    return total / employees.size(); // Possible division by zero
}

# Recommendation: Add a check for an empty vector before performing the division:

##### Cpp

if (employees.empty()) {
    cout << "No employees available for salary calculation." << endl;
    return 0.0;
}


# 2. Code Smell: Raw Loop in findEmployeeById()
The function findEmployeeById() uses a raw loop for searching, which is less efficient and less readable compared to using the standard library:

##### Cpp

int findEmployeeById(const vector<Employee> &employees, int id) {
    for (int i = 0; i < employees.size(); ++i) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

# Recommendation: Use std::find_if for better readability and safety:

##### Cpp

auto it = std::find_if(employees.begin(), employees.end(),
                       [id](const Employee &e) { return e.id == id; });
return (it != employees.end()) ? std::distance(employees.begin(), it) : -1;


# # 3. Redundant Code: Duplicate Data Structures
The EmployeeManager class uses both vector and unordered_map to store employee data, leading to increased memory usage:

##### Cpp

vector<Employee> employees;
unordered_map<int, Employee> employeeMap;

Issue: Storing the same data in both containers is redundant and wastes memory.

# Recommendation: Use only unordered_map for storing employee data, as it provides efficient lookup.


# 4. Performance Issue: Inefficient Erase Operation
The removeEmployee() function uses std::remove_if with a vector, which can be inefficient for large datasets:

##### Cpp

auto it = remove_if(employees.begin(), employees.end(), [&](const Employee &e) {
    return e.id == id;
});
if (it != employees.end()) {
    employees.erase(it, employees.end());
}

# Recommendation: If you switch to using only unordered_map, you can directly remove the element:

##### Cpp

employeeMap.erase(id);


# 5. Best Practice: Passing Large Containers by Value
Functions like printAllEmployees() pass the vector by value, causing unnecessary copying:

##### Cpp

void printAllEmployees(vector<Employee> employees) const;

# Recommendation: Pass the vector as a const reference:
##### Cpp

void printAllEmployees(const vector<Employee> &employees) const;


# 6. Modernization: Use of NULL Instead of nullptr
In modern C++ (C++11 and beyond), it is recommended to use nullptr instead of NULL for pointers.
Example: Replace:

##### Cpp

int *ptr = NULL;

##### Cpp

int *ptr = nullptr;


# 7. Error Handling: Exception Usage
In functions like calculateAverageSalary(), exceptions are used for non-exceptional control flow:

##### Cpp

if (employees.empty()) {
    throw runtime_error("No employees to calculate average salary.");
}

# Recommendation: Use a simple conditional check instead of throwing an exception:

##### Cpp

if (employees.empty()) {
    cout << "No employees available." << endl;
    return 0.0;
}

# Conclusion
The provided C++ code contains several areas that can be improved through static analysis. By addressing the identified issues, the code can be made more efficient, maintainable, and aligned with modern C++ best practices. This manual analysis highlights the benefits of integrating static analysis tools like Cppcheck and Clang-Tidy in the development process.


