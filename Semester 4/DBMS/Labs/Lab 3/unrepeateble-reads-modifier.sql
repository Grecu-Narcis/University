begin tran
	update Students
	set studentName = 'Unrepeateble Reads'
	where studentName = 'Narcis';
commit tran