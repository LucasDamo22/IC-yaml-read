#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Processor.h"
#include "Helper-functions.h"
#define RYML_SINGLE_HDR_DEFINE_NOW
#include "ryml_all.hpp"

int main(int argc, char** argv)
{

    Processor cpu1 = Processor();
    Processor cpu2 = Processor();
    std::string contents = get_file_contents(argv[1]);
    ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(contents));

    ryml::NodeRef processos = tree["Processos"];
    for (ryml::NodeRef const &child : processos.children())
    {
        double aux, min, max;
        std::stringstream ss; // using sstream to convert from csubstr to double
        ss << child[0].val();
        ss >> min;
        ss.clear();
        ss << child[1].val();
        ss >> max;
        ss.clear();

        aux = min / max;

        if (cpu2.get_coef() > cpu1.get_coef())
        {
            cpu1.add_process(aux);
        }
        else
        {
            cpu2.add_process(aux);
        }
    }

    std::cout << "cpu1 coef: " << cpu1.get_coef() << std::endl;
    std::cout << "cpu2 coef: " << cpu2.get_coef() << std::endl;
    return 0;
}