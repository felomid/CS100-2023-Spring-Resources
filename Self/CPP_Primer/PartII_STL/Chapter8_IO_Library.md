# Chapter 8 IO Library

## 8.1 IO Class

​	除了 `istream` 和 `ostream` 之外，标准库还定义了其他一些类型

- `iostream` 定义了用于读写流的基本类型
- `fstream` 定义了读写文件的基本类型
- `sstream` 定义了读写内存string对象的类型

|头文件|类型|
|:---------|:-------|
|`iostream`|`istream`, `wistream` 从流读取数据|
| |`ostream`, `wostreawm` 向流写入数据|
|  |`iostream`, `wiostream` 读写流|
|`fstream`| 与上类似|
|`sstream`| 与上类型，不过是`stringstream`|



#### IO类型间的关系

​	不同类型的流之间的差异之所以能被忽略，是通过**继承关系(inheritance) **实现的。

<img src="E:\Per_info\课程资料\大一下\CS100\CS100-recitations-spring2023-main\r14\img\iostream_inheritance.png" alt="iostream_inheritance" style="zoom:60%;" />



### 8.1.1 IO对象无拷贝或赋值

```cpp
ofstream out1, out2;
out1 = out2;												// 错误：不能对流对象赋值
ofstream print(ofstream);						// 错误：不能初始化 ofstream 参数
out2 = print(out2);									// 错误：不能拷贝流对象
```

 	正是因为不能拷贝IO对象，所以我们也不可将形参或返回类型设置为流类型（但是可以设置为流类型的引用）。并且因为读写一个IO对象会改变它的状态，所以也不能把引用设置为 `const`.



### 8.1.2 条件状态



