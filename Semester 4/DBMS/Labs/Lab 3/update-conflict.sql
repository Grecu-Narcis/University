exec ClearDB;

insert into Students(studentName) values ('Narcis');

SET TRANSACTION ISOLATION LEVEL SNAPSHOT;

begin tran
	select studentName from Students where studentName = 'Narcis';

	waitfor delay '00:00:10';

	update Students set studentName = 'Update1' where studentName = 'Narcis'; 
	select studentName from Students;
commit tran

select * from Students;

ALTER DATABASE DBMS SET ALLOW_SNAPSHOT_ISOLATION ON;
ALTER DATABASE DBMS SET READ_COMMITTED_SNAPSHOT ON;