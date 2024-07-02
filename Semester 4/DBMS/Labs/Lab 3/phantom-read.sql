exec ClearDB;

insert into Students(studentName) values ('Narcis Grecu');

set transaction isolation level repeatable read;
set transaction isolation level serializable;

begin tran
	select studentName from Students where studentName like '%Narcis%';
	waitfor delay '00:00:10';
	select studentName from Students where studentName like '%Narcis%';
commit tran

select studentName from Students where studentName like '%Narcis%';