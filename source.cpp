#include <fstream>
#include <iostream>
#include <getopt.h>

int main(int argc, char *argv[]) {
    struct option long_options[] = {
        {"source_file", required_argument, 0, 's'},
        {"destination_file", required_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    std::string sourceFile;
    std::string destinationFile;

    int opt;
    while ((opt = getopt_long(argc, argv, "s:d:", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                sourceFile = optarg;
                break;
            case 'd':
                destinationFile = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " --source_file filename --destination_file filename\n";
                return 1;
        }
    }

    std::ifstream inFile(sourceFile.c_str(), std::ios::binary | std::ios::ate);
    if (!inFile) {
        std::cerr << "Unable to open source file.\n";
        return 1;
    }

    std::ofstream outFile(destinationFile.c_str(), std::ios::binary);
    if (!outFile) {
        std::cerr << "Unable to open destination file.\n";
        return 1;
    }

    std::streampos fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    for (std::streamoff i = 0; i < fileSize; ++i) {
        inFile.seekg(-1 - i, std::ios::end);
        char c;
        inFile.get(c);
        outFile.put(c);
    }

    inFile.close();
    outFile.close();
    return 0;
}