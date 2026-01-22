//
// Created by josh on 1/21/26.
//

#ifndef POC_FS_SCANNERS_AND_GIT_REPO_REMOTE_VERIFIERS_GITREPOUTIL_H
#define POC_FS_SCANNERS_AND_GIT_REPO_REMOTE_VERIFIERS_GITREPOUTIL_H

#include <string>
#include <vector>
#include <map>

class gitrepoutil {

    std::string repoPath;
    std::vector<std::map<std::string, std::string>> remotes = {}; // name, URL
    bool isValidRemote = NULL;

public:
    gitrepoutil(std::string repoPath);

    std::vector<std::map<std::string, std::string>> getRemotes() const;

    static bool verifyRemoteURL(std::string remoteURL);
    bool getIsValidRemote() const;
    std::string getRepoPath() const;

    ~gitrepoutil();
};


#endif //POC_FS_SCANNERS_AND_GIT_REPO_REMOTE_VERIFIERS_GITREPOUTIL_H