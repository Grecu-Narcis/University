begin tran
	update Students
	set studentName = 'Dirty Read'
	where studentName = 'Narcis';

	waitfor delay '00:00:5';
rollback tran