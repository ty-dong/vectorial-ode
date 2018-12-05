//
// Created by Jiahua WU on 04.12.18.
//

#ifndef ODE_SOLVER_INPUT_H
#define ODE_SOLVER_INPUT_H

#include "ODE_solver.h"
#include <string>
using namespace std;

/// Structure storing parameters read from the setting file
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


///Abstract class of readers
class Reader{

protected:
    /// \brief Path of the file to be read
    string path;

public:

    /// \brief Constructor. Initialize the attribute path with the path given
    explicit Reader(const string& path);

    /// \brief Pure virtual function for reading in from files.
    virtual void read_in() = 0;
};

/// Inheritance of class Reader which specializes in reading data from files
class Data_Reader : public Reader{
protected:

    /// \brief delimiter used in the file to be read
    char delimiter;

public:

    /// \brief Constructor. Initialize the attributes with the input path and delimiter
    Data_Reader(const string& path,char delimiter);
    /// \brief Default destructor to be override
    virtual ~Data_Reader() = default;
};

/// Inheritance of class Data_Reader which specializes in reading files storing a vector
class Vector_Reader : public Data_Reader{
protected:
    /// \brief Vector read from the file
    Vector y;

public:

    /// \brief Constructor. Initialize data structure with the input arguments
    Vector_Reader(const string& path,char delimiter = ' ');

    /// \brief Destructor. Deallocate the memory used by the vector attribute.
    ~Vector_Reader() override;

    /// \brief Accessor. Access the vector read from the file
    Vector access_vector() const;

    /// \brief Read the file from the path attribute and assign it to the vector attribute
    void read_in() override;

};

/// Inheritance of class Data_Reader which specializes in reading files storing a matrix
class Matrix_Reader : public Data_Reader{
protected:

    /// \brief Matrix read from the file
    Matrix A;

public:
    /// \brief Constructor. Initialize data structure with the input arguments
    Matrix_Reader(const string& path, char delimiter = ' ');

    /// \brief Destructor. Deallocate the memory used by the Matrix attribute
    ~Matrix_Reader() override;

    /// \brief Accessor. Access the matrix read from the file
    Matrix access_matrix() const;

    /// \brief Read the file from the path attribute and assign it to the matrix attribute
    void read_in() override;

};

/// Inheritance of class Reader specialized in reading the setting file
class Setting_Reader : public Reader{
protected:
    /// \brief Attribute that stores the parameters read from the setting file
    Setting setting;

public:

    /// \brief Constructor. Initialize the attributes with the input argument
    explicit Setting_Reader(const string& path);

   /// \brief Accessor. Provide access to the setting parameters
    Setting access_setting() const;

    /// \brief Read the file from the path attribute and assign it to the setting attribute
    void read_in() override;

};


#endif //ODE_SOLVER_INPUT_H
