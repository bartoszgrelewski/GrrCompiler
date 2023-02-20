#include <iostream>
#include <fstream>

extern std::string parse(FILE *in);

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 3)
    {
        std::cout << "incorrect number of arguments, valid run arguments:" << std::endl;
        std::cout << "./compiler <input file> <output file>" << std::endl;
        std::cout << "./compiler <input file>" << std::endl;
        return -1;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == nullptr)
    {
        std::cout << "file " << argv[1] << " does not exist" << std::endl;
        return -2;
    }

    std::string code = parse(in);

    std::string out = "out";
    if (argv[2] != nullptr)
    {
        out = argv[2];
    }

    std::ofstream binary(out);
    binary << code;
    binary.close();

    return 0;
}