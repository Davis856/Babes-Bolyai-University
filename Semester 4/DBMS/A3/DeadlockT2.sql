BEGIN TRAN
UPDATE Members SET Username='Changedd' WHERE Member_Id = 2
WAITFOR DELAY '00:00:10'
UPDATE Guilds SET Description='Changedd' WHERE Guild_Id=1
COMMIT TRAN