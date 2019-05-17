namespace Utils
{

template<typename T>
T* Singleton<T>::m_instance = nullptr;

template <typename T>
inline T* Singleton<T>::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = Singleton<T>::createInstance();
    }
    return m_instance;
}

template <typename T>
Singleton<T>::Singleton()
{
    m_instance = static_cast<T*>(this);
}

template <typename T>
Singleton<T>::~Singleton()
{
    if(m_instance != nullptr)
    {
        delete m_instance;
    }
    m_instance = nullptr;
}

template <typename T>
T* Singleton<T>::createInstance()
{
    return new T();
}

}