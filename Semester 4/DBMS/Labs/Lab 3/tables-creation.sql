create table Students(
	studentId int IDENTITY(1, 1),
	studentName varchar(50) not null,
	primary key (studentId)
);

create table Courses(
	courseId int IDENTITY(1, 1) primary key,
	courseName varchar(50) not null
);

create table Enrollments(
	studentId int,
	courseId int,
	foreign key (studentId) references Students(studentId),
	foreign key (courseId) references Courses(courseId)
);