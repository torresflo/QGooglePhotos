#ifndef UTILS_SINGLETON_HPP
#define UTILS_SINGLETON_HPP

#include <Utils/NonCopyable.hpp>

namespace Utils
{

template <typename T>
class Singleton : public NonCopyable
{
public:
    static T* getInstance();

protected:
    Singleton();
    virtual ~Singleton();

private:
    static T* createInstance();

    static T* m_instance;
};

} //namespace Utils

#include <Utils/Singleton.inl>

#endif //UTILS_SINGLETON_HPP
