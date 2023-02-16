# Welcome to Jam project repository
![GitHub Release](https://img.shields.io/badge/release-v0.2.1-informational)
![GitHub Release Date](https://img.shields.io/badge/release-march-yellow)
![GitHub Raylib](https://img.shields.io/badge/Raylib-4.0.0-green)

## Here you will find all you need to know about:

- [Installation](#installation)
- [How to use](#how-to-use)
- [Gitflow](#gitflow)
- [Commit structure](#commit-structure)
- [ECS architecture](#ecs-architecture)
- [Network](#network)
- [VS Code configuration](#vs-code-configuration)

### Installation
- [Clone the repository](https://github.com/leon3108/JamSouffrance)
- On **Windows**
    - Install Visual studio 2021
    - Open the project and launch it
 - On **linux** run the following commands
```bash
    if [ ! -d "build" ]; then mkdir build; fi
    rm -rf jam
    cd build && cmake install .. && cmake --build . && cd .. && cp build/jam
```

### How-to-use

In ./build simply run

    ./jam

### Gitflow
The Gitflow method can be defined in a few steps:
1. Each new feature should be implemented on a new branch -> ``git checkout develop ;git checkout -b feature_branch``
2. Once the feature is ready you create a **pull request** to merge **your branch on develop**
3. Once there are enough features on develop a new release can be done by using this command ``git checkout develop; git checkout -b release/0.1.0``

> :warning: This branch will be modified only for bug fixes, no more features will be added :warning:

4. Finally when the release is ready, the branch can be merged with develop and main

[More information on this page](https://www.atlassian.com/fr/git/tutorials/comparing-workflows/gitflow-workflow)

### Commit structure

Example → `fix: fix foo to enable bar`

The commit type can include the following:

- `feat` – a new feature is introduced with the changes
- `fix` – a bug fix has occurred
- `chore` – changes that do not relate to a fix or feature and don't modify src or test files (for example updating dependencies)
- `refactor` – refactored code that neither fixes a bug nor adds a feature
- `docs` – updates to documentation such as a the README or other markdown files
- `style` – changes that do not affect the meaning of the code, likely related to code formatting such as white-space, missing semi-colons, and so on.
- `test` – including new or correcting previous tests
- `perf` – performance improvements
- `ci` – continuous integration related
- `build` – changes that affect the build system or external dependencies
- `revert` – reverts a previous commit

### ECS architecture
[*Doc ECS*](https://courageous-season-e95.notion.site/ECS-e24adb89591348fc91b781da69e7154e)

[*ECS Schema*](https://www.figma.com/file/sgttRTtOL3eVbC5MTpLJ2I/Untitled?node-id=63%3A91&t=03LXKs6kYiRorfPO-0)

### VS Code configuration

Name: Prettier - Code formatter
Id: esbenp.prettier-vscode
Description: Code formatter using prettier
Version: 9.10.4
Publisher: Prettier
VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode
