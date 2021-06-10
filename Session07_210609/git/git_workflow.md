# About Version Control #

## No Flow ##
* Everyone just commits directly to master without using branches.
* We do not recommend this for collaborating in this course (but you can use this e.g. for backup purposes)
![No Flow](./no-flow.png "No Flow")

## Git Flow ##
* created by Vincent Driessen (2010)
* based in two main branches with infinite lifetime
	* `main` - contains production code, development code will be merged into `master`
	* `develop` - contains pre-production code. When the features are finished, they are merged into `develop`

	During the development cycle, a variety of supporting branches are used:  
	* `feature-*` - used to develop new features, branch off from `develop` and must merge into `develop`
	* `hotfix-*` - used to act immediatley upon an undesired status of `master`, must merge into `master` and `develop`
	* `release-*` - preparation of a new production release, branch off from `develop` and must merge into `master` and `develop`

![Git Flow](./git-flow.png "Git Flow")

### Advantages ###
* ensures a clean state of branches at any moment in life cycle of project
* branches naming follows systematic pattern
* supported on most git tools
* ideal if there are multiple versions in production

### Disadvantages ###
* the Git history becomes unreadable
* the master/develop split is considered redundant and makes [Continuous Delivery and Continous Integration][2] harder
* not recommended when maintain single version in production

## GitHub Flow ##

* lightweight workflow, created by GitHub in 2011
* offers the distributed version control and source code management (SCM) functionality of Git, plus its own features
* provides access control and several collaboration features such as bug tracking , feature requests, task management, and wikis for every project
* GitHub allows a user to host a static website

* follows six principles
	1. anything in the master ist deployable
	2. for every new work, create a branch off from master (descriptive name)
	3. commit to that branch locally and push to the same branch on server
	4. for feedback, help or merge, open a pull request
	5. after someones review and signed off on the feature, you can merge it into `master`
	6. once it is merged and pushed to `master`, you can and *should* deploy immediately

![GitHub Flow](./github-flow.png "GitHub Flow")
### Advantages ###
* CD/CI friendly
* simpler than Git Flow
* ideal when maintain single version in production

### Disadvantages ###
* production code can become unstable most easily
* not adequate when it needs release plans
* doesn't resolve depluy, environments, releases and issues
* not recommended for maintaining multiple versions in production

## GitLab Flow ##
* created 2014
* offers the distributed version control and source code management (SCM) functionality of Git, plus its own features
* combines feature-driven-development and feature branches with issue tracking
* environment branches: `staging`, `production
* provides a Git-repository manager providing wiki, issue-tracking and continuous integration/continuous deployment pipeline features
* provides project management tools such as Issue Tracker, Group Milestones, Issue Boards, Roadmaps, Time Tracking, and more
* GitLab allows a user to host a static website
* based on 11 rules:
	1. use feature branches, no direct commits on `master`
	2. test all commits, not only ones on `master`
	3. run all tests on all commits
	4. perform code reviews before merges into master, not afterwards
	5. deployments are automatic, based on branches or tags
	6. tags are set by the user, not by CI
	7. releases are based on tags
	8. pushed commits are never rebased
	9. everyone starts from `master`, and targets `master`
	10. fix bugs in `master` first and release branches second
	11. commit messages reflect intent
	
	![GitLab Flow](./gitlab-flow.png "GitLab Flow")
	
### Advantages ###
* defines how to make Continous Integration and Continous Delivery
* cleaner git history, less messy and more readable
* ideal for single version in production

### Disadvantages ###
* more complex than GitHub Flow
* can become complex as Git Flow if maintaining multiple versions in production

## One Flow ##
* created by Adam Ruka 2015
* every new production release is based on the previous release
* it has no `develop`branch
* 

### Advantages ###
* cleaner git history, less messy and more readable
* flexible according to team decisions
* ideal for single version in production

### Disadvantages ###
* not recommended for Continous Integration and Continous Delivery
* not recommended when maintaining multiple versions in production  

more about [One Flow][4]

overviews used for this doc can be found [here][3] or [here][0]

[0]: https://medium.com/@patrickporto/4-branching-workflows-for-git-30d0aaee7bf "source"
[1]: https://github.com/nvie/gitflow "extensions"
[2]: https://www.redhat.com/de/topics/devops/what-is-ci-cd "CD/CI"
[3]: https://blog.programster.org/git-workflows "GitFlows"
[4]:https://www.endoflineblog.com/implementing-oneflow-on-github-bitbucket-and-gitlab "One Flow"