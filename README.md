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



Suggested Test Cases for Verification
To verify the issues found during static analysis, you can use the following test cases:

