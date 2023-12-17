use Github;

/* INSERT QUERIES */

-- Users table

insert into Users (userID, username, email, password)
values
(1, 'JohnDoe', 'john.doe@example.com', 'password1'),
(2, 'JaneSmith', 'jane.smith@example.com', 'password2'),
(3, 'MikeJohnson', 'mike.johnson@example.com', 'password3'),
(4, 'EmilyWhite', 'emily.white@example.com', 'password4'),
(5, 'AlexBrown', 'alex.brown@example.com', 'password5'),
(6, 'Mike Brown', null, 'password6');

insert into Users (userID, username, email, password)
values
(7, 'ChrisEvans', 'chris.evans@example.com', 'password7'),
(8, 'EmmaWatson', 'emma.watson@example.com', 'password8'),
(9, 'RyanGosling', 'ryan.gosling@example.com', 'password9'),
(10, 'OliviaJones', 'olivia.jones@example.com', 'password10'),
(11, 'SarahMiller', 'sarah.miller@example.com', 'password6');


-- VIOLATING QUERY

insert into Users(userID, username, email, password)
values
(2, 'Grecu Narcis', 'narcisgrecu07@gmail.com', null);



/* Repositories table */

insert into Repositories (repoID, repoName, description, userID, creationDate)
values
(1, 'ProjectX', 'A collaborative project', 1, '2023-11-05 08:00:00'),
(2, 'AwesomeApp', 'Building an amazing app', 2, '2023-11-05 09:30:00'),
(3, 'CodePlayground', 'Experimenting with code', 3, '2023-11-05 10:45:00'),
(4, 'DataAnalytics', 'Analyzing data for insights', 4, '2023-11-05 12:15:00'),
(5, 'CreativeDesigns', 'Designing innovative solutions', 5, '2023-11-05 14:00:00');

insert into Repositories (repoID, repoName, description, userID, creationDate)
values
(6, 'WebDevelopment', 'Building responsive websites', 7, '2023-11-06 09:00:00'),
(7, 'MachineLearningProj', 'Exploring ML algorithms', 6, '2023-11-06 10:30:00'),
(8, 'MobileGameDev', 'Creating an exciting mobile game', 9, '2023-11-06 12:00:00'),
(9, 'OpenSourceProject', 'Contributing to open source', 8, '2023-11-06 13:30:00'),
(10, 'SocialMediaApp', 'Developing a social media platform', 2, '2023-11-06 15:00:00');


/* Issues table */

insert into Issues (issueID, title, description, repoID, userID, status)
values
(1, 'BugFix', 'Fixing critical bug', 1, 1, 'Open'),
(2, 'FeatureReq', 'Implement new feature', 2, 2, 'In Progress'),
(3, 'UIUpdate', 'Updating user interface', 3, 3, 'Closed'),
(4, 'DataBug', 'Resolving data-related issue', 4, 4, 'Open'),
(5, 'Security', 'Enhancing security measures', 5, 5, 'In Progress');


/* Commits table */

insert into Commits (commitID, title, message, repoID, userID)
values
(1, 'InitialCommit', 'Initial project commit', 1, 1),
(2, 'FeatureUpdate', 'Adding new feature', 2, 2),
(3, 'BugFix', 'Resolving critical bug', 3, 3),
(4, 'DataAnalysis', 'Analyzing project data', 4, 4),
(5, 'DesignChanges', 'Implementing design changes', 5, 5);


/* Branches table */

insert into Branches (branchID, name, repoID, commitID, creationDate, lastModifiedDate)
values
(1, 'Main', 1, 1, '2023-11-05 08:15:00', '2023-11-05 09:30:00'),
(2, 'FeatureBranch', 2, 2, '2023-11-05 10:00:00', '2023-11-05 11:45:00'),
(3, 'UIUpdates', 3, 3, '2023-11-05 12:30:00', '2023-11-05 13:45:00'),
(4, 'DataBranch', 4, 4, '2023-11-05 14:30:00', '2023-11-05 15:45:00'),
(5, 'DesignBranch', 5, 5, '2023-11-05 16:00:00', '2023-11-05 17:15:00');


/* PullRequests table */

insert into PullRequests (prID, title, description, sourceBranchID, destinationBranchID, userID, creationDate)
values
(1, 'FeatureMerge', 'Merge feature to main', 2, 1, 2, '2023-11-05 09:45:00'),
(2, 'UIEnhancements', 'Request to merge UI updates', 3, 2, 5, '2023-11-05 11:00:00'),
(3, 'BugFixMerge', 'Merge bug fix to main', 4, 3, 5, '2023-11-05 13:00:00'),
(4, 'DataAnalysisPR', 'Pull request for data branch', 5, 4, 1, '2023-11-05 15:00:00'),
(5, 'DesignMerge', 'Merge design changes', 5, 1, 5, '2023-11-05 17:30:00');


/* Documentations table */

insert into Documentations (documentationID, title, content, repoID, userID, creationDate, lastModifiedDate)
values
(1, 'ProjectGuide', 'Guide for the project', 1, 1, '2023-11-05 10:00:00', '2023-11-05 11:30:00'),
(2, 'AppManual', 'Manual for the app', 2, 2, '2023-11-05 12:00:00', '2023-11-05 13:45:00'),
(3, 'CodePlaybook', 'Playbook for the code', 3, 3, '2023-11-05 14:00:00', '2023-11-05 15:15:00'),
(4, 'DataGuide', 'Guide for data analysis', 4, 4, '2023-11-05 16:00:00', '2023-11-05 17:30:00'),
(5, 'DesignManual', 'Manual for design changes', 5, 5, '2023-11-05 18:00:00', '2023-11-05 19:15:00');


/* Projects table */

insert into Projects (projectID, name, description, repoID, projectManagerID, creationDate)
values
(1, 'TeamCollab', 'Collaborative project', 1, 1, '2023-11-05 10:45:00'),
(2, 'MobileAppDev', 'Developing a mobile application', 2, 2, '2023-11-05 12:30:00'),
(3, 'DataAnalysis', 'Analyzing project data', 3, 3, '2023-11-05 14:15:00'),
(4, 'DesignProject', 'Implementing design changes', 4, 4, '2023-11-05 16:00:00'),
(5, 'InnovationLab', 'Exploring innovative solutions', 5, 5, '2023-11-05 18:00:00');


/* Followers table */

insert into Followers (followerID, followerUserID, followedUserID, followDate)
values
(1, 1, 2, '2023-11-05 11:00:00'),
(2, 2, 3, '2023-11-05 13:00:00'),
(3, 3, 4, '2023-11-05 15:00:00'),
(4, 4, 5, '2023-11-05 17:00:00'),
(5, 5, 1, '2023-11-05 19:00:00');


/* Tasks table */

insert into Tasks (taskID, projectID, title, description, assignedUserID, dueDate, completionDate, status)
values
(1, 1, 'Task1', 'Collaborative task', 2, '2023-11-06 12:00:00', '2023-11-06 15:30:00', 'Completed'),
(2, 2, 'FeatureTask', 'Implementing new feature', 3, '2023-11-07 14:00:00', '2023-11-07 16:45:00', 'In Progress'),
(3, 3, 'AnalysisTask', 'Analyzing project data', 4, '2023-11-08 10:00:00', '2023-11-08 13:15:00', 'Completed'),
(4, 4, 'DesignTask', 'Implementing design changes', 5, '2023-11-09 11:30:00', '2023-11-09 15:00:00', 'In Progress'),
(5, 5, 'InnovationTask', 'Exploring innovative ideas', 1, '2023-11-10 13:00:00', '2023-11-10 17:30:00', 'Pending');


/* ProjectMembers table */

insert into ProjectMembers (projectMemberID, projectID, userID, role, joinDate)
values
(1, 1, 1, 'Team Member', '2023-11-05 11:30:00'),
(2, 2, 2, 'Developer', '2023-11-05 13:30:00'),
(3, 3, 3, 'Analyst', '2023-11-05 15:30:00'),
(4, 4, 4, 'Designer', '2023-11-05 17:30:00'),
(5, 5, 5, 'Innovator', '2023-11-05 19:30:00');


/* Collaborators table */

insert into Collaborators (collaboratorID, repoID, userID, permissionLevel, joinDate)
values
(1, 1, 2, 'Read/Write', '2023-11-05 12:00:00'),
(2, 2, 3, 'Read Only', '2023-11-05 14:00:00'),
(3, 3, 4, 'Admin', '2023-11-05 16:00:00'),
(4, 4, 5, 'Read/Write', '2023-11-05 18:00:00'),
(5, 5, 1, 'Admin', '2023-11-05 20:00:00');



-- UPDATE QUERIES

update Collaborators 
set permissionLevel = 'Admin'
where userID = 1 or userID = 5;


update ProjectMembers
set role = 'manager'
where projectID <= 2;


update Users
set email = 'default'
where email is null;


-- DELETE QUERIES
delete from Repositories
where repoID between 6 and 10 
	or userID in (7, 8, 9);

select * from Repositories;

delete from Users
where username like 'Olivia%';


