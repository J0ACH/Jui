
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv); 

  QLabel text( QString("Pozdrav od Jachyma"));
  text.setGeometry(100, 100, 300, 50);
  text.show(); 

  return app.exec();
}


