create or alter procedure AddStudent @StudentName varchar(50)
AS
	IF (@StudentName is null)
	BEGIN
		RAISERROR('Student name cannot be null', 16, 1);
	END

	insert into Students(studentName) values (@StudentName);
GO

create or alter procedure AddCourse @CourseName varchar(50)
AS
	IF (@CourseName is null)
	BEGIN
		RAISERROR('Course name cannot be null', 16, 1);
	END

	insert into Courses(courseName) values (@CourseName);
GO

create or alter procedure AddStudentToCourse @StudentName varchar(50), @CourseName varchar(50)
AS
	DECLARE @studentId int;
	select @studentId = studentId from Students where studentName = @StudentName;

	DECLARE @courseId int;
	select @courseId = courseId from Courses where courseName = @CourseName;

	IF (@studentId is null)
	BEGIN
		RAISERROR('Student not found', 16, 1);
		RETURN;
	END

	if (@courseId is null)
	BEGIN
		RAISERROR('Course not found', 16, 1);
		RETURN;
	END

	insert into Enrollments(studentId, courseId) values (@studentId, @courseId);
GO

create or alter procedure RollbackInsert @studentName varchar(50), @courseName varchar(50)
AS
	BEGIN TRAN
		BEGIN TRY
			EXEC AddStudent @studentName;
			EXEC AddCourse @courseName;
			EXEC AddStudentToCourse @studentName, @courseName;
		END TRY

		BEGIN CATCH
			ROLLBACK TRAN
			RETURN
		END CATCH
	COMMIT TRAN
GO

exec ClearDB;

exec RollbackInsert 'Narcis', 'DBMS'; -- success
exec RollbackInsert 'Fail', null; -- fails

select * from Students;
select * from Courses;
select * from Enrollments;