//
// Created by Mike Mitterer on 08.08.15.
//

#ifndef QTCMDLINE_ARGPARSER_H
#define QTCMDLINE_ARGPARSER_H

#include <qcoreapplication.h>
#include <functional>
#include <QtCore/qcommandlineparser.h>
#include "test/Name.h"

using namespace std;
//namespace cpptest = test;

class ArgParser {
    enum class Option {
        showProgress = 0, force = 1, showTest = 2, targetDir = 3
    };

    QCommandLineParser parser;
    QMap<Option, QCommandLineOption> options;

    const cpptest::Name& name;
    const QCoreApplication& application;
    const QString title;

public:

    //ArgParser() = delete;
    ArgParser(const QCoreApplication &app, const QString &title, const cpptest::Name& name) :
            application(app), title(title),name(name) { setup(); }

    void process();

    // Test for Lambda-Function
    std::function<bool()> isForce = [this]() -> bool {
        return parser.isSet(options.values(Option::force).first());
    };

    bool showProgress();

private:
    void setup();
};


#endif //QTCMDLINE_ARGPARSER_H
