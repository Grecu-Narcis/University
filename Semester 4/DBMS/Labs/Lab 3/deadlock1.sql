exec ClearDB;

insert into Students(studentName) values ('Narcis');
insert into Courses(courseName) values ('DBMS');

begin tran
	update Students set studentName = 'Test1' where studentName = 'Narcis';
	
	waitfor delay '00:00:10';
	
	update Courses set courseName = 'Test1' where courseName = 'DBMS';
commit tran