

--- Table Tables – with the names of the tables considered

Insert into Tables(Name)
values 
('TestUsers'),
('TestOrders'),
('TestOrderItems');

SELECT * FROM Tables;
GO

--- Table Views – with the names of the views considered (not necessarily created on the tables considered in the table Tables, but preferable to see the time results)

-- pentru un PK
CREATE VIEW View_1 AS
 SELECT *
 FROM TestUsers;
GO

-- pentru un PK si cel putin un FK
CREATE VIEW View_2 AS
SELECT U.userID AS userID, O.orderID AS orderID 
FROM TestUsers AS U
INNER JOIN TestOrders AS O ON U.userID = O.userID;
GO

-- pentru doua PK
CREATE VIEW View_3 AS
SELECT
    I.OrderID, count(I.itemID) as NumberOfItems
FROM
    TestOrderItems AS I
INNER JOIN
    TestOrders AS O ON I.OrderID = O.OrderID
GROUP BY
    I.OrderID;
GO

----- Adaug view-urile in tabel -----

INSERT INTO Views VALUES
	('View_1'),
	('View_2'),
	('View_3');
GO

SELECT * FROM Views;

----- Adaug testele de efectuat in tabela Tests -----

INSERT INTO Tests VALUES
	('test_TestUsers'),
	('test_TestOrders'),
	('test_TestOrderItems')
GO

SELECT * FROM Tests;

----- Fac legatura intre teste si tabele -----

INSERT INTO TestTables VALUES
	(1, 1),
	(2, 2),
	(3, 3);

SELECT * FROM TestTables;
GO

----- Fac legatura intre teste si view-uri -----


INSERT INTO TestViews VALUES
	(1, 1),
	(2, 2),
	(3, 3);

SELECT * FROM TestViews;
GO

---- Creez procedurile de inserare -----

CREATE OR ALTER PROCEDURE ins_test_TestUsers
AS
BEGIN
	insert into TestUsers DEFAULT VALUES;
END

GO
CREATE OR ALTER PROCEDURE ins_test_TestOrders
AS
BEGIN
	DECLARE @maxID as int;
	select @maxID = max(userID) from TestUsers;

	insert into TestOrders(UserID) values (@maxID);
END


GO
CREATE OR ALTER PROCEDURE ins_test_TestOrderItems
AS
BEGIN
	DECLARE @maxID as int;
	select @maxID = max(orderID) from TestOrders;
    insert into TestOrderItems(OrderID, ItemID) values (@maxID, 1);
END
GO

-- pentru users
GO
CREATE OR ALTER PROCEDURE del_test_TestUsers
AS
BEGIN
	delete from TestOrderItems 
	where OrderID in
		(select O.OrderID 
		from TestOrders as O
		where O.UserID in
			(select U.userID
			from TestUsers as U
			)
		);

	delete from TestOrders
	where UserID in 
		(select U.userID
		from TestUsers as U);

	delete from TestUsers;
END


-- pentru Clienti
GO
CREATE OR ALTER PROCEDURE del_test_TestOrders
AS
BEGIN
    delete from TestOrderItems 
	where OrderID in
		(select O.OrderID 
		from TestOrders as O);

	delete from TestOrders;
END

GO
CREATE OR ALTER PROCEDURE del_test_TestOrderItems
AS
BEGIN
	delete from TestOrderItems;
END

----- Creez procedura generala de inserare -----
GO
CREATE PROCEDURE inserare_testgen
@idTest INT
AS
BEGIN
	DECLARE @numeTest NVARCHAR(50) = (SELECT T.Name FROM Tests T WHERE T.TestID = @idTest);
	DECLARE @numeTabela NVARCHAR(50);
	DECLARE @procedura NVARCHAR(50);
	DECLARE @tableID int;

	DECLARE cursorTab CURSOR FORWARD_ONLY FOR
		SELECT Tables.Name, Test.TableID 
		FROM TestTables Test
		INNER JOIN Tables ON Test.TableID = Tables.TableID
		WHERE Test.TestID = @idTest;

	OPEN cursorTab;

	FETCH NEXT FROM cursorTab INTO @numeTabela, @tableID;
	WHILE (@numeTest NOT LIKE N'test_' + @numeTabela) AND (@@FETCH_STATUS = 0)
	BEGIN
		SET @procedura = N'ins_test_' + @numeTabela;
		EXECUTE @procedura;

		FETCH NEXT FROM cursorTab INTO @numeTabela, @tableID;
	END

	SET @procedura = N'ins_test_' + @numeTabela;
	EXECUTE @procedura;

	CLOSE cursorTab;
	DEALLOCATE cursorTab;
END

EXECUTE inserare_testgen 3;

