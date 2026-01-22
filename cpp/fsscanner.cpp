//
// Created by josh on 1/21/26.
//

#include <filesystem>
#include "fsscanner.h"
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
            // 0 == true
            return true;
            }
    }
    return false;
}

fsscanner::fsscanner(std::string rootPath) {
    this->rootPath = rootPath;
    for (const auto &entry: std::filesystem::recursive_directory_iterator(rootPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            if (isSourceCodeFile(filePath)) {
                this->sourceCodeFiles.push_back(filePath);
            }
        }
        if (entry.is_directory() && entry.path().filename() == ".git") {
            std::string repoPath = entry.path().string();
            gitrepoutil gitUtil(repoPath);
            std::vector<std::map<std::string, std::string>> remotes = gitUtil.getRemotes();
            for (const auto &remote : remotes) {
                for (const auto& [key, value] : remote) {
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
