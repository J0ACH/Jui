#include<string>
#include<QString>

class Student{
private:
  QString jmeno;
public:
  Student(QString);
  //Student(std::string);
  //Student(char);
  virtual void display();
};