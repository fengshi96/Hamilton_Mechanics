//
// Created by shifeng on 3/13/21.
//
#ifndef CPPKIT_VECTOR_H
#define CPPKIT_VECTOR_H
#include<vector>
#include <complex>
#include <cassert>
#include <iostream>
#include <list>

typedef std::complex<double> dcomplex;
typedef std::complex<float> fcomplex;

//template<class T>
//class Vector {
//public:
//
//    // trivial initializer
//    Vector() {}
//
//    // initialize list
//    Vector(std::list<T>& l) : data_(l) {}
//
//    //allocate number of elements
//    Vector(int n) : len(n), data_(0)
//    {}
//
//    // copy constructor
//    Vector(const Vector<T>& v) {
//        len=v.len;
//        data_=v.data_;
//    }
//
//    const T& operator()(int i,int j) const {
//        assert(i < len);
//        return data_[i];
//    }
//
//    T& operator()(int i) {
//        assert(i < len);
//        return data_[i];
//    }  // caller operator. returns a reference of that element
//
//    void print() {
//        std::cout.precision(8);
//        // std::cout << "shape:= (" << nrow << "," << ncol << ")" << std::endl;
//        for(int i=0; i < len; i++) {
//            std::cout << data_[i] << "\t";
//        }
//    }
//
//    void clear(){
//        for(int i=0; i < len; i++) {
//            data_[i] = 0.0;
//        }
//    }
//
//    void resize(int n) {
//        assert(n>0);
//        len=n;
//        data_.clear();
//        data_.resize(len);
//    }
//
//    inline int size() { return len;}
//
//    void fillRand();
//    void fill(T val) {
//        std::fill(data_.begin(),data_.end(),val);
//    }
//
//    int numNonZeros(){
//        int counter=0;
//        for(int i=0; i<data_.size(); i++)
//            if(data_[i]!=0.0) counter++;
//        return counter;
//    }
//
//    void del(){
//        len = 0;
//        data_.resize(0);
//    }
//
//    std::type_info type();
//
//    void conj()
//    {
//        int n = data_.size();
//        for (int i = 0; i < n; ++i)
//            data_[i] = std::conj(data_[i]);
//    }
//
//    Vector<T> operator + (const Vector<T>& B) {
//        return data_ + B.data_;
//    }
//    Vector<T> operator - (const Vector<T>& B) {
//        return data_ - B.data_;
//    }
//    Vector<T> operator * (const auto a) {
//        return data_ * a;
//    }
//    void operator += (const Vector<T>& B){
//        data_ += B;
//    }
//    void operator -= (const Vector<T>& B) {
//        data_ -= B;
//    }
//    void operator *= (const auto a) {
//        data_ *= a;
//    }
//
//    auto dot(Vector<T>& B) {
//        return dot(data_, B.data_);
//    }
//    auto cdot(Vector<T>& B) {
//        return cdot(data_, B.data_);
//    }
//
//private:
//    int len;
//    std::vector<T> data_;
//};
//
//// member functions



// ============================================================================
// =                          Declare Vector Scalar                           =
// ============================================================================
void vscal(const dcomplex& a, std::vector<dcomplex>& X);
void vscal(const fcomplex& a, std::vector<fcomplex>& X);
void vscal(const double& a, std::vector<double>& X);
void vscal(const float& a, std::vector<float>& X);

// ============================================================================
// =                           Declare Vector Norm                            =
// ============================================================================
double norm(const std::vector<dcomplex>& v);
float norm(const std::vector<fcomplex>& v);
double norm(const std::vector<double>& v);
float norm(const std::vector<float>& v);

// ============================================================================
// =                  Declare Vector Vector Multiplication                    =
// ============================================================================
// X dot Y
dcomplex dot(std::vector<dcomplex>& X, std::vector<dcomplex>& Y);
fcomplex dot(std::vector<fcomplex>& X, std::vector<fcomplex>& Y);
double dot(std::vector<double>& X, std::vector<double>& Y);
float dot(std::vector<float>& X, std::vector<float>& Y);

// X.conj dot Y
dcomplex cdot(std::vector<dcomplex>& X, std::vector<dcomplex>& Y);
fcomplex cdot(std::vector<fcomplex>& X, std::vector<fcomplex>& Y);


/*----------------End Declaration-----------------*/
// = Free functions: Vector rescale
template<class T>
std::vector<T> operator * (const std::vector<T>& X , const auto a) {
    T sa = static_cast<T>(a);  // from c++17
    std::vector<T> tmp(X);
    vscal(sa, tmp);
    return tmp;
}

template<class T>
void operator *= (std::vector<T>& X , const auto a) {
    T sa = static_cast<T>(a);
    vscal(sa, X);
}

// = Vector plus
template<class T>
std::vector<T> operator + (const std::vector<T>& X, const std::vector<T> &Y) {
    int n = X.size();
    assert(n == Y.size());
    std::vector<T> R(n);
    for (int i = 0; i < n; ++i) {
        R[i] = X[i] + Y[i];
    }
    return R;
}

template<class T>
void operator += (std::vector<T>& X, const std::vector<T> &Y) {
    int n = X.size();
    assert(n == Y.size());
    for (int i = 0; i < n; ++i) {
        X[i] = X[i] + Y[i];
    }
}

// = Vector minus
template<class T>
std::vector<T> operator - (const std::vector<T>& X, const std::vector<T> &Y) {
    int n = X.size();
    assert(n == Y.size());
    std::vector<T> R(n);
    for (int i = 0; i < n; ++i) {
        R[i] = X[i] - Y[i];
    }
    return R;
}

template<class T>
void operator -= (const std::vector<T>& X, const std::vector<T> &Y) {
    int n = X.size();
    assert(n == Y.size());
    for (int i = 0; i < n; ++i) {
        X[i] = X[i] - Y[i];
    }
}

#endif //CPPKIT_VECTOR_H
