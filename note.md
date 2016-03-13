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

# Reference
- [1] http://www.cnblogs.com/kaituorensheng/p/3239446.html
