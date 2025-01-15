#ifndef CL_HH
#define CL_HH

template <typename T>
class cl 
{
  private:
    T *val = new T;
    
  public:
    cl(){}
    ~cl(){ delete val; }
    cl(const cl&);
  cl & operator= (const cl&);
    T* get_val() const {return val;}
};

template <typename T>
cl<T>::cl (const cl & rhs): val(new T (*rhs.val)) {}

template <typename T>
cl<T> & cl<T>::operator= (const cl & rhs)
{
  if (this != &rhs)
    {
      delete val;
      val = new T (*rhs.val);
    }
  return *this;
}

#endif /* CL_HH */
