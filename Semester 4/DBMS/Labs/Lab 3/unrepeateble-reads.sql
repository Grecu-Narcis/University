exec ClearDB;

insert into Students(studentName) values ('Narcis');

--set transaction isolation level read committed;
set transaction isolation level repeatable read;

begin tran
	select studentName from Students;
	waitfor delay '00:00:5';
	select studentName from Students;
commit tran

select studentName from Students;