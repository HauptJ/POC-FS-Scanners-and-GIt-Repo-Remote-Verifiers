//
// Created by josh on 1/21/26.
//

#ifndef POC_FS_SCANNERS_AND_GIT_REPO_REMOTE_VERIFIERS_FSSCANNER_H
#define POC_FS_SCANNERS_AND_GIT_REPO_REMOTE_VERIFIERS_FSSCANNER_H

#include <map>
#include <string>
#include <vector>

class rootDirScanner {
    std::string rootPath;
    std::vector<std::map<std::string, std::string>> validRemotes;
    std::vector<std::map<std::string, std::string>> invalidRemotes;
    std::vector<std::string> sourceCodeFiles;

public:
    rootDirScanner(std::string rootPath);
    static bool isSourceCodeFile(const std::string& filePath);
    std::vector<std::string> getSourceCodeFiles() const;
    std::vector<std::map<std::string, std::string>> getValidRemotes() const; // filePath, remoteUrl
    std::vector<std::map<std::string, std::string>> getInvalidRemotes() const; // filePath, remoteUrl
    std::string getRootPath() const;
    ~rootDirScanner();
};


#endif //POC_FS_SCANNERS_AND_GIT_REPO_REMOTE_VERIFIERS_FSSCANNER_H