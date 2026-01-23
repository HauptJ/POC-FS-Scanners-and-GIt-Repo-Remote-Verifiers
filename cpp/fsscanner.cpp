//
// Created by josh on 1/21/26.
//

#include <filesystem>
#include "fsscanner.h"
#include "gitrepoutil.cpp"
#include <map>
#include <string>

bool fsscanner::isSourceCodeFile(const std::string &filePath) {
    if (filePath.empty()) {
        return false;
    }
    const std::vector<std::string> sourceFileExtensions = {
        ".c", ".cpp", ".h", ".hpp", ".java", ".py", ".js", ".ts", ".cs", ".rb", ".go", ".rs"
};
    for (const auto &ext: sourceFileExtensions) {
        if (filePath.size() >= ext.size() &&
            filePath.compare(filePath.size() - ext.size(), ext.size(), ext) == 0) {
            // 0 == true / found
            return true;
            }
    }
    return false;
}

fsscanner::fsscanner(std::string rootPath) {
    //printf("Starting scanner\n");
    this->rootPath = rootPath;
    for (const auto &entry: std::filesystem::recursive_directory_iterator(rootPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            //printf("Checking file: %s\n", filePath.c_str());
            if (isSourceCodeFile(filePath)) {
                //printf("Found source code file: %s\n", filePath.c_str());
                this->sourceCodeFiles.push_back(filePath);
            }
        }
        if (entry.is_directory() && entry.path().filename() == ".git") {
            std::string repoPath = entry.path().string();
            //printf("Checking git repo: %s\n", repoPath.c_str());
            gitrepoutil gitUtil(repoPath);
            std::vector<std::map<std::string, std::string>> remotes = gitUtil.getRemotes();
            for (const auto &remote : remotes) {
                for (const auto& [key, value] : remote) {
                    //printf("Checking remote key: %s value: %s\n", key.c_str(), value.c_str());
                    std::map<std::string, std::string> remoteBuilder = {{gitUtil.getRepoPath(), value}};
                    if (gitUtil.getIsValidRemote()) {
                        this->validRemotes.push_back(remoteBuilder);
                    } else {
                        this->invalidRemotes.push_back(remoteBuilder);
                    }
                }
            }
        }
    }
    //printf("Scanning finished\n");
}

std::vector<std::string> fsscanner::getSourceCodeFiles() const {
    return this->sourceCodeFiles;
}

std::vector<std::map<std::string, std::string>> fsscanner::getValidRemotes() const {
    return this->validRemotes;
}

std::vector<std::map<std::string, std::string>> fsscanner::getInvalidRemotes() const {
    return this->invalidRemotes;
}

fsscanner::~fsscanner() {

}
