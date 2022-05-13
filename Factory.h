#pragma once
#include "figure.h"

class Factory {
    Vector a1_a2_a3_c[4];
public:
    void set(Vector v,unsigned int p){
        if (p < 4) {
            a1_a2_a3_c[p] = v;
        }
        else {
            cout << "factory set index fail";
        }
    }
    Vector get(unsigned int p) {
        if (p < 4) {
            return a1_a2_a3_c[p];
        }
        else {
            cout << "factory index fail";  
        }
       return  a1_a2_a3_c[1];
    }
    virtual figure* Create(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) = 0;
};

class Factory_sphere : public Factory {
public:
    figure* Create(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) override {
        return new sphere(c,a1,a2,a3,a0);
    }
};

class Factory_parallelepiped : public Factory {
public:
    figure* Create(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) override {
        return new parallelepiped(c, a1, a2, a3, a0);
    }
};

class Factory_tetrahedron : public Factory {
public:
    figure* Create(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) override {
        return new tetrahedron(c, a1, a2, a3, a0);
    }
};

