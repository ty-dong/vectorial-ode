//
// Created by Jiahua WU on 04.12.18.
//

// STL include
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstring>

// Local include
#include "../include/input.h"
using namespace std;

/// Usual Function Input module
Matrix Usual_Function_Input(){

    /// @param allparameters all the parameters of functions (sin, cos, exp, polynomial) all stored in this matrix.
    Matrix allparameters_choice;
    /// @param choice store the choice of every dimention of function g: 0 for sin, 1 for cos, 2 for exp, 3 for polynomial.
    Vector choice;
    ///@param the dimension of vector g(t)
    int dim;

    cout<<"Please input the dimension of your ODE"<<endl;
    cin>>dim;

    Vector dim_storer(1,dim);

    /// @param: vector storing the parameter of each component function
    Vector parameter(3,0);
    int tmp;
    int j(0);

    // Use do..while structure to avoid dimension mismatch caused by careless invalid input
    // Only valid input is taken into account
    do{
            cout<<"*************************"<<endl;
            cout<<"Please input your choice of function g (press Enter after the choice of every dimension)"<<endl;
            cout<<"0 a*sin(b*t+c)"<<endl;
            cout<<"1 a*cos(b*t+c)"<<endl;
            cout<<"2 a*exp(b*t+c)"<<endl;
            cout<<"3 a*t^2+b*t+c"<<endl;
            cout<<"4 terminate input process"<<endl;
            cout<<"If none of above meets your need, please define your function g in settings/user_defined_g.h"<<endl;
            cout<<"*************************"<<endl;

            cin>>tmp;
            choice.push_back(tmp);
            switch(tmp){
                case 0:
                    cout<<"Please input the parameters a,b and c of function: a*sin(b*t+c)"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters_choice.push_back(parameter);
                    ++j;
                    break;
                case 1:
                    cout<<"Please input the parameters a,b and c of function: a*cos(b*t+c)"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters_choice.push_back(parameter);
                    ++j;
                    break;
                case 2:
                    cout<<"Please input the parameters a,b and c of function: a*exp(b*t+c)"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters_choice.push_back(parameter);
                    ++j;
                    break;
                case 3:
                    cout<<"Please input the parameters a,b and c of function: a*t^2+b*t+c"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters_choice.push_back(parameter);
                    ++j;
                    break;
                case 4:
                    cerr<<"Program terminated!"<<endl;
                    j = dim;
                    break;
                default:
                    cerr<<"No matching function types!"<<endl;
            }
        } while (j < dim);
        allparameters_choice.push_back(choice);
        allparameters_choice.push_back(dim_storer);
    return allparameters_choice;
};


// Constructors
Reader::Reader(const string& path): path(path){}
Data_Reader::Data_Reader(const string& path, char delimiter): Reader(path),delimiter(delimiter){}
Vector_Reader::Vector_Reader(const string& path, char delimiter): Data_Reader(path, delimiter){}
Matrix_Reader::Matrix_Reader(const string &path, char delimiter): Data_Reader(path, delimiter){}
Setting_Reader::Setting_Reader(const string &path): Reader(path){}

// Destructors
Vector_Reader::~Vector_Reader() {y.resize(0);}
Matrix_Reader::~Matrix_Reader() {for (auto& vector: A) vector.resize(0); A.resize(0);}

// Accessors
Vector Vector_Reader::access_vector() const {return y;}
Matrix Matrix_Reader::access_matrix() const {return A;}
Setting Setting_Reader::access_setting() const {return setting;}

//Read in functions
void Vector_Reader::read_in() {
    ifstream read_file(path);
    while (!read_file.eof()) {
        string line;

        // Read the first line in s and end the loop if the file is empty
        if (!getline(read_file, line)) break;

        // Initialize an istream with s(first line of the document)
        istringstream ss(line);

        // Parse through ss(each loop corresponds to each line)
        while (ss) {
            string s;
            if (!getline(ss, s, delimiter)) break;
            y.push_back(stod(s));
        }
    }
    read_file.close();
}

void Matrix_Reader::read_in() {
    ifstream read_file(path);

    while (!read_file.eof()) {
        string line;

        // End the loop if the file is empty
        if (!getline(read_file, line)) break;

        istringstream ss(line);
        vector<double> record;
        while (ss){
            string s;
            if (!getline(ss, s, delimiter)) break;
            record.push_back(stod(s));
        }
        A.push_back(record);
    }
    read_file.close();
}

void Setting_Reader::read_in() {
    ifstream read_file(path);
    string value;
    string parameter;
    string tmp;

    while (!read_file.eof()) {

        string line;
        // Read the first line in s and end the loop if the file is empty
        if (!getline(read_file, line)) break;

        // Initialize an istream with s(first line of the document)
        istringstream ss(line);

        // Parse through ss
        getline(ss, parameter, ' ');
        getline(ss, tmp, '=');
        getline(ss, value, '#');


        // Remove space in the string
        value.erase(remove(value.begin(), value.end(), ' '), value.end());
        parameter.erase(remove(parameter.begin(), parameter.end(), ' '), parameter.end());

        if (parameter == "t0") setting.t0 = stod(value);
        else if (parameter == "tn") setting.tn = stod(value);
        else if (parameter == "path_y00") setting.path_y00 = value;
        else if (parameter == "path_A") setting.path_A = value;
        else if (parameter == "number_of_steps") setting.M = stoi(value);
        else if (parameter == "path_solution") setting.path_solution = value;
        else if (parameter == "precision") setting.precision = stoi(value);
        else if (parameter == "M") setting.M = stoi(value);
        else if (parameter == "usual_function") setting.usual_function = stoi(value);

        // Convert string into char
        else if (parameter == "delimiter_solution") {
            char char_array[10];
            strcpy(char_array,value.c_str());
            setting.delimiter_solution = char_array[0];
        }
        else if (parameter == "delimiter_data") {
            char char_array[10];
            strcpy(char_array,value.c_str());
            setting.delimiter_data = char_array[0];
        }
        else cerr << "Invalid Input\n";
    }
read_file.close();
}
