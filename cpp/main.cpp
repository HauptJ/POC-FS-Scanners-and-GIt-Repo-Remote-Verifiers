//
// Created by josh on 1/21/26.
//

#include <git2.h>
#include <stdio.h>
#include <string>

int main() {

    git_repository *repo = nullptr;
    int error;

    git_libgit2_init();

    error = git_repository_open(&repo, "/home/josh/dev/hauptj/POC-FS-Scanners-and-GIt-Repo-Remote-Verifiers/.git");
    if (error < 0) {
        const git_error *e = git_error_last();
        printf("Error %d opening repository: %s\n", error, e->message);
        return error;
    }

    git_strarray remoteNames = {0};
    error = git_remote_list(&remoteNames, repo);
    if (error < 0) {
        const git_error *e = git_error_last();
        printf("Error %d getting remotes repository: %s\n", error, e->message);
        return error;
    }

    for (int i = 0; i < remoteNames.count; i++) {
        printf("Remote %d: %s\n", i , remoteNames.strings[i]);
        git_remote* remote = nullptr;
        error = git_remote_lookup(&remote, repo, remoteNames.strings[i]);
        if (error < 0) {
            const git_error *e = git_error_last();
            printf("Error %d getting remotes repository urls: %s\n", error, e->message);
            return error;
        }
        const char* url = git_remote_url(remote);
        std::string remoteUrl = url ? url : "";
        printf("URL: %s\n", remoteUrl.c_str());


    }

    git_repository_free(repo);

    git_libgit2_shutdown();

    return 0;
}