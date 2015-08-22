//
// Created by Mike Mitterer on 08.08.15.
//

#include "SampleProject.h"

#include <iostream>

SampleProject::SampleProject() {
    std::cout << "SampleProject::SampleProject()7777" << std::endl;
}

SampleProject::~SampleProject() {
    std::cout << "SampleProject::~SampleProject2()" << std::endl;
}

void SampleProject::function() {
    std::cout << "SampleProject::function()" << std::endl;
}