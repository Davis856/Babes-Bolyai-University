BEGIN TRANSACTION
UPDATE Members SET Password='changed'
WHERE Member_Id = 4
WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION