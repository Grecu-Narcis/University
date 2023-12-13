use Github;

drop table Versions;

create table Versions(
	versionID int default -1
);


-- modify type of column
create procedure modifyTypeOfColumn
as
	alter table UsersDemo alter column department nvarchar(50) not null;
	
	update Versions
	set versionID = 1;
go

create procedure undoModifyTypeOfColumn
as
	alter table UsersDemo alter column department int;

	update Versions
	set versionID = 0;
go


exec modifyTypeOfColumn
exec undoModifyTypeOfColumn


-- add/remove column
create procedure addColumn
as
	alter table UsersDemo add age int;

	update Versions
	set versionID = 2;
go

create procedure undoAddColumn
as
	alter table UsersDemo drop column age;

	update Versions
	set versionID = 1;
go

exec addColumn
exec undoAddColumn

-- add/remove default constraint
create procedure addDefaultCostraint
as
	alter table UsersDemo add constraint department_default default -1 for department; 

	update Versions
	set versionID = 3;
go

create procedure undoAddDefaultCostraint
as
	alter table UsersDemo drop constraint department_default;
	
	update Versions
	set versionID = 2;
go


exec addDefaultCostraint
exec undoAddDefaultCostraint


--add/remove primary key
create procedure addPrimaryKey
as
	alter table UsersDemo 
	add constraint Pk_Users primary key(userID);

	update Versions
	set versionID = 4;
go

create procedure undoAddPrimaryKey
as
	alter table UsersDemo
	drop constraint Pk_Users;

	update Versions
	set versionID = 3;
go

exec addPrimaryKey;
exec undoAddPrimaryKey;


-- add/remove candidate key
create procedure addCandidateKey
as
	alter table UsersDemo
	add constraint CK_Users UNIQUE(username, email);

	update Versions
	set versionID = 5;
go

create procedure undoAddCandidateKey
as
	alter table UsersDemo
	drop constraint CK_Users;

	update Versions
	set versionID = 4;
go


exec addCandidateKey;
exec undoAddCandidateKey;


-- add/remove foreign key
create procedure addForeignKey
as
	alter table UsersDemo
	add constraint FK_Users foreign key(projectID) references Projects(projectID);

	update Versions
	set versionID = 6;
go

create procedure undoAddForeignKey
as
	alter table UsersDemo
	drop constraint FK_Users;

	update Versions
	set versionID = 5;
go


exec addForeignKey;
exec undoAddForeignKey;


-- create/delete table
create procedure createTable
as
	CREATE TABLE UsersDemo1
	(
		userID int not null,
		username varchar(50),
		email varchar(50),
		password varchar(30),
		department int,
	);

	update Versions
	set versionID = 7;
go

create procedure undoCreateTable
as
	drop table UsersDemo1;

	update Versions
	set versionID = 6;
go


create procedure main @Version int
as
	if @Version > 7 or @Version < 0
	begin
		RAISERROR('There are only 8 versions from 0 up to 7.', 10, 1);
		RETURN
	end

	declare @CurrentVersion as int;
	select @CurrentVersion = versionID from Versions;

	PRINT 'Current Version is: ';
	PRINT @CurrentVersion;

	PRINT 'Required version: ';
	PRINT @Version;

	if @CurrentVersion = @Version
	begin
		PRINT 'We already are on the required version';
		RETURN
	end

	if @Version > @CurrentVersion
	BEGIN
		while @Version != @CurrentVersion
		BEGIN
			IF @CurrentVersion = 0
			BEGIN
				exec modifyTypeOfColumn;
			END

			IF @CurrentVersion = 1
			BEGIN
				exec addColumn;
			END

			IF @CurrentVersion = 2
			BEGIN
				exec addDefaultCostraint;
			END

			IF @CurrentVersion = 3
			BEGIN
				exec addPrimaryKey;
			END

			IF @CurrentVersion = 4
			BEGIN
				exec addCandidateKey;
			END

			IF @CurrentVersion = 5
			BEGIN
				exec addForeignKey;
			END

			IF @CurrentVersion = 6
			BEGIN
				exec createTable;
			END

			select @CurrentVersion = versionID from Versions;
		END
		RETURN
	END

	ELSE
	BEGIN
		while @Version != @CurrentVersion
		BEGIN
			IF @CurrentVersion = 1
			BEGIN
				exec undoModifyTypeOfColumn;
			END

			IF @CurrentVersion = 2
			BEGIN
				exec undoAddColumn;
			END

			IF @CurrentVersion = 3
			BEGIN
				exec undoAddDefaultCostraint;
			END

			IF @CurrentVersion = 4
			BEGIN
				exec undoAddPrimaryKey;
			END

			IF @CurrentVersion = 5
			BEGIN
				exec undoAddCandidateKey;
			END

			IF @CurrentVersion = 6
			BEGIN
				exec undoAddForeignKey;
			END

			IF @CurrentVersion = 7
			BEGIN
				exec undoCreateTable;
			END

			select @CurrentVersion = versionID from Versions;
		END
	END
go


drop procedure main;

update Versions
set versionID = 0;

exec main 6;

select * from versions;

drop procedure modifyTypeOfColumn;
drop procedure undoModifyTypeOfColumn;

drop procedure addColumn;
drop procedure undoAddColumn;

drop procedure addDefaultCostraint;
drop procedure undoAddDefaultCostraint;

drop procedure addPrimaryKey;
drop procedure undoAddPrimaryKey;

drop procedure addCandidateKey;
drop procedure undoAddCandidateKey;

drop procedure addForeignKey;
drop procedure undoAddForeignKey;

drop procedure createTable;
drop procedure undoCreateTable;