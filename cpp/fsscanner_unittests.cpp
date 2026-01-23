//
// Created by josh on 1/21/26.
//

#include "fsscanner.cpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

TEST(fsscannertest, isSourceCodeFile) {
    std::vector<std::string> validSourceCodeFilePathsIn = {
        "/home/josh/example.c",
        "/home/josh/project/src/main.cpp",
        "/home/josh/scripts/script.py"
    };

    std::vector<std::string> invalidSourceCodeFilePathsIn = {
        "/home/josh/document.txt",
        "/home/josh/image.png",
        "/home/josh/archive.zip"
    };

    for (const auto& filePath : validSourceCodeFilePathsIn) {
        EXPECT_TRUE(fsscanner::isSourceCodeFile(filePath)) << "Failed for valid source code file: " << filePath;
    }

    for (const auto& filePath : invalidSourceCodeFilePathsIn) {
        EXPECT_FALSE(fsscanner::isSourceCodeFile(filePath)) << "Failed for invalid source code file: " << filePath;
    }
}

TEST(fsscannertest, expectedScanResult) {
    try {
        std::string testRootDir = "/home/josh/dev";

        std::vector<std::string> expectedSourceCodeFiles = {
            "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers/cpp/main.cpp",
            "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers/cpp/allTests.cpp"
        };

        std::string expectedValidGitRepoPath = "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers/.git";
        std::string expectedInvalidGitRepoPath = "/home/josh/dev/gl/hauptj/k8s-stack/.git";
        std::string expectedValidRemoteUrl = "github.com";
        std::string expectedInvalidRemoteUrl = "gitlab.com";
        /*std::map<<std::string, std::vector<std::string>> expectedValidRemotes = {
            {expectedValidGitRepoPath, {expectedValidRemoteUrl}}
        };
        std::map<std::string, std::vector<std::string>> expectedInvalidRemotes = {
            {expectedInvalidGitRepoPath, {expectedInvalidRemoteUrl}}
        };*/

        fsscanner scanner(testRootDir);
        std::vector<std::string> actualSourceCodeFiles = scanner.getSourceCodeFiles();
        EXPECT_GT(actualSourceCodeFiles.size(), 0);
        std::vector<std::map<std::string, std::string>> actualValidRemotes = scanner.getValidRemotes();
        EXPECT_GT(actualValidRemotes.size(), 0);
        printf("actualValidRemotes size: %zu\n", actualValidRemotes.size());
        std::vector<std::map<std::string, std::string>> actualInvalidRemotes = scanner.getInvalidRemotes();
        EXPECT_GT(actualInvalidRemotes.size(), 0);
        printf("actualInvalidRemotes size: %zu\n", actualInvalidRemotes.size());

        // check if we found the expected source code files

        for (const auto& expectedFile : expectedSourceCodeFiles) {
            EXPECT_NE(std::find(actualSourceCodeFiles.begin(), actualSourceCodeFiles.end(), expectedFile), actualSourceCodeFiles.end()) // if we reach the end, the file was not found
                << "Expected source code file not found: " << expectedFile;
        }

        for (const auto& remote : actualValidRemotes) {
            for (const auto& [key, value] : remote) {
                printf("key: %s, value: %s\n", key.c_str(), value.c_str());
                if (key == expectedValidGitRepoPath) {
                    EXPECT_TRUE(value.contains(expectedValidRemoteUrl));
                    printf("Found: %s contains %s\n", value.c_str(), expectedValidRemoteUrl.c_str());
                }
            }
        }

        for (const auto& remote : actualInvalidRemotes) {
            for (const auto& [key, value] : remote) {
                printf("key: %s, value: %s\n", key.c_str(), value.c_str());
                if (key == expectedInvalidGitRepoPath) {
                    EXPECT_TRUE(value.contains(expectedInvalidRemoteUrl));
                }
            }
        }

    } catch (std::exception& e) {
        printf("%s\n", e.what());
        FAIL() << "Exception occurred during expectedScanResultsTest: " << e.what();
    }
}