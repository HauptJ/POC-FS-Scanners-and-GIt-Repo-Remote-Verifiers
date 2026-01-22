//
// Created by josh on 1/21/26.
//

#include "gitrepoutil.h"

#include <vector>
#include <git2.h>
#include <stdexcept>
#include <string>

bool gitrepoutil::verifyRemoteURL(const std::string remoteURL) {
    if (!remoteURL.empty() && remoteURL.contains("github.com")) {
        return true;
    }
    return false;
}

gitrepoutil::gitrepoutil(std::string repoPath) {
    this->repoPath = repoPath;

    try {
        if (git_libgit2_init() < 0) {
            throw std::runtime_error("Failed to initialize libgit2");
        }

        git_repository *repo = nullptr;
        int error = git_repository_open(&repo, repoPath.c_str());
        if (error < 0) {
            const git_error* e = git_error_last();
            if (error == GIT_ENOTFOUND) {
                throw std::runtime_error("Repository not found at path: " + repoPath);
            } if (error == GIT_EINVALIDSPEC) {
                throw std::runtime_error("EC: " + std::to_string(error) + "Invalid repository specification at path: " + repoPath);
            } if (error == GIT_EINVALID) {
                throw std::runtime_error("EC: " + std::to_string(error) + "Invalid repository at path: " + repoPath);
            } else {
                throw std::runtime_error("EC: " + std::to_string(error) + " Failed to open repository: " + std::string(e->message));
            }
        }

        git_strarray remoteNames = {0};
        error = git_remote_list(&remoteNames, repo);
        if (error < 0) {
            const git_error *e = git_error_last();
            printf("Error %d getting remotes repository: %s\n", error, e->message);
            throw std::runtime_error("EC: " + std::to_string(error) + " Failed to get remotes open repo: " + std::string(e->message));
        }

        for (int i = 0; i < remoteNames.count; ++i) {
            const char *remoteName = remoteNames.strings[i];
            git_remote *remote = nullptr;
            error = git_remote_lookup(&remote, repo, remoteName);
            if (error < 0) {
                const git_error *e = git_error_last();
                printf("Error %d looking up remote %s: %s\n", error, remoteName, e->message);
                throw std::runtime_error("EC: " + std::to_string(error) + " Failed to lookup remote " + std::string(remoteName) + ": " + std::string(e->message));
            }

            const char *url = git_remote_url(remote);
            std::string remoteUrl = url ? url : "";
            std::map<std::string, std::string> remoteVal = {
                    {std::string(remoteName), std::string(url)}};
            this->remotes.push_back(remoteVal);

            git_remote_free(remote);
            git_libgit2_shutdown();

            this->isValidRemote = verifyRemoteURL(remoteUrl);
        }

    } catch (const std::runtime_error &e) {
        git_libgit2_shutdown();
        throw std::runtime_error(e);
    }
}

bool gitrepoutil::getIsValidRemote() const {
    if (this->isValidRemote == true || this->isValidRemote == false) {
        return this->isValidRemote;
    }
    return this->isValidRemote;
}

gitrepoutil::~gitrepoutil() {

}