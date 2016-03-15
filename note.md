# C++ Primer 5e Note
This is the note written during my reading *C++ Primer 5e*.

## Chapter 6: Functions
### There're mainly 2 types when passing arguments:
- Pass by value (include pass by pointer): the value is copied into function. however avoid copy when objects are large class type.
- Pass by reference: just alias of objects

### Tips
- Compared to Programmers in C often use pointer parameters to access objects outside a function, C++ programmers generally use **reference parameters** instead.
- Reference parameters that are not changed inside a function should be **references to const**.
- `void fcn(const int i);` and `void fcn(int i);` should not exist at the same time or raise redefinition error.
- `const int &a = 12; // ok` however `int &b = 12; // error: initializer must be an object!`
- `const int c = 123; const int &d = c; // ok` however `int &e = c; // error`
- **Using a reference instead of a reference to const unduly limits the type of arguments that can be used with the function. As had been said, we cannot pass a const object or a literal, or an object that requires conversion to a plain reference parameter.**
- Passing array: (1) with `const` when not modify elemets: `void print(const int *x, size_t size);` (2) without `const`: `void change(int *x, size_t, size);` (3) array reference: `void print(int (&arr)[10])`
- `int *ptrs[10]`: ptrs is an array of 10 pointers to int. **an array of pointers**
- `int (*ptr)[10]`: ptr points to an array of 10 ints. **a pointer to array**
- `int (&ref)[10]`: ref refers to an array of 10 ints
- Passing 2-d array: (1) `void print(const int (*x)[10], size_t rowSize);`  (2) `void print(const int x[][10], size_t rowSize);`
- `size_t size = end(ary) - begin(ary);`
- Reference returns are lvalues; other return types yield rvalues. For example, 
```
char &get_val(string &s, size_type ix){ return s[ix]; }
int main(){
  string s = "hello world!"'
  get_val(s, 0) = 'H';
  cout << s;  // "Hello world!"
}
```
- list initializing the return value>: `vector<string> str_list(){ return {"abc", "def", "ghi"}; }`
- Return from `main`: the value returned from main is treated as a **status indicator**. `0` means success while most of others mean failure.
- Returning a pointer to an array: (1) Use type alias `typedef int arrT[10];` or `using arrT = int[10];`, then `arrT *func(int i);` returns a pointer to an array. (2) Without type alias: `int (*func(int i))[10]`. (3) Under C++11, `auto func(int i) -> int(*)[10]`. Return type follows the `->` sign and use auto to temporarily replace.
- When using default arguments, be sure to **declare with initializer** and **not repeat in parameter list of definition**.
```
void printSth(int a, char b = 'b', string c = "str");
int main(){ ... }
void printSth(int a, char b, string c){
	cout << a << ", " << b << ", " << c << ", " << endl;
}
```
- `constexpr` functions: the return type and the type of each parameter **in a must be a literal type**.

### Function overloading
- `Record lookup(Account &);` and `Record lookup(const Account &);` and `Record lookup(Account*)` and `Record lookup(const Account*);` can exist at the same time. (**low-level const**)
- while **top-level const** cannot exist simultaneously. e.g. `Record lookup(const Account)` and `Record lookup(Account)`, or `Record lookup(Phone*)` and `Record lookup(Phone* const)`.
- `const_cast` is useful in the context of overloaded fuinctions.
```
const string &shorterString(const string &s1, const string &s2){  return s1 < s2 ? s1 : s2;  }
string &shorterString(string &s1, string s2){ 
  auto &r = shorterString(const_cast<const string&>(s1), const_cast<const string&>(s2)); 
  return const_cast<string &>(r);
}
```


### size_t v.s. size_type [1]
1. size_t是全局定義的類型；size_type是STL類中定義的類型屬性，用以保存任意string和vector類對象的長度
2. string::size_type 制類型一般就是unsigned int, 但是不同機器環境長度可能不同 win32 和win64上長度差別;size_type一般也是unsigned int
3. 使用的時候可以參考：
   string::size_type  a =123;
   vector<int>size_type b=234;
   size_t b=456;
