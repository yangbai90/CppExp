//****************************************************************
//* This file is part of the AsFem framework
//* A Simple Finite Element Method program (AsFem)
//* All rights reserved, Yang Bai @ CopyRight 2020
//* https://github.com/yangbai90/AsFem.git
//* Licensed under GNU GPLv3, please see LICENSE for details
//* https://www.gnu.org/licenses/gpl-3.0.en.html
//****************************************************************

#ifndef ASFEM_RANKTWOTENSOR_H
#define ASFEM_RANKTWOTENSOR_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>




using namespace std;

class RankFourTensor;

class RankTwoTensor{
public:
    RankTwoTensor();
    RankTwoTensor(const double &val);
    RankTwoTensor(const RankTwoTensor &a);
    enum InitMethod{
        InitZero,
        InitIdentity
    };
    RankTwoTensor(const InitMethod &method);
    
    // set from voigt notation
    RankTwoTensor(const double &v11,const double &v22,const double &v12);// for 2d voigt
    RankTwoTensor(const double &v11,const double &v22,const double &v33,
                  const double &v23,const double &v31,const double &v12);// for 3d voigt
    // set from full input
    RankTwoTensor(const double &v11,const double &v12,
                  const double &v21,const double &v22);// for 2d all elements
    RankTwoTensor(const double &v11,const double &v12,const double &v13,
                  const double &v21,const double &v22,const double &v23,
                  const double &v31,const double &v32,const double &v33);// for 3d all elements

    
    inline int GetDim() const {return _N;}
    //*******************************************************************
    //*** Operator overload
    //*******************************************************************
    inline double operator()(const int &i,const int &j) const{
        return _vals[(i-1)*_N+j-1];
    }
    inline double& operator()(const int &i,const int &j){
        return _vals[(i-1)*_N+j-1];
    }
    inline double operator[](const int &i) const{
        return _vals[i-1];
    }
    inline double& operator[](const int &i){
        return _vals[i-1];
    }
    //***********************
    //*** for = operator
    //***********************
    inline RankTwoTensor& operator=(const double &a){
        for(int i=0;i<_N2;++i) _vals[i]=a;
        return *this;
    }
    inline RankTwoTensor& operator=(const RankTwoTensor &a){
        for(int i=0;i<_N2;++i) _vals[i]=a._vals[i];
        return *this;
    }
    // RankTwoTensor& operator=(RankTwoTensor &a)=default;
    // RankTwoTensor& operator=(const RankTwoTensor &a)=default;
    // RankTwoTensor& operator=(const RankTwoTensor &&a)=delete;
    // RankTwoTensor& operator=(RankTwoTensor &&a)=delete;

    //***********************
    //*** for + operator
    //***********************
    inline RankTwoTensor operator+(const double &a) const{
        RankTwoTensor temp(0.0);
        for(int i=0;i<_N2;++i) temp._vals[i]=_vals[i]+a;
        return temp;
    }
    inline RankTwoTensor operator+(const RankTwoTensor &a) const{
        RankTwoTensor temp(0.0);
        for(int i=0;i<_N2;++i) temp._vals[i]=_vals[i]+a._vals[i];
        return temp;
    }
    //*** for += operator
    inline RankTwoTensor& operator+=(const double &a) {
        for(int i=0;i<_N2;++i) _vals[i]+=a;
        return *this;
    }
    inline RankTwoTensor& operator+=(const RankTwoTensor &a){
        for(int i=0;i<_N2;++i) _vals[i]+=a._vals[i];
        return *this;
    }
    //**********************
    //*** for - operator
    //**********************
    inline RankTwoTensor operator-(const double &a) const{
        RankTwoTensor temp(0.0);
        for(int i=0;i<_N2;++i) temp._vals[i]=_vals[i]-a;
        return temp;
    }
    inline RankTwoTensor operator-(const RankTwoTensor &a) const{
        RankTwoTensor temp(0.0);
        for(int i=0;i<_N2;++i) temp._vals[i]=_vals[i]-a._vals[i];
        return temp;
    }
    //*** for -= operator
    inline RankTwoTensor& operator-=(const double &a) {
        for(int i=0;i<_N2;++i) _vals[i]-=a;
        return *this;
    }
    inline RankTwoTensor& operator-=(const RankTwoTensor &a){
        for(int i=0;i<_N2;++i) _vals[i]-=a._vals[i];
        return *this;
    }
    //**********************
    //*** for * operator
    //**********************
    inline RankTwoTensor operator*(const double &a) const{
        RankTwoTensor temp(0.0);
        for(int i=0;i<_N2;++i) temp._vals[i]=_vals[i]*a;
        return temp;
    }
    //*** for left hand side scalar times rank-2 tensor
    friend RankTwoTensor operator*(const double &lhs,const RankTwoTensor &a);
    //*** for left hand vector times rank-2 tensor
    
