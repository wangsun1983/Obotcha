Obotcha:基于C++14的开源工具库
-[![Total alerts](https://img.shields.io/lgtm/alerts/g/wangsun1983/Obotcha.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wangsun1983/Obotcha/alerts/)

-----------------------------------
### 什么是Obotcha
Obotcha是基于C++14开发的一个工具库，该工具库目前提供了如下的功能。  

-   [基础类](https://github.com/wangsun1983/Obotcha/tree/master/lang)  
    -  Object类 （所有Class父类）
    -  Reflect类（支持C++类反射）
    -  Exception类（各类异常）
-   [多线程工具类](https://github.com/wangsun1983/Obotcha/tree/master/util/concurrent)  
    - Thread类 （实现了线程的创建，退出）
    - 线程池类  （实现了ThreadExecutorPool，ThreadCachedPoolExecutor，ScheduledThreadPoolExecutor） 
    - 线程锁（Mutex，Condition） ，读写锁（ReadWriteLock）
    - 线程等待锁（CountDownLatch，Barrier）
    - 基本数据类型的原子操作（AtomicBoolean，AtomicInteger等） 
-   [IO工具库](https://github.com/wangsun1983/Obotcha/tree/master/io)  
    - 文件读取/写入类（FileInputStream/FileOutputStream类）
    - 文件节点读取类（FileNodeReader类）
    - 文件状态监听类（FileWatcher类）
    - Zip文件操作类（ZipStream类）
    - 内存映射文件操作类（MemoryFileInputStream，MemoryFileOutputStream类）  
    - so库文件读取类（LibraryFileInputStream类）
- [数据库工具库](https://github.com/wangsun1983/Obotcha/tree/master/sql)
    - 支持Sqlite3搜索，执行
    - 支持MySql搜索，执行
    - 支持数据ORM反射
-  [文本处理工具库](https://github.com/wangsun1983/Obotcha/tree/master/util/text)
    - xml文件读写类 （XmlDocument，XmlValue，XmlWriter类）
    - json文件读写类（JsonArray，JsonReader，JsonWriter类）
    - ini文件读取类（IniReader，IniValue类）
    - yaml文件读取类（YamlReader类）
    - conf文件读取类（ConfReader类）
-  [网络处理工具库](https://github.com/wangsun1983/Obotcha/tree/master/net)   
    - 支持Tcp服务端，客户端管理
    - 支持Udp服务端，客户端管理
    - 支持WebSocket服务端，客户端管理
    - 支持Http V1协议
    - 支持Https
-  [进程间通信工具库 ](https://github.com/wangsun1983/Obotcha/tree/master/process)
     - 支持Posix标准的进程间通信。
-  [安全相关工具库](https://github.com/wangsun1983/Obotcha/tree/master/security)
     - 支持Aes，Base64，Crc32，Des，Md，Rsa，Sha加密。

### Obotcha的原由
2019年初的时候和朋友讨论用C++编写一个后台服务器程序，使用了一段时间发现虽然boost，poco这些工具库提供了很多强大的功能，但是对于初学者来说，使用还是非常的不方便。   
-  内存管理，这个是C++/C语言老生常谈的问题。
-  类功能的不聚合。
-  范型编程后代码会变得非常难理解。
- C++各种开源库散布在各个角落，没有统一集中管理。
- 没有反射导致ORM无法实现。
基于上面这些原因，所以我就开始了Obotcha的编写。

### Obotcha的设计
- Obotcha使用了自己的sp智能指针来做内存管理。为了达到这个目的，所有的类申明都需要使用DELCARE_SIMPLE_CLASS和DECLARE_CLASS。前者用于非模板类申明，后者用于模板类申明。示例如下：
    ```
    DECLARE_SIMPLE_CLASS(Data) {
    public:
        int i;
    };
    ```
- Obotcha的整体代码架构均参考了Java的代码结构和实现。目的是能使用Obotcha很快地将java代码转换C++代码。
- Obotcha使用了部分第三方库（openssl，zlib等），这些使用的开源库代码均存放在external目录下。
- Obotcha使用g++和gcc作为主要编译器，目前暂时不支持clang。

### Obotcha的编译
- 第一次编译需要在代码根目录下运行`./build.sh`，这样可以生成对应的out目录。
- 之后每次编译可以直接使用`make`命令来编译。

### Obotcha的示例
- Obotcha的测试代码是最好的例子，这些代码存放在test目录下 。test目录下存放了Obotcha所有类的接口测试函数。

### Obotcha的未来
-   预计明年开始使用Obotcha开始进行后台服务器Gagira的开发。
