BEGIN TRAN
UPDATE Guilds SET Description='Changed' WHERE Guild_Id=1
WAITFOR DELAY '00:00:10'
UPDATE Members SET Username='Changed' WHERE Member_Id = 2
COMMIT TRAN

SELECT * FROM Guilds
SELECT * FROM Members