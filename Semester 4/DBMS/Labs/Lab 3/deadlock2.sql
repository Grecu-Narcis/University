begin tran
	update Courses set courseName = 'Test2' where courseName = 'DBMS';
	
	waitfor delay '00:00:10';
	
	update Students set studentName = 'Test2' where studentName = 'Narcis';	
commit tran