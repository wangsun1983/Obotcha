# Obotcha
[![Total alerts](https://img.shields.io/lgtm/alerts/g/wangsun1983/Obotcha.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wangsun1983/Obotcha/alerts/)

- **如何声明一个简单类（不含模板）**
```
DECLARE_SIMPLE_CLASS(TestClass1) {
public:
    int i;
    ~_TestClass1() {
    
    }
};
```

+ **如何声明一个复杂类（含模板）**
```
DECLARE_CLASS(ArrayList,1) {
public:
    inline void add(T val) {
        elements.insert(elements.end(),val); 
    }
}`
```
- **如何生成实例**
```
 TestClass1 c1 = createTestClass1();
```
Obotcha中不需要用new来生成实例。  
使用DECLARE_SIMPLE_CLASS/DECLARE_CLASS后系统会自动生成对应的create函数（create+类名）  
