//
// Created by josh on 1/21/26.
//

#include "gitrepoutil.cpp"
#include "gtest/gtest.h"
#include <string>

TEST(GitRepoUtilTest, TestIsGitRepositoryValid) {
    std::string in_str = "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers/.git";
    gitrepoutil gitutil = gitrepoutil(in_str);
    EXPECT_TRUE(gitutil.getIsValidRemote());
}

TEST(GitRepoUtilTest, TestIsGitRepositoryInValid) {
    std::string in_str = "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers-bad/.git";
    try {
        gitrepoutil gitutil = gitrepoutil(in_str);
    } catch (std::runtime_error& e) {
        printf("%s\n", e.what());
        EXPECT_STREQ(e.what(), "Repository not found at path: /home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers-bad/.git");
    }
}

TEST(GitRepoUtilTest, TestIsValidRemoteURL) {
    std::string in_remote_Url = "git@github.com:HauptJ/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers.git";
    EXPECT_TRUE(gitrepoutil::verifyRemoteURL(in_remote_Url));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}