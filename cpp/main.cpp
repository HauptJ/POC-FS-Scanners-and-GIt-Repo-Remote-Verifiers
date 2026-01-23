//
// Created by josh on 1/21/26.
//

#include <stdio.h>
#include <stdexcept>
#include <string>
//#include "gitRepoUtil.cpp" // Uncomment if compiling allTests.cpp
#include "rootDirScanner.cpp"

int main(int argc, char* argv[]) {

    try {
        if (argc == 1) {
            throw std::runtime_error("Usage: gitUtil.getRepository.*");
        }
        if (argc > 1) {
            printf("Number of root repositories to check: %d\n", argc - 1);

            for (int i = 1; i < argc; i++) {
                std::string repoPath = argv[i];
                printf("Checking root directory: %s\n", repoPath.c_str());
                rootDirScanner scanner(repoPath);
                std::vector<std::map<std::string, std::string>> invalidRemotes = scanner.getInvalidRemotes();
                for (const auto& remote : invalidRemotes) {
                    for (const auto& [key, value] : remote) {
                        printf("Invalid remote found: %s -> %s\n", key.c_str(), value.c_str());
                    }
                }
                std::vector<std::map<std::string, std::string>> validRemotes = scanner.getValidRemotes();
                for (const auto& remote : validRemotes) {
                    for (const auto& [key, value] : remote) {
                        printf("Valid remote found: %s -> %s\n", key.c_str(), value.c_str());
                    }
                }
                std::vector<std::string> sourceCodeFiles = scanner.getSourceCodeFiles();
                for (const auto& filePath : sourceCodeFiles) {
                    printf("Source code file found: %s\n", filePath.c_str());
                }
            }
        }
    } catch (std::exception& e) {
        printf("Error: %s\n", e.what());
        return 1;
    }
    return 0;
}