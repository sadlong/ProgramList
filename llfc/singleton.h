#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"

template <typename T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>& st) = delete;
    static std::shared_ptr<T> m_instance;

public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            //这里为什么不用make_shared? ---评论区的答案是构造函数是protected
            m_instance = std::shared_ptr<T>(new T);
        });
        return m_instance;
    }

    void PrintAdress() {
        std::cout << m_instance.get() << std::endl;
    }

    ~Singleton() {
        std::cout << "this is sigleton destruct" << std::endl;
    }
};

//类内声明 类外初始化 初始化要带上变量类型
template <typename T>
std::shared_ptr<T> Singleton<T>::m_instance = nullptr;

#endif // SINGLETON_H
