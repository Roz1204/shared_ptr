#pragma once

template <class T>
class shared_ptr {
private:
    T* m_ptr;
    int* m_ref_count;
    void release();

public:
    shared_ptr() : m_ptr(nullptr)
                 , m_ref_count(new int(0))
    { }

    shared_ptr(T* ptr) : m_ptr(ptr)
                       , m_ref_count(new int(1))
    { }

    ~shared_ptr(); 

    shared_ptr(const shared_ptr<T>& obj);
    shared_ptr<T>& operator=(const shared_ptr<T>& obj);

    shared_ptr(shared_ptr<T>&& obj); 
    shared_ptr<T>& operator=(shared_ptr<T>&& obj);

    T& operator*() const;
    T* operator->() const;
    T& operator[](int index) const;

    int get_count() const;

    void swap(shared_ptr<T>& obj);
};

template <class T>
void shared_ptr<T>::swap(shared_ptr<T>& obj) {
    std::swap(m_ptr, obj.m_ptr);
    std::swap(m_ref_count, obj.m_ref_count);
}

template <class T>
int shared_ptr<T>::get_count() const {
    return *m_ref_count;
}

template <class T>
T& shared_ptr<T>::operator[](int index) const {
    return m_ptr[index];
}

template <class T>
T* shared_ptr<T>::operator->() const {
    return m_ptr;
}

template <class T>
T& shared_ptr<T>::operator*() const {
    return *m_ptr;
}

template <class T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& obj) {
    if(this != &obj){
        release();

        m_ptr = obj.m_ptr;
        m_ref_count = obj.m_ref_count;

        obj.m_ptr = nullptr;
        obj.m_ref_count = nullptr;
    }
    return *this;
}

template <class T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& obj)
{
    m_ptr = obj.m_ptr;
    m_ref_count = obj.m_ref_count;

    obj.m_ptr = nullptr;
    obj.m_ref_count = nullptr;
}

template <class T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& obj) {
    if(this != &obj) {
        m_ptr = obj.m_ptr;
        m_ref_count = obj.m_ref_count;
        ++(*m_ref_count);
    }
    return *this;
}

template <class T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& obj) {
    m_ptr = obj.m_ptr;
    m_ref_count = obj.m_ref_count;
    ++(*m_ref_count);
}

template <class T>
void shared_ptr<T>::release() {
    if(m_ptr) {
        --(*m_ref_count);
        if(*m_ref_count == 0) {
            delete m_ptr;
            delete m_ref_count;

            m_ptr = nullptr;
            m_ref_count = nullptr;
        }
    }
}

template <class T>
shared_ptr<T>::~shared_ptr() {
    release();
}