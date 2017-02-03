# Quick and dirty guide to git

1. Open git bash into the repository where the project is located (navigate to the project repo on your computer, right click --> git bash)
2. Configure origin (DO IT ONCE, AND FORGET IT FOR THE REST OF THE SEMESTER)
    * If you already have an origin setup, you can remove it with 
	* **git remote remove origin**
	* Then --> **git remote add --track master origin ADDRESS_YOU_USE_TO_CONNECT_TO_GIT_EITHER_SSH_OR_HTTPS**
	* This command makes it so that origin points towards the branch master on the git online repository
3. Configure your push behavior (DO IT ONCE AND FORGET IT)
    * **git config --global push.default current** --> This command will make it so that git infers the origin of your branch when you are pushing it. 
	* See http://stackoverflow.com/questions/6089294/why-do-i-need-to-do-set-upstream-all-the-time
4. Make sure you are in master
    * If you are not in master, switch to master with the command:
    * **git checkout master**
5. Pull from the server to get the last version of the project
    * **git pull**
6. Create a new branch for you to work on
    * **git checkout -b BRANCH_NAME**
7. Once you have made your modifications, stage your modified files by:
    * **git status** --> This command allow you to see modifications tracked by git in your project
	* **git add MODIFIED_FILE_NAME** --> This command allow you to include specific files in a commit
	* You can use the command **git add *** to add every modified files.
8. Commit the changes you have added in step 5
    * **git commit -m "COMMIT_MESSAGE"**
9. Repeat steps 7 and 8 until you are satisfied with the state of your branch and want to merge it to the project
10. Fetch the modifications from the server into your branch
    * **git fetch origin**
11. Merge those modifications into your branch
    * **git merge origin/master**
12. If there are merge conflicts, modify your files until the conflicts are resolved. 
    * You can use the command **git diff YOUR_BRANCH origin/master** to view the changes between one branch and master.
13. Push your branch to master
    * **git push -u**
14. On git's website, ask for a pull request on your branch.