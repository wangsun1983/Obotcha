Obotcha:Tools library based on  C++14
-[![Total alerts](https://img.shields.io/lgtm/alerts/g/wangsun1983/Obotcha.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wangsun1983/Obotcha/alerts/)

-----------------------------------
### What is Obotcha
Obotcha is a tool library based on C++14.it provides the following functions.

-   [Base Class](https://github.com/wangsun1983/Obotcha/tree/master/lang)  
    -  Object （SuperClass）
    -  Reflect（provide reflect functions ）
    -  Exception（provide Exception function ）
-   [Thread](https://github.com/wangsun1983/Obotcha/tree/master/util/concurrent)  
    - Thread（provide methods to create/start a thread）
    - Executor （provide ThreadExecutorPool，ThreadCachedPoolExecutor，ScheduledThreadPoolExecutor） 
    - Mutex（Mutex，Condition......）
    - ReadWriteLock（ReadWriteLock......）
    - ConcurrentLock（CountDownLatch，Barrier......）
    - Atomic Data（AtomicBoolean，AtomicInteger......） 
-   [IO](https://github.com/wangsun1983/Obotcha/tree/master/io)  
    - FileInputStream/FileOutputStream (provide methods to read/write file)
    - FileNodeReader (provide methods to read/write a node）
    - FileWatcher (provide methods to monitor file's changes) 
    - ZipStream（provide methods to zip/unzip files）
    - LibraryFile (provide methods to open library)
- [Db](https://github.com/wangsun1983/Obotcha/tree/master/sql)
    - Provide ORM for sqlite/mysql
    - Provide methods to use redis
-  [Text](https://github.com/wangsun1983/Obotcha/tree/master/util/text)
    - Xml  （XmlDocument，XmlValue，XmlWriter）
    - Json（JsonArray，JsonReader，JsonWriter）
    - Ini（IniReader，IniValue）
    - Yaml（YamlReader）
    - Conf（ConfReader）
-  [Net](https://github.com/wangsun1983/Obotcha/tree/master/net)   
    - Support Tcp client/server
    - Support Udp client/server
    - Support Websocket client/server
    - Support Http1.1/Http 2.0
    - Support Https
-  [Process ](https://github.com/wangsun1983/Obotcha/tree/master/process)
     - Provide methods to do IPC transaction。
     - Provider class(Serializable) to do data serialization
-  [Security](https://github.com/wangsun1983/Obotcha/tree/master/security)
     - Support Aes，Base64，Crc32，Des，Md，Rsa，Sha。

### Why Obotcha
In early 2019, I discussed with my friends to write a  server program in C + +. After using C++ for some time, I found that although boost and poco tool libraries provide many powerful functions, they are still very inconvenient for beginners. 

- Memory management, this is an old issue.
- Non aggregation of class functions.
- After paradigm programming, the code becomes very difficult to understand.
- Various open source libraries of C + + are scattered in every corner without unified and centralized management.
- Without reflection, ORM cannot be realized.
- There is no implementation of serialization / deserialization, which makes  process communication very troublesome

For these reasons, I started writing obotcha.


### How to use Obotcha
-  Obotcha uses its own smart pointer(sp) for memory management. To achieve this, all class declarations need to use DECLARE_ Class or DECLARE_ TEMPLATE_ CLASS. The former is used for non template class declaration, and the latter is used for template class declaration. Examples are as follows：
    ```
    DECLARE_CLASS(Data) {
    public:
        int i;
    };
    ```
- Obotcha uses DECLARE_ REFLECT_ Field defines reflective / serializable member variables, Examples are as follows：
    ```
    DECLARE_CLASS(SampleData) {
    public:
        int intData;
        byte byteData;
        double doubleData;
        float floatData;
        long longData;
        String stringData;
        uint8_t uint8Data;
        uint16_t uint16Data;
        uint32_t uint32Data;
        uint64_t uint64Data;
        bool boolData;
        DECLARE_REFLECT_FIELD(SampleData,intData,byteData,doubleData,
                                floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                                uint64Data,boolData)
    };
     ```
- The overall code architecture of obotcha refers to the code structure and implementation of Java. The purpose is to use obotcha to quickly convert java code into C + + code.
- Obotcha uses some third-party libraries (OpenSSL, zlib, etc.), and the open source library codes used are stored in the external directory.
- Obotcha can use G + + / GCC / clang as the main compiler.

### How to build Obotcha
-The first compilation needs to run in the code root directory/ build. SH `, which can generate the corresponding out directory.
-After the first time, you can directly use the 'make' command to compile.

### Obotcha's Sample Code
- Obotcha's test code is the best example. These codes are stored in the [obotcha TestSuite](https://github.com/wangsun1983/Obotcha/tree/master/security) .
- Obotchatestsuite stores the interface test functions of all classes of obotcha.

### Obotcha's Future
-I t is expected that obotcha will be used in 2022 to start the development of  server Gagira.
