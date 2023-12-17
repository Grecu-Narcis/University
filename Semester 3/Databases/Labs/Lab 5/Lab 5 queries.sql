create table Ta (
    aid int primary key,
    a2 int unique,
    x int
)
GO

create table Tb (
    bid int primary key,
    b2 int,
    x int
)
GO

create table Tc (
    cid int primary key,
    aid int references Ta(aid),
    bid int references Tb(bid)
)
GO

create or alter procedure insertIntoTa(@rows int) 
as
    declare @max int
    set @max = @rows*2 + 100
    while @rows > 0 begin
        insert into Ta values (@rows, @max, @rows%120)
        set @rows = @rows-1
        set @max = @max-2
end
GO

create or alter procedure insertIntoTb(@rows int)
as
    while @rows > 0 begin
        insert into Tb values (@rows, @rows%870, @rows%140)
        set @rows = @rows-1
    end
GO

create or alter procedure insertIntoTc(@rows int) 
as
    declare @aid int
    declare @bid int
    while @rows > 0 begin
        set @aid = (select top 1 aid from Ta order by NEWID())
        set @bid = (select top 1 bid from Tb order by NEWID())
        insert into Tc values (@rows, @aid, @bid)
        set @rows = @rows-1
end
GO

exec insertIntoTa 10000
exec insertIntoTb 12000
exec insertIntoTc 4000

delete Tc
delete Ta
delete Tb


-- A
-- clustered index scan
-- because of the primary key we already have a clustered index that is on Ta(aid)
select * from Ta order by aid;

-- clustered index seek
select * from Ta where aid = 1;

-- nonclustered index scan
create index nonClusteredTa on Ta(x);
drop index nonClusteredTa on Ta;

select x from Ta order by x;

-- nonclustered index seek
select a2 from Ta where x = 2;

-- Key Lookup
select x from Ta where a2 = 19000 

-- B
select * from Tb where b2 = 35

create nonclustered index index2 on Tb(b2) include (bid, x)
drop index index2 on Tb

select * from Tb where b2 = 35
GO

-- C
create or alter view view1 as
    select top 1000 T1.x, T3.bid
    from Tc T3 join Ta T1 on T3.aid = T1.aid
    where T1.x < 15
GO

select * from view1

