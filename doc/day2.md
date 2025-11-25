1. *The [[nodiscard]] attribute in C++ (introduced in C++17) is a language feature used to indicate that the return value of a function or an object of a specific type should not be ignored. Its primary purpose is to help developers prevent bugs by ensuring that important return values, such as error codes or newly created objects, are properly handled.*
-> I have to handle the return value, otherwise compiler will give warning

2. *The const keyword, when placed after the parameter list and before the function body in a member function declaration and definition, signifies that the function will not modify the state of the object on which it is called.*

3. *The explicit keyword in C++ is a specifier used primarily with constructors and conversion operators to prevent implicit type conversions. Its main purpose is to disallow the compiler from automatically converting one type to another using a constructor that takes a single argument, or a user-defined conversion operator.*
-> `MyClass obj1 = 5; // Implicit conversion from int to MyClass
    func(10);        // Implicit conversion from int to MyClass`