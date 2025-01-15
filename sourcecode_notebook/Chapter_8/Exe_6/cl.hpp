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
    cl(const cl&) = default;
    T* get_val() const {return val;}
};

#endif /* CL_HH */
