# Git and GitHub

> Author(s): Brian Crites ([@brrcrites](https://github.com/brrcrites)), Mike Izbicki ([@mikeizbicki](https://github.com/mikeizbicki))

In this class we will be using the git version control system as well as the GitHub remote repository service. Git is a version control system (VCS) which allows for the revision and coordination of code between different developers and between different features. GitHub allows for these features not only locally but over the internet, and adds features such as code reviews and issue tracking. GitHub has become the de-facto standard for hosting and developing open source projects. Whatever programming language you use in the future, you will almost certainly use a VCS. In this lab you will learn the basics of using git and how to save your local work to GitHub.

## Git, GitHub, and Hammer 

For this lab we will be using the git tools on the hammer server, as well as GitHub. You will need to log into the hammer server using a secure shell (SSH). If you are using a Linux or Mac computer, you can run the following command in the terminal

```
ssh <your_username>@hammer.cs.ucr.edu
```

Replacing `<your_username>` with your CS username. You may be asked to exchange keys with the server, which you should allow, and then you will be prompted for your password. You should note that when typing your password no characters will be displayed, but you are still typing (this is a security measure).

If you are using a Windows computer you will first need to install a program called PuTTY, which can be installed from [putty.org](http://www.putty.org/). When you open PuTTY there will be a box for a “Host Name”, where you will input `<your_username>@hammer.cs.ucr.edu` (again replacing `<your_username>` with your CS username). From there you can follow the above steps for exchanging keys and entering your password.

The server that is used for CS100 is a version of RedHat Linux, which is a paid version of linux that has the benefit of being extremely stable. The problem with this version of linux is that to keep it stable they do not update its tools to new version very often. The version of the git tool that is installed is not compatible with the online service GitHub, so you will need to enable an updated version of the tool for your account with the following command in your terminal

```
$ source /opt/rh/devtoolset-6/enable
```

This will allow you to use a newer version of git that is compatible with github. **You will need to run this command every time you login to hammer** or alternatively add it to your .bashrc using emacs or vim. If you are unfamilair with command line editors, you can read these tutorials for [vim](https://blog.interlinked.org/tutorials/vim_tutorial.html) and [emacs](http://www.jesshamrick.com/2012/09/10/absolute-beginners-guide-to-emacs/) to get started. Knowing at least one command line editor is extremely important since lots of new development is being done on cloud servers which do not have visual interfaces.

> Note: You are not required to develop on the hammer server for this course, and are encouraged to use your own development environment. However, you will need to validate that your code will run correctly on the hammer server as we cannot account for differences in everyone's individual development environments. You are required to host your code on GitHub.

## Git Config

Git is a local program for performing version control, which is also capable of working with a remote git server for saving code off site. GitHub is a web based git repository, which the local git program is capable of interfacing with. Git and GitHub are therefore two seperate systems and git needs to be configured correctly in order for your code changes to be tracked correctly. You should run the following commands on any new system you are committing from before you start working (these can be run from any directory):

```
git config --global user.name "<first-name last-name>"
git config --global user.email <github-registered-email>
```

GitHub will use the user email that you configure with your git client to track which users are creating what commits. This means that you'll need to use the email address you've registered with GitHub in the above configurations (otherwise you may see commits from an anonymous user)

## Git Init & Clone

The traditional way to start a new project in git is to create a new directory and change into it. Go ahead and run the following commands on the terminal in hammer:

```
$ mkdir lab-01
$ cd lab-01
```

Then to initialize that directory as a git project use the following git initialization command

```
$ git init
```

This will create a hidden .git repository which holds all the information that git uses to keep track of your files and changes. The folder is hidden because it begins with a period. By default, the ls command does not display these hidden folders. To display them, you must pass the -a flag, which displays all files. Compare the results of the following two commands:

```
$ ls
$ ls -a
```

However, you use a different method if you want to receive a copy of an already existing repository, which you will do for all of the labs and assignments in this course. Rather than initializing a new repository, you will make a “clone” or a repository that already exists. Start by moving out of the git project you just created, and removing that directory

```
$ cd ..
$ rm -rf lab-01
```

The `..` after the change directory command moves us up one directory, and the `rm -rf` will force (`-f`) the removal of all files recursively (`-r`) in that directory.

Now, go to the upper right of this page and click the “Clone or download” dropdown. A box will appear that should say “Clone with HTTPS” (if it says “Clone with SSH”, then click the small blue text to the right that says “Use HTTPS”). The box should look like the following, being careful to make sure it says "Clone with HTTPS".

![Image of clone popup set to HTTPS](https://github.com/cs100/template-lab-01-git-github/blob/master/images/https-clone.png?raw=true)

Copy the link in the box below, this is the GitHub repository url which you will use to clone that repository. Now, run the following command:

```
$ git clone <github-url>
```

Replacing the above `<github-url>` with the url that you copied from the “Clone or download” box. This will create a new folder named `lab-01-git-and-github-...` with some additional text based on your username/groupname. This new directory is a copy of the GitHub repository, and is already initialized as a git project. Move into this new directory and we can begin modifying it.

> Note: README.md files are special in GitHub repositories. The contents of the README.md file in the repositories root will actually be rendered along with a list of files for anyone who visits the repository. The hash (#) at the beginning of the line is part of GitHub Markdown which specifies that this line should be a title. [You can read more about GitHub Markdown here](https://guides.github.com/features/mastering-markdown/).

## Git Status, Add & Commit

Let's add some actual code to our project. Create a file main.cpp with the following code:

```
#include <iostream>

int main()
{
    std::cout << "hello git" << std::endl;
    return 1;
}
```

Compile and run the code:

```
$ g++ main.cpp
$ ./a.out
```

We've created our first file but git doesn’t automatically keep track new files for us. Instead, we have to tell git to start tracking this new file. Run the following command:

```
$ git status
```

In the output, there is a section labeled "untracked files." Notice that the main.cpp and a.out files is in this section. This means that git knows the the exists, but isn’t currently keeping track of changes to the file. We want to keep track of the main.cpp file, but not the a.out file since that should be recompiled to run correctly on different machines.

We don’t want git to continue to tell us that a.out is untracked, but luckily git has a solution for this problem. You can create a file .gitignore that will contain a list of all of the files that you want git to ignore when it tells you what is/isn’t tracked and modified. Create a .gitignore file (using either and editor or file redirection) and add a.out to that file:

```
$ echo “a.out” > .gitignore
```

The echo command will output the string `“a.out”` to terminal, which will then be redirected (`>`) to the .gitignore file (which will be created if it doesn’t already exist). Now check the status of your repo:

```
$ git status
```

Notice that a.out is no longer listed, only main.cpp and the new .gitignore are listed as untracked. Now, we can add both of these files to our project with the following commands:

```
$ git add main.cpp
$ git add .gitignore
```

> Note: Do not add executable or object files to your git repo, only add source files. Tracking executables uses LOTS of disk space and they are unlikely to work on other peoples machines. **If we see these files in your git repos, your grade on the assignment will be docked 20%**. You should use a .gitignore file so that they don’t appear in your git status or accidentally get added to your repository.

Now, when we run git status, there is a section labeled "Changes to be committed" with the main.cpp and .gitignore files underneath it. This means that git now thinks this file is part of the project, and will being to track changes to it.

Whenever we finish a task in our repo, we "commit" our changes. This tells git to save the current state of the repo, made up of all the files we’ve added, so that we can come back to it later if we need to. Commit your changes using the command:

```
$ git commit -m "my first commit”
```

Every commit needs a "commit message" that describes what changes we made in the repo. Writing clear, succinct, informative commit messages is one of the keys to using git effectively. In this case we passed the -m flag to git so the commit message was specified in the command line. If we did not pass a flag, then git would have opened the vim editor for us to type a longer commit message.

That was not a very informative commit message, so lets edit it to be something more informative. Anytime you need to modify the last commit that you made, you need to amend it which is done through the following command:

```
$ git commit --amend
```

Running this allows you to edit the last commit that you made, including which files were included in that commit. Anything that you have done a git add to before running git commit --amend will be added to the last commit in addition to allowing you to edit the commit message.

> Note: the --amend flag will let you add anything to the previous commit, even if it's not a good idea. Because of this you should use it carefully and for situations where you have forgotten a minor change (README, comment, better commit message) or your last commit did not actually function correctly and you need to “patch” it.

We didn’t write an informative commit message, so we should modify it to be something more useful. Run the `git commit --amend` command and you should see something like the following open in either vim or emacs.

```
My first commit
  
# Please enter the commit message for your changes. Lines starting
# with ‘#' will be ignored, and an empty message aborts the commit.
#
# On branch brrcrites/lab-01
# Changes to be committed:
#   added:   main.cpp
#   added:   .gitignore
#
# Changes not staged for commit:
#
# Untracked files:
#
```

While you can write any message that you want here, GitHub will do some automatic formatting based on past good practices for writing commit messages that you should adhere to. 

* The first line will be formatted as a subject line, and cut off at 50 characters. You should therefore pick a concise subject message that is < 50 characters long 
* You should separate the first line from the rest of your body text with a blank line
* The body of your message (anything else you add after the subject but before the commented lines) should describe what changes occurred and why, rather than how you did it. This is often formatted as a bulleted list using a * as the bullet.

Following these rules will make your commits nicely formatted on GitHub and easier to understand and process. Lets update our commit message to the following

```
Add initial program

* Added an initial main file which prints hello git to the command line
  
# Please enter the commit message for your changes. Lines starting
# with ‘#' will be ignored, and an empty message aborts the commit.
#
# On branch brrcrites/lab-01
# Changes to be committed:
#   modified:   README.md
#
# Changes not staged for commit:
#
# Untracked files:
#
```

After editing the file with the above message, exit your editor and the commit should update.

> Note: The -m flag should only be used when writing very short commit messages, and otherwise you should use the interactive mode to have both a subject and commit body. [For some more tips on writing effective git commit messages, read this blog post](https://chris.beams.io/posts/git-commit/).

Let's make one more commit so we'll have something to play with. Update your main to print the following statement after “hello git”:

```
std::cout << "git is easy?" << std::endl;
```

Now run:

```
$ git commit -m "Add git is easy output to main”
```

Uh oh! We got an error message saying: "no changes added to the commit".

Every time you modify a file, if you want that file included in the commit, you must explicitly tell git to add the file again. This is because sometimes programmers want to commit only some of the modified files. Run:

```
$ git status
```

To see the files that are currently being tracked. We can add the changes to the main.cpp file, and verify it is added, with:

```
$ git add main.cpp
$ git status
```

We can then commit the changes using:

```
$ git commit -m "Add git is easy output to main”
```

## Git Branch & Log

We’ve already talked about the fact that git keeps track of the state of your code every time you commit. This creates specific snapshots of your code at a point in time, and allows git to keep track of changes to each file over time. Git’s ability to keep track of each files changes and when those changes happened is an important factor in its ability to allow us to work collaboratively. Most software is written across an entire team of developers, and each developers could in theory be working on the same segment of code at any given time. If every time one of the developers made a commit, the other developers had to download the updates to the files, fix any conflicts between what they were already working on, and then test to make sure everything is broken then nothing would ever get done. 

Instead, each developers freezes the code at a specific commit (usually the most recent when they clone their repo, more on that later) and then they request the updates to all the files, resolve conflicts, and test the code when they are done working on their bit of the development. The way git represents the different developers working on the same code without constantly making collisions is with a feature called branching. A branch is what we call it when someone takes a commit from git, and starts developing from there separately from everyone else.

A project can have many branches, and every branch can be different than every other branch. The visualization showing where each branch has split and been added to, as well as merged back into each other is often known as the “working tree”. List the branches in your current project using the command:

```
$ git branch
```

This should list just a single branch called master. This branch was created for you automatically when you ran the `git init` command. 

> Note: There are a number of different git workflows that you can utilize, however this tutorial is going to use the ["Feature Branch Workflow"](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow) workflow. If you contribute to open source you may use the ["Forking Workflow"](https://www.atlassian.com/git/tutorials/comparing-workflows/forking-workflow) because it uses another layer of abstraction on top of branches (known as forks) which keep the open source repository clean. If you work for a company that needs to have a very stable product, you may use the ["Gitflow Workflow"](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow) which has dedicated develop, test, and release branches that can be rolled out over time and attempt to keep everything more stable.

Every time we add a new feature to a project, we create a branch for that feature. In order to help keep track of which branches are for what features, and who is using them, we are going to use a standard naming convention to make things easier. Let's create a branch called `add-user-input` in our project, and prepend our GitHub username so we know its ours:

```
$ git branch <github-username>/add-user-input
```

You should replace `<github-username>` with your own GitHub username. Verify that our branch was created successfully with the following command:

```
$ git branch
```

You should see two branches now. There should be an asterisk next to the master branch. This tells us that master is the currently active branch, and if we commit any new changes, they will be added to the master branch. (That is, master will change to point to whatever your new commit is.)

Switch to our new branch using the command:

```
$ git checkout <github-username>/add-user-input
```

Now run the following command:

```
$ git branch
```

Verify that the asterisk is next to the `<github-username>/add-user-input` branch. Since the only thing you did was switch branches, the working tree looks almost the same. The only difference is the asterisk has moved. You can also view the status of the current branch using:

```
$ git status
```
 
Let's modify our main.cpp file so that it asks the user their name before saying hello:

```
#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "What is your name?" << std::endl;
    std::cin >> name;
    std::cout << "Hello " << name << "!" << std::endl;

    return 1;
}
```

Sometimes, we make modification to a program and can’t quite remember exactly what we’ve changed since the commit. Luckily, since git is keeping track of all our file changes it provides a simple way to see what's been modified with the following command:

```
$ git diff main.cpp
```

Running this will show you the difference between the current version of main.cpp and the version at the last commit and you should see something like this

```
 #include <iostream>
+#include <string>
 
 int main()
 {
-    std::cout << "hello git" << std::endl;
+    std::string name;
+    std::cout << "What is your name?" << std::endl;
+    std::cin >> name;
+    std::cout << "Hello " << name << "!" << std::endl;
+
     return 1;
 }
```

Here, the lines with a plus (`+`) at the beginning represent new lines and the lines with a minus (`-`) represent lines that were removed. We can now commit our changes to the current working branch the same way we committed them before:

```
$ git add main.cpp
$ git commit -m "Add user input”
```

Before this commit, the `<github-username>/add-user-input` and `master` branches were pointing to the same commit. When you run this command, the `<github-username>/add-user-input` branch gets updated to point to this new commit. In git parlance, since the `<github-username>/add-user-input` branch now has one more commit than the `master` branch (and the `master` branch hasn’t been updated) it is now 1 commit ahead of `master`.

Let's verify that our changes affected only the `<github-username>/add-user-input` branch and not the `master` branch. First, checkout the `master` branch, then cat the main.cpp file, then return to the `<github-username>/add-user-input` branch.

```
$ git checkout master
$ cat main.cpp
$ git checkout <github-username>/add-user-input
```

You should be able to see the difference between the files (your text editor may also ask you to load the new file since it has detected changes). Branches allow us to work on and track multiple features at the same time without having to worry about creating errors in our repository (because the `master` branch will always be in a working state). We can also move forward and back in the changes that we’ve made to any branch, making it very easy to make a mistake and be able to recover from it (one of the major benefits of using git). 

Changing between branches to see the differences in files is difficult an error prone. Luckily, git provides a mechanism for viewing the commits that have been made through the git log. Run the following command and you should see your commit history:

```
$ git log
```

Each line starts with commit and then a series of numbers and letters known as a hash which are used to (relatively) uniquely identify each commit. At the end of some of these lines you can see additional information like (`HEAD -> <github-username>/add-user-input`) and (`master`). These are indicators showing the last commits for various branches (or at least the last ones git knows about).

Normally when working on a feature you would want to update the documentation in the README.md to reflect the changes. Proper documentation of your system will be part of your grade for this course. However, since the documentation for the labs is the instructions, you will only need to update your documentation for the projects.

While we were working on our `<github-username>/add-user-input branch`, someone reported a bug in our `master` branch. In particular, the main function in our `master` branch returns 1, but a successful program should return 0. In UNIX, any return value other than 0 indicates that some sort of error occurred.

To fix this bug, we first checkout our `master` branch:

```
$ git checkout master
```

Then create a bugfix branch and check it out:

```
$ git branch <github-username>/main-return-hotfix
$ git checkout <github-username>/main-return-hotfix
```

Now we're ready to edit the code. Update the main function to return 0, then commit your changes:

```
$ git add main.cpp
$ git commit -m "Fix main to return 0 not 1”
```

## Git Merge & Conflicts

We want our users to get access to the fixed software, so we have to add our hotfix code into the `master` branch. This process is called "merging," which in this case it is a simple procedure. First, checkout the `master` branch:

```
$ git checkout master
```

Then run the command:

```
$ git merge <github-username>/main-return-hotfix
```

This will try and automatically merge the hotfix code we wrote with the code in our current branch, which right now is `master`. If we are trying to merge branch B into branch A, there should be no conflicts if branch B is ahead (meaning there are new commits in B from when it was branched off A) and not behind (meaning there are new commits in A from when B was branched off). Branches can be both ahead and behind each other at any given time, meaning new commits have been made to both branches without a merge happening. This is very common, and so if conflicts do arise then git will warn us about them.

> Note: While the git merge conflict checking is good, it is not infowlable. Issues can arise that git will merge without warning you, usually when an interface is changed in one file but the calls are not changed in another. This can lead to weird bugs that are hard to diagnose if you think that the git merging system in infowlable.

With real bugs on more complicated software, bug fixes won't be quite this easy. They might require editing several different files and many commits. It might take us weeks just to find out what's even causing the bug! By putting our changes in a separate branch, we make it easy to have someone fixing the bug while someone else is adding new features.

Our `<github-username>/add-user-input` feature is also ready now. We've tested it (well not really, but you’ll get plenty of testing in the next lab) and are sure it's working correctly. It's time to merge this feature with the `master` branch. Run the commands:

```
$ git checkout master
$ git merge <github-username>/add-user-input
```

This one isn’t quite as easy as the last merge. We get an error message saying:

```
Auto-merging main.cpp
CONFLICT (content): Merge conflict in main.cpp
Automatic merge failed; fix conflicts and then commit the result.
```

This error is called a "merge conflict" and is one of the hardest concepts for new git users to understand. Why did this happen?

In our hotfix branch above, git automatically merged the main.cpp file for us. It could do this because the main.cpp file in the `master` branch did not change after we created the bugfix branch, in other words the hotpatch branch was ahead but not behind `master`. Unfortunately, after we merged the hotfix branch into `master`, this changed the main.cpp file. Now when git tries to merge our changes from the `<github-username>/add-user-input` branch, it doesn't know which parts to keep from `<github-username>/add-user-input`, and which parts to keep from the hotfix branch. We have to tell git how to do this manually.

If you inspect the contents of the main.cpp file, you'll see something like:

```
#include <iostream>
#include <string>

int main()
{
<<<<<<< HEAD
    std::cout << "hello git!" << std::endl;
    Std::cout << “git is easy?” << std::endl;
    return 1;
=======
    std::string name;
    std::cout << "What is your name?" << std::endl;
    std::cin >> name;
    std:::cout << "Hello " << name << "!" << std::endl;

    return 0;
>>>>>>> <github-username>/add-user-input
}
```

As you can see, the file is divided into several sections. Any line not between the `<<<<<<<<` and `>>>>>>>>` lines is common to both versions of main.cpp. The lines between `<<<<<<<< HEAD` and `=======` belong only to the version in the current branch (`master`). And the lines between `=======` and `>>>>>>>> <github-username>/add-user-input` belong only to the `<github-username>/add-user-input` branch (the branch you are merging in).

The key to solving a merge conflict is to edit the lines between `<<<<<<<` and `>>>>>>>` to include only the correct information between the two branches. In our case, we want the return statement from the master branch, and all of the input/output from the `<github-username>/add-user-input` branch. So we should modify the main.cpp file to be:

```
#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "What is your name?" << std::endl;
    std::cin >> name;
    std::cout << "Hello " << name << "!" << std::endl;

    return 0;
}
```

Most of the changes you’ll need to make will be between the special markers that represent the conflicting code, however you will sometimes have to make changes outside of these special markers. This is usually because you made changes that didn’t conflict somewhere else, but the conflicting code changed some access/mutation pattern and you have to correct the unconflicted code. Whenever you fix a merge conflict yourself, git will assume whatever you did was correct so you should only be doing what's necessary to merge the two branches. This isn’t the time to fix additional bugs, make style changes, or modify an accessor. You should use `--amend` for that work after you’ve fixed the merge to keep the commits clean.

Once we have resolved this merge conflict, we can finalize our merge. We first tell git that we've solved the conflict by adding the conflicting files, then we perform a standard commit. Since git knows we are trying to merge a commit, it will actually generate a generic merging commit message for us.

```
$ git add main.cpp
$ git commit
```

As you can see, resolving merge conflicts is a tedious process. Most projects try to reduce the number of merge conflicts as much as possible. A simple strategy for doing this is using many small source files rather than a few large files, and working on features with little overlap. However, merge conflicts are often unavoidable especially when working with larger teams.

## Git Tag

Often, you’ll want to tag certain git commits because they are special. The most common reason to tag a commit in git is to tag it as a beta or release version, especially when using [semantic versioning schemes](https://semver.org/). Let's assume that our code is now ready for release as a v1.0.0 and tag it as such.

```
$ git tag -a v1.0.0 -m “Initial release”
```

The -m in this case works the same as it does when performing a commit, allowing us to add a message but bypassing the editor to do so. Note that if you wanted to tag a commit besides the current commit you would need to add the commit hash after the version number (but before the message). Normally a 1.0.0 release would have lots of additional notes on the current state of the software, but this is just an example. These tagged versions are stored in a special section of the repository on GitHub along with compressed versions of the source files to make public releases easier.

## Git Push & Pull

While git is a VCS, GitHub is a remote repository which is an important distinction for two reasons. The first is that up until now all the work you’ve done has only been saved locally, so if there is a problem with your computer you would have no backup and therefore no way to recover the files. The second is that because all the changes are local, there is no way for people collaborating with you to see your changes or merge them into their own branches. Go to your GitHub repository for this lab, and you should see that none of the work you've done is listed.

Since we cloned the remote repository from GitHub directly, our local repository is already associated with a remote repository (usually referred to as “remote” or “upstream”). In order to send the changes we’ve made locally to GitHub, we just need to “push” them up to the server (do this now).

```
$ git push
```

This will push all the commits for **the current branch**, not all the branches you have changes for. If there haven’t been any other changes to the remote GitHub version of that branch, then this will simply send the commits to the repo. However, if there have been changes to the branch, perhaps because someone else has also been working on that same branch or changes have been merged into master, then you will first need to “pull” the remote changes, merge them with your work, and then push the merged version to GitHub

```
$ git pull
```

Like git push, git pull will request the changes for **only the current branch**, not all the branches. Git will automatically try and merge the remote changes with your current changes. It may be able to automatically merge or you may need to fix merge conflicts. Either way you then need to

```
$ git commit
$ git push
```

It is also possible to receive the remote changes (also known as upstream changes) without having git automatically attempt to merge them into your branch. For this you would use the following command

```
$ git fetch
```

After this, you can do a git merge to integrate the remote changes. Git pull essentially runs a git fetch and a git merge together in one step. You will be using git push and git pull extensively in your projects for this course, and merge conflicts will likely occur fairly regularly.

## Submission

None of the labs or assignments for this course require direct submissions. Everything will be graded based on your GitHub repositories. Labs will be graded based on the last commit to the repository, while projects will be graded based on specific tags.

