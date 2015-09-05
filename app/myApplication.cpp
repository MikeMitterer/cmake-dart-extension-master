#include <QApplication>
#include <qcommandlineparser.h>
#include <iostream>
#include "interface/MainWindow.hpp"
#include <Qdebug>
#include <dart/extension/include/SampleProject.h>
#include <dart/extension/src/NewCppClass.h>
#include <src/app/ArgParser.h>

using namespace std;

/**
 * Here is my Main!
 */
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("my-copy-program");
    QCoreApplication::setApplicationVersion("1.0");

    const cpptest::Name name{"Mike"};
    ArgParser parser{app,"Dart Master",name};
    parser.process();

    //ArgParser p2{};

    qWarning() << "Test Debug";
    SampleProject sampleProject;
    sampleProject.function();

    NewCppClass newCppClass("Mike");
    newCppClass.showName();

    auto newCppClass1 = unique_ptr<NewCppClass>(new NewCppClass("Gerda"));
    newCppClass1->showName();

    cout << "Hallo" << endl;

    if(parser.showProgress()) {
        cout << "test" << endl;
        qWarning() << "Show progress Mike";
    }

    if(parser.isForce()) {
        cout << "LambdaTEST (rForce)" << endl;
    }

//    if(args.length() <= 1) {
//        parser.showHelp(0);
//    }
//
//    const bool showProgress = parser.isSet(options[Options::showProgress]);
//    const bool force        = parser.isSet(options[Options::force]);
//    const bool showTest     = parser.isSet(options[Options::showTest]);
//    const QString targetDir = parser.value(options[Options::targetDir]);

    exit(0);
}
