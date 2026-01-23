//
// Created by josh on 1/21/26.
//

#include "gitRepoUtil.cpp"
#include "gtest/gtest.h"
#include <string>
#include <map>

TEST(GitRepoUtilTest, TestIsGitRepositoryValid) {
    try {
        std::string in_str = "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers/.git";
        gitRepoUtil gitutil = gitRepoUtil(in_str);
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
} catch (std::runtime_error& e) {
        printf("%s\n", e.what());
        FAIL() << "Exception thrown during valid repository test.";
    }
}

TEST(GitRepoUtilTest, TestIsGitRepositoryInValid) {
    std::string in_str = "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers-bad/.git";
    try {
        gitRepoUtil gitutil = gitRepoUtil(in_str);
    } catch (std::runtime_error& e) {
        printf("%s\n", e.what());
        EXPECT_STREQ(e.what(), "Repository not found at path: /home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers-bad/.git");
    }
}

TEST(GitRepoUtilTest, TestIsValidRemoteURL) {
    std::string in_remote_Url = "git@github.com:HauptJ/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers.git";
    EXPECT_TRUE(gitRepoUtil::verifyRemoteURL(in_remote_Url));
}