4. size_t 使用的時候頭文件需要 <cstddef> ；size_type 使用的時候需要<string>或者<vector>
5.  sizeof(string::size_type) 
     sizeof(vector<bool>::size_type) 
     sizeof(vector<char>::size_type)  
     sizeof(size_t) 
     上述長度均相等，長度為win32:4 win64:8
6. 二者聯繫：在用下標訪問元素時，vector使用vector::size_type作為下標類型，而數組下標的正確類型則是size_t

### Functions with Varying Parameters
**Unknown number of arguments of a single type** 
- Use `initializer_list`. 
- You may `initializer_list<int> li;`, but be aware of the elements in an `initializer_list` are always const values. 
- When initialize a initializer_list one should pass `{"abc", "zxc"}`. e.g. `printSomeStrings({sa, sb, sc, "OVER!"});` 
- When printing, one can use either **range for** or **iterator**. 
- When using range for, use `for(const auto &i : ls)` rather than `for(auto i : ls)` because you are not going to (also cannot) modify something in the initializer_list. By this, one can avoid waste cpu to copy the value.

### Declaration and Definition
- Header files should contain declarations, source files should contain definitions.
- However, `inline` and `constexpr` functions are usually defined in header files because may being defined multiple times in the program. 

### Aids for Debugging
**Preprocessor** is a program that runs before the compiler. Preprocessor variables are managed by the preprocessor but not compiler. As as result, we refer to them directly without the `std::` prefix. e.g. `NULL`. Also, when using `#ifndef FUNC_H`, `#define FUNC_H` and `#endif FUNC_H`, `FUNC_H` is a preprocessor variable. A preprocessor variable have one of two possible states: defined or not defined.
- `assert` preprocessor macro: remember to `#include <cassert>`. if argument passed into `assert` is true then do nothing.
- `NDEBUG` preprocessor macro: `assert` depends on whether `NDEBUG` is defined or not. If defined (e.g. `g++ -D NDEBUG main.cc`), then `assert` is disabled. Also, a couple of variables can be useful in debugging:
```
#ifndef NDEBUG
		if(i3 == i4){
			cerr << "Error: in " << __FILE__ << ": in function " << __func__
				 << " at line " << __LINE__ << ". On " << __DATE__ << " at "
				 << __TIME__ << endl;
		}
	#endif
// output: "Error: in array_test.cpp: in function main at line 123. On Mar 13 2016 at 14:28:16"
```

