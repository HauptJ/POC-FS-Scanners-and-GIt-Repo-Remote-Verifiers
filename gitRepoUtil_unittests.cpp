//
// Created by josh on 1/21/26.
//

#include "gitRepoUtil.cpp"
#include "gtest/gtest.h"
#include <string>
#include <map>
#include <filesystem>

TEST(GitRepoUtilTest, TestIsGitRepositoryValid) {
    try {
        std::string actualCurrWorkDir = std::filesystem::current_path().string();
        std::string actualRepoPath = actualCurrWorkDir + "/.git";
        gitRepoUtil gitutil = gitRepoUtil(actualRepoPath);
        EXPECT_TRUE(gitutil.getIsValidRemote());
        std::vector<std::map<std::string, std::string>> actualRemotes = gitutil.getRemotes();
        EXPECT_EQ(actualRemotes.size(), 1);
        for (const auto& remote : actualRemotes) {
            for (const auto& [key, value] : remote) {
                if (key == "origin") {
                    EXPECT_TRUE(value.contains("github.com"));
                } else {
                    FAIL() << "Unexpected remote name found: " << key;
                }
            }
        }
} catch (std::exception& e) {
        printf("%s\n", e.what());
        FAIL() << "Exception thrown during valid repository test.";
    }
}

TEST(GitRepoUtilTest, TestIsGitRepositoryInValid) {
    std::string actualRepoPath = "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers-bad/.git"; // replace with your own path
    try {
        gitRepoUtil gitutil = gitRepoUtil(actualRepoPath);
    } catch (std::exception& e) {
        printf("%s\n", e.what());
        EXPECT_STREQ(e.what(), "Repository not found at path: /home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers-bad/.git"); // replace with your own path
    }
}

TEST(GitRepoUtilTest, TestIsValidRemoteURL) {
    std::string actualRemoteUrl = "git@github.com:HauptJ/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers.git";
    EXPECT_TRUE(gitRepoUtil::verifyRemoteURL(actualRemoteUrl));
}

TEST(GitRepoUtilTest, TestIsInValidRemoteURL) {
    std::string actualRemoteUrl = "git@gitlab.com:HauptJ/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers.git";
    EXPECT_FALSE(gitRepoUtil::verifyRemoteURL(actualRemoteUrl));
}