-- Requirement a) UNION
select U.userID
from Users U
where U.username = 'admin' or U.username like 'Mike %'
union all
select R.userID
from Repositories R;

select R.repoID
from Repositories R
where R.repoName like 'C%'
union
select P.repoID
from Projects P
where P.name like 'D%';

-- Requirement b) INTERSECTION
select R.repoID
from Repositories R
where R.userID in (2, 3, 5)
intersect
select P.repoID
from Projects P
where P.projectID in (1, 3, 4);

select U.userID
from Users U
where U.userID in (1, 2, 3)
intersect
select C.userID
from Collaborators C
where C.repoID in (1, 2, 3);


-- Requirement c) EXCEPT
select U.userID
from Users U
where U.userID not in (4, 5, 6)
except
select C.userID
from Collaborators C
where C.repoID not in (10, 12, 43);

select distinct R.repoID
from Repositories R
where R.userID not in (1, 4, 6, 7, 8, 9, 10)
except
select P.repoID
from Projects P
where P.projectID not in (2, 5, 6, 7, 8, 9, 10);


-- Requirement d) JOIN
select U.email, U.password, R.repoName, P.name
from Users U
full join Repositories R on R.userID = U.userID
full join Projects P on P.repoID = R.repoID;

select U.email, U.password, R.repoName
from Users U
left join Repositories R on R.userID = U.userID;

select B.name, R.repoName
from Branches B
right join Repositories R on B.repoID = R.repoID;

select U.username, PM.role, P.name, R.repoName, C.permissionLevel
from Users U
inner join ProjectMembers PM on U.userID = PM.userID
inner join Projects P on P.projectID = PM.projectID
inner join Repositories R on P.repoID = R.repoID
inner join Collaborators C on C.repoID = R.repoID;


-- Requirement e) IN operator and SUBQUERY in WHERE
select U.username
from Users U
where U.userID in
	(select distinct R.userID
	from Repositories R
	where R.repoID in
		(select P.repoID
		from Projects P
		where P.projectID = 2 or P.projectID = 5
		)
	);	

select R.repoName, R.userID
from Repositories R
where R.repoID in
	(select top 10 P.repoID
	from Projects P
	where P.projectManagerID between 2 and 5
	order by P.creationDate
	);

-- Requirement f) 2 queries with Exists
select U.username
from Users U
where exists (
	select * 
	from Repositories R
	where R.userID > 5 and R.userID < 8);

select PM.userID
from ProjectMembers PM
where exists (
	select * 
	from Projects P
	where P.projectManagerID = PM.userID);


-- Requirement g) 2 queries with SELECT in FROM

select Q.repoName
from (select *
		from Repositories R 
		where R.repoID not in (1,2,3)
		) Q;

select top 3 R.name
from (select *
		from Projects P 
		where P.projectID in (1,2,3)
		) R
where R.repoID = 2 or R.repoID = 5;


-- Requirement h) 
select count(*)
from Tasks T
group by T.projectID;

select count(*)
from Repositories R
group by R.userID
having R.repoID > 2 or R.repoID < 5;

select PM.projectID
from ProjectMembers PM
group by PM.projectID
having PM.projectID in 
	(
		select P.projectID
		from Projects P
	);

select C.permissionLevel
from  Collaborators C
group by C.permissionLevel
having avg (C.repoID) > any 
	(
		select P.projectID
		from Projects P
	);


-- Requirement i)

SELECT *
FROM Users U
WHERE U.userID > ALL
    (SELECT R.userID
     FROM Repositories R
	 where R.repoID between 3 and 6
    );

select *
from Repositories R
where R.creationDate > any
	(select B.lastModifiedDate
	from Branches B
	);

select *
from Issues I
where I.repoID != all
	(select R.repoID
	from Repositories R
	where R.repoID > 3
	);

SELECT *
FROM Users U
WHERE U.userID = any
    (SELECT R.userID
     FROM Repositories R
	 where R.repoID between 3 and 6
    );

-- Rewrite with aggregation operators

SELECT *
FROM Users U
WHERE U.userID >
    (SELECT max(R.userID)
     FROM Repositories R
	 where R.repoID between 3 and 6
    );

select *
from Repositories R
where R.creationDate > 
	(select min(B.lastModifiedDate)
	from Branches B
	);

-- Rewrite using IN/NOT IN

select *
from Issues I
where I.repoID not in
	(select R.repoID
	from Repositories R
	where R.repoID > 3
	);

SELECT *
FROM Users U
WHERE U.userID in
    (SELECT R.userID
     FROM Repositories R
	 where R.repoID between 3 and 6
    );