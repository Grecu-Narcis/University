create or alter procedure NoRollbackInsert @studentName varchar(50), @courseName varchar(50)
AS
	BEGIN TRAN
		DECLARE @errors int;
		SET @errors = 0;

		BEGIN TRY
			EXEC AddStudent @studentName;
		END TRY

		BEGIN CATCH
			SET @errors = @errors + 1;
		END CATCH

		BEGIN TRY
			EXEC AddCourse @courseName;
		END TRY

		BEGIN CATCH
			SET @errors = @errors + 1;
		END CATCH

		IF (@errors = 0) BEGIN
			BEGIN TRY
				EXEC AddStudentToCourse @studentName, @courseName;
			END TRY

			BEGIN CATCH
			END CATCH
		END
	COMMIT TRAN
GO

exec ClearDB;

exec NoRollbackInsert 'Grecu', 'DB'; -- success
exec NoRollbackInsert 'Test', null; -- fail

select * from Students;
select * from Courses;
select * from Enrollments;