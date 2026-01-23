# Recursive Root Directory Scanner and Git Repository Remote URL Verifier
Proof of concept recursive file system scanner and Git repository config remote URL verifier using libgit2

## Overview
This project is a proof-of-concept (POC) tool that recursively scans a file system to identify Git repositories and verifies their remote URLs using the libgit2 library. The tool is designed to help developers and system administrators ensure that their Git repositories are correctly configured with valid remote URLs.

## Features
- Recursive scanning of directories to locate Git repositories.
- Verification of remote URLs for each identified Git repository.
- Utilization of the libgit2 library for Git operations.
- Command-line interface for easy usage.
- Detailed logging of results and errors.

## Prerequisites
- C++ compiler (e.g., GCC, Clang) with C++23 support
- CMake (version 4.1 or higher)
- libgit2 library (version 1.5.0 or higher)
- Git is installed on the system

## Instructions to Build and Run
1. Clone the repository:
2. build main.cpp with libgit2
   ```bash
   g++ -std=c++23 -o git_repo_verifier main.cpp -lgit2
   ```
3. Run the tool, providing the directory to scan as an argument:
```bash
   ./git_repo_verifier /path/to/scan
   ```

## Testing
1. Ensure Google Test is installed on your system.
2. Comment out `#include "gitRepoUtil.cpp"` in rootDirScanner.cpp 
3. Configure the file paths in gitRepoUtil_unittest.cpp to point to your test Git repositories.
4. build allTests.cpp with libgit2 and Google Test (lgtest)
   ```bash
   g++ -std=c++23 -o allTests allTests.cpp -lgit2 -lgtest
   ```
5. Run the tests:
   ```bash
    ./allTests
    ```

## Algorithm
1. Start from the specified root directory.
2. Recursively traverse each subdirectory.
3. Identify and log source code files based on their extensions.
4. For each directory, check if it contains a `.git` folder.
5. If a Git repository is found, use libgit2 to open the repository and retrieve its remote URL.
6. Verify the remote URL uses a valid / allowed hostname for example, github.com. 
7. If the remote URL is valid, log the repository path and the valid URL.
8. If the remote URL is invalid, log the repository path and the invalid URL.
9. Continue scanning until all directories have been processed.
