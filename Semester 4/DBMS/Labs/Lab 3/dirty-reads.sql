create or alter procedure ClearDB
AS
	delete from Enrollments;
	delete from Courses;
	delete from Students;
GO

-- init
exec ClearDB;
insert into Students(studentName) values ('Narcis');

set transaction isolation level read uncommitted;
--set transaction isolation level read committed;

begin tran
	select studentName from Students;
	waitfor delay '00:00:5';
	select studentName from Students;
	waitfor delay '00:00:5';
	select studentName from Students;
commit tran

--T1
set transaction isolation level repeatable read
begin tran
	select name from ToyStore;
	--waitfor delay '00:00:5';
	--select name from ToyStore;
--update ToyStore 
--set name = 'Nichiduta'
--where toyStoreId = 2;
commit tran

--create table ToyStore(
--	toyStoreId int primary key,
--	name varchar(50),
--	phoneNo varchar(50),
--	website varchar(50)
--);

--T2
set transaction isolation level repeatable read
begin tran
insert into toyStore values(4, 'Noriel', '0316306808', 'www.noriel.ro');
commit tran