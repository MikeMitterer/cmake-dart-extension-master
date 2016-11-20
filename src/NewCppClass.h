//
// Created by Mike Mitterer on 08.08.15.
//

#ifndef QTCMDLINE_NEWCPPCLASS_H
#define QTCMDLINE_NEWCPPCLASS_H


#include <iosfwd>
#include <string>

class NewCppClass {
private:
    const std::string name;

public:
    NewCppClass(const std::string &name) : name{name} { }

    void showName();
};


#endif //QTCMDLINE_NEWCPPCLASS_H
