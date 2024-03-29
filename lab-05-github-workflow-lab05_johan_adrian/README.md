# GitHub Flow

> Author(s): Andrew Lvovsky ([@borninla](https://github.com/borninla)) and Brian Crites ([@brrcrites](https://github.com/brrcrites))

For most of your professional careers in industry, you will work on projects alongside other contributors. In order to reduce the friction that can occur between developers with different backgrounds, styles, and opinions, most companies, organizations, and projects dictate their preferred style and method of contribution. Dictating a preferred style gives your codebase a consistent look and makes it easier for developers to understand since things are done in a consistent manner. Having a preferred method of contribution, or workflow, makes sure that different contributors know who is working on what and enforce that their contribution meets the standards set out by the organization. Having a good workflow is an important step to make sure your organziation (or for this course, your team) is working efficiently to create well-tested and high quality code.

Many [git workflows](https://www.endpoint.com/blog/2014/05/02/git-workflows-that-work) exist today and they all have their pros and cons. However, GitHub flow is one of the simplest to learn and is our preferred method for this course. A brief overview of GitHub flow is found in the diagram below.

<img src="images/github-flow.png?raw=true" width="1000">

Source: [GitHub Guides](https://guides.github.com/introduction/flow/)

The goal of this lab is to get you more comfortable using Git and GitHub when working on a team. You and your partner will work on extending the Bash Unit Testing lab by adding a count function, along with unit tests for it. By the end of this lab, you should be familiar with

* how to create issues to manage tasks
* how to use branches to reduce conflicts
* how to use pull requests to review and merge changes
* how to tackle merge conflicts
* how to tag releases
* how to revert to previous commits

> Note: please wait to clone this repository until instructed to later in this README

## Issue Tracking

The first thing we are going to do is use the built-in GitHub issue system to track and manage tasks. Issues are useful to keep track of bugs that appear in projects as well as tracking work that still needs to be done. 

In GitHub each repository has its own associated set of issues, which are located under the `Issues` tab near the top of the repository. Currently, there aren't any open issues for this lab, so let's add some. Click on the green `New issue` button. On this page, you should notice some sections on the right. They are:

* Assignees - the developer assigned to the task, who will recieve email alerts when comments are made on the issue. Keep in mind that more than one person can be assigned to the same issue, especially when they require some discussion.
* Labels - help to categorize the types of tasks that need to be completed. GitHub will autopopulate a list of tags for your repo, but you are free to edit or remove them as you see fit. We recommend using a basic set of `bug`, `test`, and `develop` tags to start with, and adding more as needed. GitHub tags can range from [relatively small and simple sets](https://medium.com/@dave_lunny/sane-github-labels-c5d2e6004b63) to [large hierarchies of color coded tags](https://robinpowered.com/blog/best-practice-system-for-organizing-and-tagging-github-issues/).
* Projects - which project this issue falls under. Projects are typically used to split the issues across teams or large features, and for this course we recommend you just have a single TODO project if you use it at all. If you are using the Projects feature, it is possible to to have issues automatically added to a project's Kanban board. [You can read this link for more information](https://help.github.com/en/articles/configuring-automation-for-project-boards).
* Milestone - which milestone this issue falls under. This is similar to Projects, except milestones are usually associated with specific sprints and track completion of issues towards a particular feature or release.

Let's start by creating two issues for today's lab, with each partner creating one of the issues. Here we have listed the title is in bold followed by the text for the body of the issue. Note that you can use markup in the body of your issues which we encourage you to do.

* **Create a word counting function**: Add a function to `main.cpp` which counts the number of words input from the user
* **creating a word counting unit test**: Create unit tests for the word count function

Throughout the remainder of the lab, Partner 1 will be working on the count function and Partner 2 will be creating the unit test. Make sure to set the assignees according to who will be completing which portion. For creating a count function, choose the "enhancement" label. For the unit test, choose the "unit test" label. Don't worry about selecting Projects or Milestone for this lab.

> Note: If the "enhancement" or "unit test" label doesn't exist, click on "Edit labels" and then "New label" at the top right and add it.

## Copying Files from the Bash Lab

Did you think we we're done adding issues? Nope! ( ͡° ͜ʖ ͡°) 

This lab will be extending the work you did in the Bash and Unit Tests lab. Create an issue for initializing the repository with the previous labs files (you should choose a good title and description) and assign the issue to both partners along with an "enhancement" label.

Start by cloning the repository for this lab. Since the code provided in this lab already contains a submodule you will need to clone it recursively in order to recieve the code in the submodule along with the repository code.

```
git clone --recursive <lab-clone-url>
```

> Note: whenever you close a repository with that contains submodules you will need to use the `--recursive` flag to recieve the code within the submodule. If you forget to clone it recursively, you can run `git submodule update --init --recursive` to pull the submodules after the repo has been cloned. This can also be necessary when switching to a branch which has had a submodule added to it.

Since this is an extension of the previous lab start by copying over the files from your Bash and Unit Testing lab (either partners files will be fine as long as they completed the Bash and Unit Testing lab) into the new lab. If you are working in a different environment than before or no longer have a local copy of your Bash and Unit Testing lab, re-clone it to your machine before proceeding (but don't clone it into this lab's folder). Make sure that both the Bash and Unit Testing lab's directory and this lab's directory are on the same level of directory hierarchy, otherwise you will need to modify the path in the next step. Navigate to the Bash and Unit Testing lab's directory and use the `cp` command to copy the following files into this labs directory.

```
cp c-echo.h test.cpp CMakeLists.txt main.cpp .gitignore ../<this-labs-directory>
```

Five new files should now be located in this lab's directory (you will have to navigate back to this labs directory and use `ls` to see them).

Since we are adding `c-count.h`, we should also update our `CMakeLists.txt` file in the `ADD_EXECUTABLE` field like so:

```
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(c-echo-count
    main.cpp
)

ADD_EXECUTABLE(test
    test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
```

Let's also change our .gitignore to reflect our additions (you can remove the entry for `c-echo` since we changed the name of the generated executable in CMake):

```
c-echo-count
test

CMakeCache.txt
CMakeFiles/
cmake_install.cmake
Makefile
```

Go ahead and git add, commit, and push these five files. You have now completed your first issue. Go back to the issues tab and click on the issue you created for moving the files. Scroll to the bottom and click the "Close issue" button, which will convert that issue from open to closed, representing it has been completed.

Make sure the partner that didn't add the files does a `git pull` so that everyone is up-to-date going into the next section.

## The Importance of Effective Branching

In the Git lab, you learned that branching is used when developers want to change code without having to deal with conflicts between other contributors. When working on a team, it is wise to separate what each person is working on (and often each feature that person is working on) by making a branch unique to that change or set of changes. When that team member finishes their part, they can then merge back into the master or main development branch to signify that it is complete and should be part of the code everyone uses moving forward.

> Note: You should refer back to the links we provided in the git lab for creating good commit messages, however these are not the only good methods for commit messages. Lots of organizations have requirements on commit messages as they do reviews and style. Some of these try and categorize the commits such as the [gitmoji](https://gitmoji.carloscuesta.me/) system.

Each partner should now create a branch from the master branch. Both partners should title their branches as such, respectively:

```
$ git branch <partner-1-github-username>/count-func
$ git branch <partner-2-github-username>/count-test
```

You should prepend your branch with your username to make it easy to see who owns which branch and to avoid naming conflicts between individual contributors branches. After you have each created your individual branch, **it is very important** that you change to that branch with `git checkout <branch-name>`

### The First Branch (Partner 1)

Partner 1 should add the following count function to the provided `c-count.h`:

```c++
#include <iostream>

unsigned int count(const std::string& str) {
    unsigned int counter = 0;
    bool on_space = true;
    
    for(int i = 0; i < str.size(); i++) {
        if (std::isspace(str[i]))
            on_space = true;
        else if (on_space) {
            counter++;
            on_space = false;
        }
    }

    return counter;
}
```

This function counts the number of words in a string, delimited by whitespace. It takes a string and iterates through every character. When whitespace is encountered, a flag gets set. If the next character doesn't contain whitespace, the counter is incremented and the flag is unset.

### The Second Branch (Partner 2)

Partner 2 should add or update the following unit tests to `test.cpp`, taking special note to update the tests from the previous lab since we have updated the name of the executable that is generated by CMake:

```c++
#include "c-echo.h"
#include "c-count.h"

#include "gtest/gtest.h"

TEST(EchoTest, HelloWorld) {
    char* test_val[3]; test_val[0] = "./c-echo-count"; test_val[1] = "hello"; test_val[2] = "world";
    EXPECT_EQ("hello world", echo(3,test_val));
}

TEST(EchoTest, EmptyString) {
    char* test_val[1]; test_val[0] = "./c-echo-count";
    EXPECT_EQ("", echo(1, test_val));
}

TEST(CountTest, HelloWorld) {
    std::string test_str = "hello world";
    EXPECT_EQ(2, count(test_str));
}

TEST(CountTest, EmptyString) {
    std::string test_str = "";
    EXPECT_EQ(0, count(test_str));
}

TEST(CountTest, ManySpaces) {
    std::string test_str = "   this   string has     weird   spacing";
    EXPECT_EQ(5, count(test_str));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

One more thing, Partner 2. Your `c-count.h` should still look like below:

```c++
#include <iostream>

// count function should go here
```

Let's say you didn't know your partner was editing the same file in another branch. To test the functionality of your unit test, you should write a count function that always returns 0.

```c++
#include <iostream>

int count(const std::string& phrase) {
    return 0;
}
```

Partner 2 should now build and compile using `cmake3 .`, `make`, then run `./test`. You should see 2 tests fail, CountTest's HelloWorld and ManySpaces. EmptyString passes since we are returning 0 at all times.

### The Push

Both partners should now commit and push these changes to their branches (if you haven't already).

> Note: Since these branches were made locally and need to be pushed up to GitHub, you will be prompted to run `git push --set-upstream origin <branch name>` when pushing a branch for the first time.

Each partner should also refresh their local git's view of what branches exist and what they have by running `git fetch`. This will sync your git's local view of the world with what is in GitHub showing new changes. Rather than merging your branches into master through the command line, it is good practice to open a pull request that can be reviewed by your team members. 

## Pull Requests

Most organizations lock their master or main development branches so that code reviews and a passing set of unit and/or integration tests are required before code can be merged in to the master or main devleopment branches. The GitHub pull request system allows for maintainers of repositories to block changes from being added to certain branches until they meet specific requirements, such as having a minimum number of approved code reviews and successfully passing automated tests. By having GitHub enforce these rules for us *before* our stable branches (like master) can have code added to them, we greatly increase the changes that our stable branches will continue to be stable.

Let's try doing this now. Both partners should open up their GitHub repository to prepare the PR. 

### Creating a Pull Request

Partner 1 should press on the "Branch" dropdown menu located right above the repository files list and select `<partner-1-github-username>/count-func`. This will cause you to switch to viewing the new branch, at which point you should click on the "New pull request" button right next to the "Branch" dropdown. This will bring up the editing screen for the PR. You might notice that this page looks similar to creating a new issue, with an added "Reviewers" section. Partner 1 should add a reviewer by clicking on the "Reviewers" section, searching for Partner 2's username, and selecting them. This will assign Partner 2 to review the PR and will add them to the notification list so they will receieve emails about any comments or discussion made on the PR. Make sure to also assign yourself (Partner 1) under the Assignees section, and give it a label that best suits the addition. Title it `Add Count Function` and leave a brief description of what is being added. In most cases, a description should be well-detailed so the reviewer can easily understand what modifications they need to look for. Once done finalizing the PR, click on "Create pull request".

Partner 2 should follow the same steps above, except by selecting `<partner-2-github-username>/count-test` from the branch dropdown menu. Also, title it `Count Unit Test`. Make sure to choose Partner 1 as the reviewer and Partner 2 as the assignee.

### Issue Tracking Strikes Back!

Previously, in order to close an issue, we went to the issues page and closed it by hand. However, this is not the typical method for closing issues on GitHub. Instead, issues are usually closed through special annotations in commit messages. This has the benefit of not only closing the issue when the commit with the annotation is merged into master automatically, but also linking the PR or commit that has the annotation to the issue automatically so it can be easily referenced later if there is an issue.

Both partner's should amend their latest commit message using the `--amend` flag, which re-opens the last commit allowing it to be changed. Type the following to do so:

```bash
git commit --amend
```

This will open up your editor. The very top should contain your most recent commit message. Go ahead and change the message to `Fixes #<issue-number>`.

> Note: the issue number can be found to the right of your issue's title (after the hashtag). Don't forget to include the hash before the issue number.

Save the message and exit the editor, then push once more. You will need to force this push by entering `git push -f`, since this commit was already pushed earlier and needs to be updated.

Go to your PRs on GitHub and you'll notice that every commit made to a branch that has an open PR will be listed. You should also notice that your commit message has a hyperlink. If you click on the number, it should send you to the specified issue. Once the PR is merged and closed, GitHub will take care of closing the issue for you automatically. Nice!

### Reviewing a Pull Request / Code Reviews

When developing on existing projects, team members will usually be working on integrating features, squashing bugs, refactoring, or otherwise working with existing code. To help make sure that new changes will not adversely affect the system and are of generally high quality, code reviews are usually held with other members of the team. While there are lots of different ways to perform a code review, it is typically done through comments (either generally on the PR or related to specific lines of code changed in that PR). This is because GitHub is primarily focused on remote and decentralized teams. Because you are likely to see your team members often, you may find it easier to work through code reviews in person. This is fine, but we do request that you write a simple "Reviewed in person" comment before merging a PR (more on merging in a later section).

You should review this [guide](https://smartbear.com/learn/code-review/best-practices-for-peer-code-review/) for some good practices for code reviews.

Partner 2 should now review Partner 1's PR. Navigate to the "Pull requests" tab and choose the `Add Count Function` PR. From here, you can review comments made about the PR under the "Conversation" tab, all commits associated with that PR under the "Commits" tab, and what changes have been made to various files under the "Files changed" tab.

Near the bottom of the "Conversation" tab, you should see a green checkmark next to a title reading "This branch has no conflicts with the base branch". This means GitHub found no merge conflicts between this branch and the master branch. Go ahead and press "Merge pull request". It will ask you to confirm the merge, which you should do. This will cause GitHub to essentially call `git checkout master && git merge <partner-1-github-username>/count-func` behind the scenes and merge the branch into master. You are now given the option to delete the branch, which you should do. This keeps the number of branches associated with your repo manageable and stops you from accidentally re-using a branch for a feature it wasn't named for.

> Note: deleting the branch will not automatically remove it from your local git (remember git doesn't automatically get updates from GitHub). You should switch off the branch on your local git (usually by checking out the master branch) and then run `git fetch` to sync your local git with GitHub, which will then trim the branch from your local git. If you do not do this and try and push from the deleted branc you will recieve an error.

Partner 1 should navigate to the "Pull requests" tab and select the `Count Unit Test` PR. Unlike the first PR, this one has a merge conflict and GitHub cannot merge it automatically.

#### Fixing a Merge Conflict

Let's resolve the merge conflict. Partner 1 should type the following commands which will change their current branch to master, update it to match what is on GitHub, and switch them back to their new branch:

> Note: You might get an error about your `test` executable being overwritten during the checkout process. If this happens, simply remove the executable by typing `rm test`, then try again.

```bash
git checkout master
git pull
git checkout <partner-2-github-username>/count-test
git merge master
```

The last line will attempt to auto-merge master with the current branch, which we already know from GitHub will cause a conflict. You should see something like below:

```
Auto-merging c-count.h
CONFLICT (content): Merge conflict in c.count.h
Automatic merge failed; fix conflicts and then commit the result.
```
If you open `c-count.h` in a text editor, you should see some lines that include `<<<<<<< HEAD`, `=======`, and `>>>>>>> master`. 

```c++
#include <iostream>

<<<<<<< HEAD
int count(const std::string& phrase) {
        return 0;
=======
unsigned int count(const std::string& str) {
        unsigned int counter = 0;
        bool on_space = true;

        for(int i = 0; i < str.size(); i++) {
                if (std::isspace(str[i]))
                        on_space = true;
                else if (on_space) {
                        counter++;
                        on_space = false;
                }
        }

        return counter;
>>>>>>> master
}
```

Everything past `<<<<<<< HEAD` and before `=======` is the new code coming in from the branch being merged, while everything past `=======` and before `>>>>>>> master` is existing code from the master branch (the branch that is being merged into). We'd like to accept the fully-built count function, so go ahead and delete everything past `<<<<<<< HEAD` and before `=======`. Make sure to also delete these indicators, or you will get compilation errors.

> Note: while this merge was relatively straight-forward and we just wanted to accept what was in master, there are times when you will need to merge both branches in order to get what you actually want. This may lead to additional errors, so its always important to test the code to make sure it's still working after a merge has been resolved.

Once you are done, be sure to `git add` the file you just modified, commit it, and push to GitHub. When committing a merge, simply typing `git commit` without the `-m` flag will automatically populate a merge message. Partner 1 should now refresh the `Count Unit Test` PR on GitHub. Notice that every commit made in the branch should appear within the PR automatically, so you don't need to close and re-open a PR if there are issues. PRs and the conversation and commit history associated with them can serve as valuable documentation about why certain design or coding decisions were made.

Using the good practices for code reviews reference above, make sure everything looks good with this PR. There should no longer be any merge conflicts, so go ahead and press "Merge pull request" and repeat the same process of deleting the branch as stated above.

## Reverting Commits

Throughout the development process, there are times where new commits may introduce problems in existing code. For these situations we can use git to revert the changes so our master is functional while we debug the issue on our own branch. This is very important for larger teams who might have contributors branching off of a broken master, leading to frustration when a developer thinks their changs are broken when really it was master that was broken.

Uh-oh, we forgot about adding the function to `main.cpp`! Let's do that now. Since Partner 1 resolved the merge conflict, Partner 2 should do this part.

```c++
#include "c-echo.h"

int main(int argv, char** argc) {
    std::cout << "Count of output: " << count(echo(argv,argc)) << std::endl;
}
```

You should be in the master branch, so go ahead and git add, commit, and push this change. Now try building using `cmake3 .` and `make`. Oops, looks like something broke! It seems that we forgot to add `#include "c-count.h"`.

Let's fix this using reversion! To revert back to the last commit, type the following command.

```
git revert HEAD
```

This will create a new commit that is left off at the last commit. Let's add the main function once more, this time not forgetting `#include "c-count.h"`.

```c++
#include "c-echo.h"
#include "c-count.h"

int main(int argv, char** argc) {
    std::cout << "Count of output: " << count(echo(argv,argc)) << std::endl;
}
```

Please git add, commit, and push one more time.

> Note: To revert to two or more commits down the chain, replace `HEAD` with the commit reference (the long string of characters that identify each commit that can be viewed using `git log`).

## Tagging

Often, you’ll want to tag certain git commits because they are special. The most common reason to tag a commit in git is to tag it as a stable version, especially when using the [semantic versioning schemes](https://semver.org/). Let's assume that our code is now ready for release as `v1.0.0` and tag it as such.

```
$ git tag -a v1.0.0 -m “Initial stable release”
```

The `-m` in this case works the same as it does when performing a commit, allowing us to add a message but bypassing the editor to do so. The `-m` flag will only allow you to set the title, so make sure to follow the 50 character commit title rule from the Git lab and only use it when no additional information would be necessary in the commit message body. If you wanted to tag a commit besides the current commit you would need to add the commit hash after the version number (but before the message). Normally a 1.0.0 release would have lots of additional notes on the current state of the software, but this is just an example. These tagged versions are stored in a special section of the repository on GitHub along with compressed versions of the source files to make public releases easier.

> Note: It is possible to create both annotated tags using the `-a` flag and unannotated flags. Annotated flags carry additional information about their creation, so you **must** use them when adding a tag for your assignment.
