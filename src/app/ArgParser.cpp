//
// Created by Mike Mitterer on 08.08.15.
//

#include <qmap.h>
#include <iostream>
#include "ArgParser.h"

void ArgParser::setup() {
    parser.setApplicationDescription(title);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to copy."));
    parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Destination directory."));

    // A boolean option with a single name (-p)
    options.insert(Option::showProgress,
             QCommandLineOption("p", QCoreApplication::translate("main", "Show progress during copy")));

    // A boolean option with multiple names (-f, --force)
    options.insert(Option::force,
                   QCommandLineOption({"f", "force"}, QCoreApplication::translate("main", "Overwrite existing files.")));

//    // A boolean option with multiple names (-t, --test)
//    options.insert(Options::showTest,
//        QCommandLineOption({"t", "test"}, QCoreApplication::translate("test", "Show test-output!")));
//
//    // An option with a value
//    options.insert(Options::targetDir,
//        QCommandLineOption({"t", "target-directory"},
//                                   QCoreApplication::translate("main", "Copy all source files into <directory>."),
//                                   QCoreApplication::translate("main", "directory")));

    parser.addOptions(options.values());
}

void ArgParser::process() {
    parser.process(application);

    const QStringList args = parser.positionalArguments();
    const QStringList options = parser.optionNames();

//    if (args.length() < 1) {
//        parser.showHelp(0);
//    }

//    for(auto option : options) {
//        std::cout << option.toStdString() << std::endl;
//    }

}

bool ArgParser::showProgress() {
    const QCommandLineOption option = options.values(Option::showProgress).first();
    return parser.isSet(option);
}
