# Chapter 3 String Vector and Array

### 3.5.5 Interface to Old version

#### **Using string objects and C-style string together**
- In order to initialize a C-style string using string objects, we can use `.c_str()` provided by string class.

- `c_str` function returns a pointer pointing to the char array ended with '\0'.
- Also, the return type is **const char*** to make sure that we won't change the content
```cpp
  char *str  = s; //  错误：不能用 string 对象初始化 char*
  const char *str = s.c_str();  //正确
```
> Pay attention that we can't guarantee that the array returned by `c_str` is always valid. In fact, if the following operations change the value of `s` , it may make the previous returned array invalid.

#### **Initialize vector objects using array**

To do this, you need to specify the address of the first and the trailing element.

```cpp
int int_arr[] = {0, 1, 2, 3, 4, 5};
vector<int> ivec(begin(int_arr), end(int_arr));
vector<int> subvec(int_arr + 1, int_arr + 4);
```
> You are recommended to use Standard Library type rather than array.

## 3.6 Multi-dimensional Array

- Multi-dimensional Array is actually **array of array**

#### **Use range-for statement tu operate multi-dimensional array**
```cpp
size_t cnt = 0;
for (auto &row : ia)
  for (auto &col : row) {
    col = cnt;
    ++cnt;
  }
```
- We use referrence type since we want to change the value
- However, there is a deeper reason

```cpp
for (const auto &row : ia)
  for (auto col : row)
    std::cout << col << endl;
```
- Why do we still use referrence type here ?

- **Because we want to avoid the array being automatically converted to pointer** !!!

```cpp
for (auto row : ia)
  for (auto col : row)
```
- This will not pass compilation since when the compiler initialize `row` , it will be converted to a pointer pointing to the first element of its corresponding row array, so the value type of `row` is `int*` , then the inner loop is obviously invalid.

> In conclusion, if you want to use range-for statement to cope with multi-dimensional array, all the other loop should use referrence type except for the most inside one.

#### **Pointer and multi-dimensional array**

```cpp
int *ip[4];     //  含有4个整型指针的数组
int (*ip)[4];   //  指向含有4个整数的数组
```

> We suggest you to use type alias to simplify the process you use multi-dimensional array
> ```cpp
>using int _array = int[4] //  preferred
>typedef int int_array[4]  //  less preferred, but better than using #define
>```
