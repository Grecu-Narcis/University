use Github;

/*
CREATE TABLE Users
(
	userID int,
	username varchar(50),
	email varchar(50),
	password varchar(30),

	primary key(userID)
);
*/

/*
create table Repositories
(
	repoID int IDENTITY(1,1),
	repoName varchar(100),
	description varchar(500),
	userID int,

	PRIMARY KEY(repoID),
	FOREIGN KEY(userID) REFERENCES Users(userID)
);

alter table Repositories alter column repoName varchar(100) not null;
alter table Repositories alter column userID int not null;

alter table Repositories add creationDate datetime not null;
*/

/*	
create table Issues
(
	issueID int,
	title varchar(20) not null,
	description varchar(500),
	repoID int not null,
	userID int not null,

	PRIMARY KEY(issueID),
	FOREIGN KEY(repoID) REFERENCES Repositories(repoID),
	FOREIGN KEY(userID) REFERENCES Users(userID)
);

alter table issues add status varchar(10) not null;
*/

/*
create table Commits
(
	commitID int,
	title varchar(50) not null,
	message varchar(500),
	repoID int not null,
	userID int not null,

	PRIMARY KEY(commitID),
	FOREIGN KEY(repoID) REFERENCES Repositories(repoID),
	FOREIGN KEY(userID) REFERENCES Users(userID)
);
*/

/*
create table Branches
(
	branchID int,
	name varchar(100),
	repoID int not null,
	commitID int not null,
	creationDate datetime not null,
	lastModifiedDate datetime not null,

	PRIMARY KEY(branchID),
	FOREIGN KEY(repoID) REFERENCES Repositories(repoID),
	FOREIGN KEY(commitID) REFERENCES Commits(commitID)
);
*/

/*
create table PullRequests
(
	prID int,
	title varchar(50) not null,
	description varchar(500),
	sourceBranchID int,
	destinationBranchID int,
	userID int,
	creationDate datetime not null,

	PRIMARY KEY(prID),
	FOREIGN KEY(sourceBranchID) references Branches(branchID),
	FOREIGN KEY(destinationBranchID) references Branches(branchID)
);
*/

/*
create table Documentations
(
	documentationID int,
	title varchar(50) not null,
	content varchar(1000), 
	repoID int not null,
	userID int not null,
	creationDate datetime not null,
	lastModifiedDate datetime not null,

	primary key(documentationID),
	foreign key(repoID) references Repositories(repoID),
	foreign key(userID) references Users(userID)
);
*/

/*
create table Files
(
	fileID int,
	name varchar(100),
	path varchar(200),
	repoID int not null,
	userID int not null,
	uploadDate datetime not null,
	lastModifiedDate datetime not null,

	primary key(fileID),
	foreign key(repoID) references Repositories(repoID),
	foreign key(userID) references Users(userID)
);
*/

/*
create table Projects
(
	projectID int,
	name varchar(100) not null,
	description varchar(500),
	repoID int not null,
	projectManagerID int not null,
	creationDate datetime not null,

	primary key(projectID),
	foreign key(repoID) references Repositories(repoID),
	foreign key(projectManagerID) references Users(userID)
);
*/
/*
create table Followers
(
	followerID int,
	followerUserID int not null,
	followedUserID int not null,
	followDate datetime not null,

	primary key(followerID),
	foreign key(followerUserID) references Users(userID),
	foreign key(followedUserID) references Users(userID)
);

create table Tasks
(
	taskID int,
	projectID int not null,
	title varchar(50) not null,
	description varchar(500),
	assignedUserID int not null,
	dueDate datetime not null,
	completionDate datetime not null,
	status varchar(10) not null,

	primary key(taskID),
	foreign key(projectID) references Projects(projectID),
	foreign key(assignedUserID) references Users(userID)
);
*/

/*
create table ProjectMembers(
	projectMemberID int primary key,
	projectID int,
	userID int,
	role varchar(250),
	joinDate datetime,
	
	foreign key(projectID) references Projects(projectID),
	foreign key(userID) references Users(userID)
);


alter table ProjectMembers alter column projectMemberID int not null;
*/

/*
create table Collaborators(
	collaboratorID int primary key,
	repoID int,
	userID int,
	permissionLevel varchar(250),
	joinDate datetime,
	
	foreign key(repoID) references Repositories(repoID),
	foreign key(userID) references Users(userID)
);
*/