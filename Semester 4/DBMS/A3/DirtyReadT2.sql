SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRANSACTION
SELECT * FROM Members
WAITFOR DELAY '00:00:15'
SELECT * FROM Members
COMMIT TRAN