SELECT * FROM TestUsers;
SELECT * FROM TestOrders;
SELECT * FROM TestOrderItems;
----- Creez procedura generala de stergere -----

GO
CREATE PROCEDURE stergere_testgen
@idTest INT
AS
BEGIN
	DECLARE @numeTest NVARCHAR(50) = (SELECT T.Name FROM Tests T WHERE T.TestID = @idTest);
	DECLARE @numeTabela NVARCHAR(50);
	DECLARE @procedura NVARCHAR(50);

	DECLARE @tableID int;

	DECLARE cursorTab CURSOR FORWARD_ONLY FOR
		SELECT Tables.Name, Test.TableID 
		FROM TestTables Test
		INNER JOIN Tables ON Test.TableID = Tables.TableID
		WHERE Test.TestID = @idTest;

	OPEN cursorTab;

	FETCH NEXT FROM cursorTab INTO @numeTabela, @tableID;
	WHILE (@numeTest NOT LIKE N'test_' + @numeTabela) AND (@@FETCH_STATUS = 0)
	BEGIN
		SET @procedura = N'del_test_' + @numeTabela;
		EXECUTE @procedura;
		FETCH NEXT FROM cursorTab INTO @numeTabela, @tableID;
	END

	SET @procedura = N'del_test_' + @numeTabela;
	EXECUTE @procedura;

	CLOSE cursorTab;
	DEALLOCATE cursorTab;
END

EXECUTE stergere_testgen 1;

SELECT * FROM TestUsers;
SELECT * FROM TestOrders;
SELECT * FROM TestOrderItems;

----- Creez procedura generala pentru view-uri -----

GO
CREATE OR ALTER PROCEDURE view_testgen
@idTest INT
AS
BEGIN
	DECLARE @viewName NVARCHAR(50) = 
		(SELECT V.Name FROM Views V
		INNER JOIN TestViews TV ON TV.ViewID = V.ViewID
		WHERE TV.TestID = @idTest);

	DECLARE @comanda NVARCHAR(55) = 
		N'SELECT * FROM ' + @viewName;
	
	EXECUTE (@comanda);
END

EXECUTE view_testgen 3;

----- Creez procedura de rulare a unui test -----

GO

CREATE PROCEDURE run_test
@idTest INT
AS
BEGIN
	DECLARE @startTime DATETIME;
	DECLARE @endTime DATETIME;

	SET @startTime = GETDATE();
	
	EXECUTE stergere_testgen @idTest;
	EXECUTE inserare_testgen @idTest;
		
	EXECUTE view_testgen @idTest;

	SET @endTime = GETDATE();

	-- var pt insert
	DECLARE @testName NVARCHAR(50) =
		(SELECT T.Name FROM Tests T WHERE T.TestID = @idTest);
	
	INSERT INTO TestRuns VALUES (@testName, @startTime, @endTime);

	DECLARE @viewID INT =
		(SELECT V.ViewID FROM Views V
		INNER JOIN TestViews TV ON TV.ViewID = V.ViewID
		WHERE TV.TestID = @idTest);
	
	DECLARE @tableID INT =
		(SELECT TB.TableID FROM Tests T
		INNER JOIN TestTables TT ON T.TestID = TT.TestID
		INNER JOIN Tables TB ON TB.TableID = TT.TableID
		WHERE T.TestID = @idTest AND 
		T.Name LIKE N'test_' + TB.Name);
	
	DECLARE @testRunID INT = 
		(SELECT TOP 1 T.TestRunID FROM TestRuns T
		WHERE T.Description = @testName);
	
	INSERT INTO TestRunTables VALUES (@testRunID, @tableID, @startTime, @endTime);
	INSERT INTO TestRunViews VALUES (@testRunID, @viewID, @startTime, @endTime);

	PRINT CHAR(10) + '---> TEST COMPLETAT CU SUCCES IN ' + 
		 CONVERT(VARCHAR(10), DATEDIFF(millisecond, @startTime, @endTime)) +
		 ' milisecunde. <---'
END

EXECUTE run_test 1;
GO

select * from TestRunTables;
select * from TestRunViews;

DROP PROCEDURE run_test

GO

SELECT * FROM Sala;
SELECT * FROM Clienti;
SELECT * FROM Colaborare;
SELECT * FROM Antrenori;

SELECT * FROM Tables;
SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;
SELECT * FROM Tests;
SELECT * FROM TestTables;
SELECT * FROM TestViews;
SELECT * FROM Views;

DROP TABLE Tables
DROP TABLE TestRuns
DROP TABLE TestRunTables
DROP TABLE TestRunViews
DROP TABLE Tests
DROP TABLE TestTables
DROP TABLE TestViews
DROP TABLE Views