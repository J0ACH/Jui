#include <iostream>
#include "Student.h"
using namespace std;

Student::Student(QString name) : jmeno(name) {}

void Student::display(){
  cout << "Hi from test qstring library. Im a student with name " << this->jmeno.toStdString() << endl;
}