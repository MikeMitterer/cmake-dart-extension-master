//
// Created by Mike Mitterer on 21.08.15.
//

#ifndef QTCMDLINE_NAME_H
#define QTCMDLINE_NAME_H


#include <iosfwd>
#include <string>

namespace test {

    class Name {
        const std::string name;

    public:
        //Name(const Name& name) = delete;
        Name(const Name &&name) = delete;

        Name(const std::string &name) : name(name) { }
    };

}

#endif //QTCMDLINE_NAME_H
