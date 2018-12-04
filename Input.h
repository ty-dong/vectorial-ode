//
// Created by Jiahua WU on 04.12.18.
//

#ifndef ODE_SOLVER_INPUT_H
#define ODE_SOLVER_INPUT_H

#include "ODE_solver.h"
#include <string>
using namespace std;

struct Setting{
    int M;
    int precision = 5;
    Real t0;
    Real tn;
    string path_y00;
    string path_A;
    string name_of_solution;
    string function_type;
    char delimiter_data = ' ';
    char delimiter_solution = ',';
};

class Reader{
protected:
    string path;

public:
    explicit Reader(const string& path);
    virtual void read_in() = 0;
};

class Data_Reader : public Reader{
protected:
    char delimiter;

public:
    Data_Reader(const string& path,char delimiter);
    virtual ~Data_Reader() = default;
};

class Vector_Reader : public Data_Reader{
protected:
    Vector y;

public:
    Vector_Reader(const string& path,char delimiter = ' ');
    ~Vector_Reader() override;

    Vector access_vector() const;

    void read_in() override;

};

class Matrix_Reader : public Data_Reader{
protected:
    Matrix A;

public:
    Matrix_Reader(const string& path, char delimiter = ' ');
    ~Matrix_Reader() override;

    Matrix access_matrix() const;

    void read_in() override;

};

class Setting_Reader : public Reader{
protected:
    Setting setting;

public:
    explicit Setting_Reader(const string& path);

    Setting access_setting() const;
    void read_in() override;

};


#endif //ODE_SOLVER_INPUT_H
