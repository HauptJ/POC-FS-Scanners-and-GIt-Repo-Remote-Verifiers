//
// Created by josh on 1/21/26.
//

#include <stdio.h>
#include <string>
#include "gitrepoutil.cpp"

int main(int argc, char* argv[]) {

    if (argc > 1) {
        printf("Number of repos to check: %d\n", argc - 1);

        for (int i = 1; i < argc; i++) {
            std::string repoPath = argv[i];
            printf("Checking repository: %s\n", repoPath.c_str());
            gitrepoutil gitutil = gitrepoutil(repoPath);
            printf("Git Repo Remote URL is valid?: %s\n", gitutil.getIsValidRemote() ? "Yes" : "No");
        }
    }

    return 0;
}