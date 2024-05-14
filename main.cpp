#include "mainscene.h"
#include "config.h"
#include<QResource>
#include <QApplication>
#include "scene.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainscene w;
    Scene new_w(&w);
    new_w.show();
    new_w.setFocus();
    return a.exec();
}
