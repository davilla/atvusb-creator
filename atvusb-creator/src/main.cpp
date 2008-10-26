#include <iostream>
#include <QtGui/QApplication>

#include "aucDialog.h"
int main(int argc, char** argv){
	QApplication application( argc, argv );       

  aucDialog dialog;
  dialog.show();
	return application.exec();
}