### Function Pointer
- If there is a function `bool lengthCompare(const string &, const string &);` then we may declare a pointer (in place of the function name): `bool (*pf)(const string &, const string &);  // uninitialized`.
- By `typedef`, it can be easier: `typedef bool (*func)(const string &, const string &);` or `typedef decltype(lengthCompare) *func;` so that `func` has pointer to function type. (We should know that function `lengthCompare` has type `bool(const string &, const string &)`)
- **Usage** When using the name of a function as a value, the function is automatically converted to a pointer. e.g. we can initialize either `pf = lengthCompare;` or `pf = &lengthCompare;`. When using, either `bool b1 = pf("hello", "goodbye")` or `bool b1 = (*pf)("hello", "goodbye")` is okay.
- **Example** [Person.h](https://github.com/coldmanck/Cpp-Primer/blob/master/Person.h) Be aware of **`const` class objects can only explicitly call `const` member functions**, so `getHeight()` and `getWeight()` member functions in Person class should be declared `const`. For `const` member functions defined outside of the class declaration, the `const` keyword must be used on both the function prototype in the class declaration and on the function definition. **Note that constructors should not be marked as const.** [2]
```
#include "Person.h"

void printBigger(const Person &p1, const Person &p2, bool (*pf)(const Person &, const Person &)){
	if(pf(p1, p2))
		cout << p1 << " is bigger!" << endl;
	else
		cout << p2 << " is bigger!" << endl;
}

bool compareHeight(const Person &p1, const Person &p2){
	return p1.getHeight() > p2.getHeight() ? true : false;
}

bool compareWeight(const Person &p1, const Person &p2){
	return p1.getWeight() > p2.getWeight() ? true : false;
}

int main(){
  Person p1(174,65), p2(177, 59);
	printBigger(p1, p2, compareHeight);
	printBigger(p1, p2, compareWeight);
}
```

## Chapter 7: Classes
- `Abstract Data Type`: a class that uses data abstraction abd encapsulation.
- Functions defined in the class are implicitly `inline`.
- when calling `object.func()` it likes `ClassName::func(&object)`.
- `this` is a **`const` pointer** point to the address of calling object. Type: `ClassName *const`. 
- As a result, we cannot (by default) bind `this` to a `const` object.
- By declare `const` after the parameter list, we indicate that `this` is a `const` pointer to `const` to solve the problem.
- `std::string Sales_data::isbn const()` equals `std::string Sales_data::isbn(const Sales_data *const this)` is a **const member function**.
- 簡單來說就是在 member function 上加 `const` 可以讓 `const` object 也能使用（也只能使用）此 const member function.
- Functions that are conceptually part of a class, but not defined inside the class, are typically declared (but not defined) in the same header as the class itself.
- If no constructor is defined, the compile-generated **synthesized default constructor** is used to initialize.
- Classes that have members of built-in or compund type (array or pointer) usually should rely on the synthesized default constructor **only** if all such members have in-class initializers. Also, if there's another class type in the class, it cannot be initialized.
- 4 types of constructor 
```
  Sales_data() = default;
  Sales_data(const std::string &b): bookNo(b) {}
  Sales_data(const std::string &b, unsigned u, double p): bookNo(b), units_sold(u), revenue(p*u) {}
  Sales_data(std::istream &);	// defined outside class
  
  // outside class
  Sales_data::Sales_data(std::istream &is){ is >> *this; }
  
  // in main.cc
  Sales_data s1, s2("yoyo"), s3("haha", 123, 456), s4(cin);
```
- **Declaration and definition, of the member function which use another class type, should be placed in different files**; declared in header file and defined in source file. [3]
- Related to copy, assignment and destruction, compiler will synthesize them automatically. However, it may encounter some problems when class using **dynamic array**.
- The only difference between using `class` and `struct` is **default access control**.
- Type members: `typedef std::string::size_type pos` or `using pos = std::string::size_type`, must appear before they are used. As a result, they usually appear at the beginning of the class.
- `inline` and `constexpr` function should be defined in the header.
- A `mutable` data member is never `const`, even when it is a member of a const object. Accordingly, a `const` member function may change a `mutable` member.
- **In-class initializer must use either the `=` form of initialization or the direct form of initialization using curly braces `{}`.**
- A `const` member function that returns `*this` as a reference should have a return type that is a reference to `const`. Which means, `const Screen &display(std::ostream &os) const`.
- Member function definitions are processed **after** the compiler processes all of the declarations in the class. -> So we can make use of any other entity declared inside the class. (two-step process)
- However, the two-step process aplies only to names used in the body of a member function. Names used in declarations, including names used for the **return type** and **types in the parameter list**, must be seen before being used.
- Type name aliases usually should appear at the beginning of a class. (p.285)
- Even though the class member is hidden (by re-definition in the member function), it's still possible to use either `this->member` or `ClassName::member` to access that `member`.
- In addition, use `::member` to access the global `member`.
- **initialize** v.s. **assign** in constructor: **Members that are `const`, references, or of a class type that doesn't have a default constructor, must be initialized** but not assigned. (p.288-289) Therefore, by using constructor initializers we can avoid faceing compile-time errors and have better efficiency. (**initialized**, rather than **(default) initialized and assigned**)
- When using constructor initializer list, members are initialized in the order in which they appear in the class definition, but not order of initializer list.
- Delegating constructors: use another constructor from its own class to perform its initialization.
- **Implicit conversion**: A constructor that cab be called with a single argument defines an implicit conversion from the constructor's parameter type to the class type. Only 1 class-type conversion is allowed: 
```
String bookName = "The_Book";	Sales_data s1; 
s1 += bookName;	s1 += cin;		// correct
s1 += "The_Book";				// wrong: from const char* -> string -> Sales_data
s1 += string("The_Book");		// okay: from string -> Sales_data
s1 += Sales_data("The_book");	// okay: from const char* -> string
```
- Insert `explicit` at the beginning of the declaration of member function (inside class, no repeated ouside the class body) having just 1 argument to prevent **implicit conversion** of constructors. e.g. `explicit Sales_data(const std::string &b): bookNo(b) { ++count; }`
- When a constructor is declared `explicit`, it can be used only with the **direct form** of initialization (so `Sales_data item = bookName;` is illegal.)
- However, we still can explicitly convert the type to use `explicit` constructor: `s1 += static_cast<Sales_data>(bookName);`

### Friend function / class
- A class can allow another **class or function** to access iots nonpublic members by making that class or function a `friend`.
- A friend declaration only specifies access. It's not a general declaration of the function. Therefore we must also **declare** the function (outside the class) in the same header as the class itself. (While some compilers not enforce this rule)
- A class can also make another class `friend class Window_mgr;` its friend, or declare specific member functions of another (previously defined) class as friends `friend void Window_mgr::clear(ScreenIndex);`, so that the latter's member can access the private/protect member of the former.
- A friend function can be deined inside class, which implictly become `inline`.
- Making a **member function (of another class)** a friend requires careful structuring of our programs. First, **declare** the class which have member function having access to another class. Then, **declare** this member function being `class` in *another class*. Finally, we can **define** this member function. (C++ Primer P.281)
- However, to make other **classes** and **non-member functions** friend, they don't need to have been declared before. (C++ Primer P.281)
- Even if a `friend` non-member function defined in the class, it should also be declared outside the class to be visible.
- `Sales_data obj();` declares a function; `Sales_data obj;` define a default initialized `Sales_data` object.
- Aggregate class (no use): a class is an aggregate if (1) all of its data members are `public` (2) has no constructor (3) has no in-class initializers (4) has no base classes or `virtual` functions. We can define this type of class by list intialization: `Data d1 = {0, "David", 1234};` by the order of data member declared inside the class. (no use)
- A class is literal if it is (1) aggregate class (2) non-aggregate class but meets following restrictions: (a) the data members all must have literal type. (arithmetic types, references, pointers and certain classes) (b) the class must have at least 1 `constexpr` constructor. (c) if a data member has an in-class initializer, the initializer for a member of built-in type must be a constant expression, or if the member has class type, the initializer must use the member's own `constexpr` constructors. (d) The class must use default definition for its destructor.
- We may not initialize the `static` member inside the class. (But `static` member function is OKAY.) Instead, we must define and initialize each static data member outside the class body (Header.cpp file is the best). e.g. `double Account::interestRate = initRate();` **Note that even `initRate()` is private member function it's OK.** **`static` member 跟 member function 一樣需要被在 class 外面 define.**
- However we can still **in-class intialize** the `const static` members, and must do so for `constexpr static` members.


## Reference
1. [【c++】size_t 和 size_type的區別](http://www.cnblogs.com/kaituorensheng/p/3239446.html)
2. [8.10 — Const class objects and member functions](http://www.learncpp.com/cpp-tutorial/810-const-class-objects-and-member-functions/)
3. [Why are constructors defined outside of C++ classes?](http://www.cplusplus.com/forum/beginner/61056/#msg330613)
4. [C++中的extern用法](http://blog.xuite.net/mmkider/world/5015593-C%2B%2B%E4%B8%AD%E7%9A%84extern%E7%94%A8%E6%B3%95)