    inline RankTwoTensor operator*(const RankTwoTensor &a) const{
        // return A*B(still rank-2 tensor)
        RankTwoTensor temp(0.0);
        for(int i=1;i<=_N;++i){
            for(int j=1;j<=_N;++j){
                temp(i,j)=0.0;
                for(int k=1;k<=_N;++k){
                    temp(i,j)+=(*this)(i,k)*a(k,j);
                    // temp(i,j)+=(*this)(k,i)*a(k,j);
                }
            }
        }
        return temp;
    }
    inline void VectorCrossDot(const double (&a)[3],const double (&b)[3]){
        for(int i=1;i<=_N;++i){
            for(int j=1;j<=_N;++j){
                (*this)(i,j)=a[i-1]*b[j-1];
            }
        }
    }
    inline void VectorCrossDot(const vector<double> &a,const vector<double> &b){
        for(int i=1;i<=_N;++i){
            for(int j=1;j<=_N;++j){
                (*this)(i,j)=a[i-1]*b[j-1];
            }
        }
    }
    
    inline double DoubleDot(const RankTwoTensor &a) const{
        // return A:B calculation
        double sum=0.0;
        for(int i=1;i<=_N;++i){
            for(int j=1;j<=_N;++j){
                // J.N. Reddy use A_ijB_ji
                sum+=(*this)(i,j)*a(i,j);// use this to get the positive definite scale!!!
            }
        }
        return sum;
    }
    //*** for *= operator
    inline RankTwoTensor& operator*=(const double &a) {
        for(int i=0;i<_N2;++i) _vals[i]*=a;
        return *this;
    }
    RankTwoTensor& operator*=(const RankTwoTensor &a){
        RankTwoTensor temp=(*this)*a;
        (*this)=temp;
        return *this;
    }
    //****************
    //*** /
    //****************
    inline RankTwoTensor operator/(const double &a) const{
        RankTwoTensor temp(0.0);
        for(int i=0;i<_N2;++i) temp._vals[i]=_vals[i]/a;
        return temp;
    }
     inline RankTwoTensor& operator/=(const double &a){
        for(int i=0;i<_N2;++i) _vals[i]=_vals[i]/a;
        return *this;
    }
    //********************************************************
    //**** other mathematic related functions
    //********************************************************
    inline double Trace() const{
        return (*this)(1,1)+(*this)(2,2)+(*this)(3,3);
    }
    inline double Det() const{
        // taken from http://mathworld.wolfram.com/Determinant.html
        // Eq.10
        return (*this)(1,1)*(*this)(2,2)*(*this)(3,3)
              -(*this)(1,1)*(*this)(2,3)*(*this)(3,2)
              -(*this)(1,2)*(*this)(2,1)*(*this)(3,3)
              +(*this)(1,2)*(*this)(2,3)*(*this)(3,1)
              +(*this)(1,3)*(*this)(2,1)*(*this)(3,2)
              -(*this)(1,3)*(*this)(2,2)*(*this)(3,1);
    }
    //*** for the different invariants of stress(strain)
    inline double FirstInvariant() const{
        return Trace();
    }
    inline double SecondInvariant() const{
        double trAA=((*this)*(*this)).Trace();
        double trA=Trace();
        return 0.5*(trA*trA-trAA);
    }
    inline double ThirdInvariant() const{
        return Det();
    }
    //*** for inverse
    inline RankTwoTensor Inverse() const{
        double J=Det();
        if(abs(J)<1.0e-15){
            cout<<"*** Error: inverse failed for a singular rank-2 tensor          !!!   ***\n";
            abort();
        }
        RankTwoTensor inv(0.0);
        // taken from wiki:
        //   https://en.wikipedia.org/wiki/Invertible_matrix
        double A= (*this)(2,2)*(*this)(3,3)-(*this)(2,3)*(*this)(3,2);
        double D=-(*this)(1,2)*(*this)(3,3)+(*this)(1,3)*(*this)(3,2);
        double G= (*this)(1,2)*(*this)(2,3)-(*this)(1,3)*(*this)(2,2);
        inv(1,1)=A/J;inv(1,2)=D/J;inv(1,3)=G/J;

        double B=-(*this)(2,1)*(*this)(3,3)+(*this)(2,3)*(*this)(3,1);
        double E= (*this)(1,1)*(*this)(3,3)-(*this)(1,3)*(*this)(3,1);
        double H=-(*this)(1,1)*(*this)(2,3)+(*this)(1,3)*(*this)(2,1);
        inv(2,1)=B/J;inv(2,2)=E/J;inv(2,3)=H/J;

        double C= (*this)(2,1)*(*this)(3,2)-(*this)(2,2)*(*this)(3,1);
        double F=-(*this)(1,1)*(*this)(3,2)+(*this)(1,2)*(*this)(3,1);
        double I= (*this)(1,1)*(*this)(2,2)-(*this)(1,2)*(*this)(2,1);
        inv(3,1)=C/J;inv(3,2)=F/J;inv(3,3)=I/J;
        return inv;
    }
    inline RankTwoTensor Transpose() const{
        RankTwoTensor temp(0.0);
        for(int i=1;i<=_N;++i){
            for(int j=1;j<=_N;++j){
                temp(i,j)=(*this)(j,i);
            }
        }
        return temp;
    }
    //********************************************************
    //**** For stress and strain decomposition
    //********************************************************
    //*******************************************************************
    //*** some setting functions
    //*******************************************************************
    inline void SetToZeros(){
        for(int i=0;i<_N2;++i) _vals[i]=0.0;
    }
    inline void SetToIdentity(){
        for(int i=1;i<=_N;++i){
            for(int j=1;j<=_N;++j){
                if(i==j){
                    (*this)(i,j)=1.0;
                }
                else{
                    (*this)(i,j)=0.0;
                }
            }
        }
    }
    // for deformation gradient based calculation(or similar calculation)
    void SetFromVoigt(const double &v11,const double &v22,const double &v12);// for 2D
    void SetFromVoigt(const double &v11,const double &v22,const double &v33,
                      const double &v23,const double &v31,const double &v12);// for 3D
    //********************************************************
    //**** For rotation tensor
    //********************************************************
    void SetFromEulerAngle(const double &theta1,const double &theta2,const double &theta3);
    //*******************************************************************
    //*** Print functions
    //*******************************************************************
    inline void Print() const{
        printf("*** %14.6e    %14.6e    %14.6e     ***\n",(*this)(1,1),(*this)(1,2),(*this)(1,3));
        printf("*** %14.6e    %14.6e    %14.6e     ***\n",(*this)(2,1),(*this)(2,2),(*this)(2,3));
        printf("*** %14.6e    %14.6e    %14.6e     ***\n",(*this)(3,1),(*this)(3,2),(*this)(3,3));
    }

    
private:
    const int _N=3;
    const int _N2=9;
    double _vals[9];
};


#endif // ASFEM_RANKTWOTENSOR_H