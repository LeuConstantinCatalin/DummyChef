CREATE PROCEDURE TransferBucatar
    @username VARCHAR(50)
AS
BEGIN
    BEGIN TRANSACTION;
    
    -- Caută și inserează utilizatorul într-o singură instrucțiune dacă este găsit
    INSERT INTO users (username, password, type, activity)
    SELECT username, password, 'bucatar', 1
    FROM bucatariRequest
    WHERE username = @username;

    -- Șterge utilizatorul din bucatariRequest doar dacă a fost inserat în users
    DELETE FROM bucatariRequest
    WHERE username = @username
    AND EXISTS (
        SELECT 1
        FROM users
        WHERE username = @username
    );

    COMMIT TRANSACTION;
END;


INSERT INTO bucatariRequest (username, password)
VALUES ('new_username', 'new_password');

EXEC TransferBucatar @username = 'new_username';

INSERT INTO bucatariRequest (username, password)
VALUES ('new_username1', 'new_password1');

INSERT INTO bucatariRequest (username, password)
VALUES ('new_username2', 'new_password2');
INSERT INTO bucatariRequest (username, password)
VALUES ('new_username3', 'new_password3');
INSERT INTO bucatariRequest (username, password)
VALUES ('new_username4', 'new_password4');

CREATE PROCEDURE CheckUsernameExists
    @username VARCHAR(50),
    @tableName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @paramDef NVARCHAR(MAX);
    DECLARE @count INT;

    -- Construiește dinamically query-ul SQL pentru a căuta username-ul în tabela specificată
    SET @sql = N'SELECT @count = COUNT(*) FROM ' + QUOTENAME(@tableName) + ' WHERE username = @username';
    SET @paramDef = N'@username VARCHAR(50), @count INT OUTPUT';

    -- Execută query-ul SQL dinamically
    EXEC sp_executesql @sql, @paramDef, @username = @username, @count = @count OUTPUT;

    -- Verifică rezultatul și returnează un mesaj
    IF @count > 0
    BEGIN
        PRINT 'Username found!';
    END
    ELSE
    BEGIN
        PRINT 'Username not found.';
    END
END;


EXEC CheckUsernameExists admin1, users ,resultMessage;

DROP PROCEDURE CheckUsernameExists

CREATE PROCEDURE CheckUsernameExists
    @username VARCHAR(50),
    @tableName NVARCHAR(128),
    @resultMessage NVARCHAR(50) OUTPUT
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @paramDef NVARCHAR(MAX);
    DECLARE @count INT;

    -- Construiește dinamically query-ul SQL pentru a căuta username-ul în tabela specificată
    SET @sql = N'SELECT @count = COUNT(*) FROM ' + QUOTENAME(@tableName) + ' WHERE username = @username';
    SET @paramDef = N'@username VARCHAR(50), @count INT OUTPUT';

    -- Execută query-ul SQL dinamically
    EXEC sp_executesql @sql, @paramDef, @username = @username, @count = @count OUTPUT;

    -- Verifică rezultatul și setează mesajul corespunzător
    IF @count > 0
    BEGIN
        SET @resultMessage = 'Username found!';
    END
    ELSE
    BEGIN
        SET @resultMessage = 'Username not found.';
    END
	 SELECT @resultMessage;
END;
