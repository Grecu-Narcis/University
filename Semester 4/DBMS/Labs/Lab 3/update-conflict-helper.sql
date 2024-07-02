SET TRANSACTION ISOLATION LEVEL SNAPSHOT;

begin tran
	select studentName from Students where studentName = 'Narcis';

	waitfor delay '00:00:05';

	update Students set studentName = 'Update2' where studentName = 'Narcis'; 
commit tran