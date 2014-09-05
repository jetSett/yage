template<class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::SmartPtr() : Ownership<T>(nullptr), _data(nullptr){
}

template<class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::SmartPtr(T* val) : Ownership<T>(nullptr){
    _data = val;
}

template<class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::SmartPtr(const SmartPtr<T, Ownership>& ptr) :
    Ownership<T>(ptr),
    _data(this->clone(ptr._data)){
}

template<class T, template <class> class Ownership>
SmartPtr<T, Ownership>::~SmartPtr() {
    this->release(_data);
}

template<class T, template <class> class Ownership>
inline T& SmartPtr<T, Ownership>::operator*() const{
    return *_data;
}

template<class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::operator T*() const{
    return _data;
}

template<class T, template <class> class Ownership>
inline T* SmartPtr<T, Ownership>::operator->() const{
    return _data;
}

template<class T, template <class> class Ownership>
const SmartPtr<T, Ownership>& SmartPtr<T, Ownership>::operator=(const SmartPtr<T, Ownership>& ptr){
    SmartPtr<T, Ownership>(ptr).swap(*this);

    return *this;
}

template<class T, template <class> class Ownership>
const SmartPtr<T, Ownership>& SmartPtr<T, Ownership>::operator=(T* pt){
//    SmartPtr<T, Ownership> ptr(pt);
//    ptr.swap(*this);
    if(pt != _data){
        SmartPtr<T, Ownership>(pt).swap(*this);
    }
    return *this;
}
