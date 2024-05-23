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

DROP PROC CheckUsernameExists

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

EXEC CheckUsernameExists 'daff', 'users', ' ';
select * from users

select * from ingrediente
order by id
select * from furnizori
select * from lista_de_cumparaturi
select * from furnizori_lista_de_cumparaturi
select * from retete
select * from stocuri_furnizori
select * from users

SELECT * FROM 
retete R JOIN lista_de_cumparaturi LC ON R.id = LC.reteta_id

ALTER TABLE ingrediente_reteta
ADD Cantitate INT,
    UnitateMasura VARCHAR(30);


INSERT INTO ingrediente(nume) VALUES
('biscuiti'),
('cafea'),
('mascarpone'),
('lapte'),
('sunca'),
('mere');

select * from retete

select * from ingrediente
select * from ingrediente_reteta

INSERT INTO ingrediente_reteta VALUES
(1,1,9),
(2,1,7),
(3,1,3),
(4,2,2),
(5,2,7),
(6,2,8),
(7,3,5),
(8,3,6),
(9,3,4);

UPDATE ingrediente_reteta
SET UnitateMasura = 'bucata'
WHERE ID = 1
UPDATE ingrediente_reteta
SET UnitateMasura = 'ml'
WHERE ID = 2
UPDATE ingrediente_reteta
SET Cantitate = 15, UnitateMasura = 'g'
WHERE ID = 3
UPDATE ingrediente_reteta
SET Cantitate = 2, UnitateMasura = 'bucata'
WHERE ID = 4
UPDATE ingrediente_reteta
SET Cantitate = 400, UnitateMasura = 'ml'
WHERE ID = 5
UPDATE ingrediente_reteta
SET Cantitate = 200, UnitateMasura = 'g'
WHERE ID = 6
UPDATE ingrediente_reteta
SET Cantitate = 100, UnitateMasura = 'g'
WHERE ID = 7
UPDATE ingrediente_reteta
SET Cantitate = 300, UnitateMasura = 'g'
WHERE ID = 8
UPDATE ingrediente_reteta
SET Cantitate = 400, UnitateMasura = 'g'
WHERE ID = 9


ALTER PROCEDURE RequestIngrediente
    @NumeReteta VARCHAR(50)
AS
BEGIN

SELECT I.nume, IR.Cantitate, IR.UnitateMasura
FROM retete R 
JOIN ingrediente_reteta IR on IR.RetetaID = R.id
JOIN ingrediente I ON I.id = IR.IngredientID
WHERE R.nume = @NumeReteta

END

CREATE PROCEDURE RequestToateIngredientele

AS
BEGIN

SELECT I.nume, IR.Cantitate, IR.UnitateMasura
FROM retete R 
JOIN ingrediente_reteta IR on IR.RetetaID = R.id
JOIN ingrediente I ON I.id = IR.IngredientID

END

EXEC RequestToateIngredientele
EXEC RequestIngrediente	Tiramisu

Create PROCEDURE RequestReteta
    @NumeReteta VARCHAR(50)
AS
BEGIN

SELECT nume, mod_de_preparare, poza
FROM retete
WHERE nume = @NumeReteta

SELECT I.nume, IR.Cantitate, IR.UnitateMasura
FROM retete R 
JOIN ingrediente_reteta IR on IR.RetetaID = R.id
JOIN ingrediente I ON I.id = IR.IngredientID
WHERE R.nume = @NumeReteta

END

SELECT id FROM retete

EXEC RequestReteta Tiramisu

ALTER PROCEDURE RequestToateRetetele
AS
BEGIN

DECLARE @maxID INT;
DECLARE @ID INT = 1;

SELECT @maxID = MAX(id)
FROM retete;

WHILE @ID <= @maxID
BEGIN

    SELECT nume, mod_de_preparare, poza
	FROM retete
	WHERE id = @ID;

	SELECT I.nume, IR.Cantitate, IR.UnitateMasura
	FROM retete R 
	JOIN ingrediente_reteta IR on IR.RetetaID = R.id
	JOIN ingrediente I ON I.id = IR.IngredientID
	WHERE R.id = @ID

    SET @ID = @ID + 1; 

END

END

EXEC RequestToateRetetele

CREATE PROCEDURE RequestIdMaxRetete
AS
BEGIN
	DECLARE @maxID INT;
	SELECT @maxID = MAX(id)
	FROM retete;
	SELECT @maxID;
END

Create PROCEDURE RequestRetetaFromID
    @ID INT
AS
BEGIN
SELECT nume, mod_de_preparare, poza
FROM retete
WHERE id = @ID
END

Create PROCEDURE RequestIngredienteRetetaFromID
    @ID INT
AS
BEGIN
SELECT I.nume, IR.Cantitate, IR.UnitateMasura
FROM retete R 
JOIN ingrediente_reteta IR on IR.RetetaID = R.id
JOIN ingrediente I ON I.id = IR.IngredientID
WHERE R.id = @ID;
END

select * from users

EXEC RequestIdMaxRetete
EXEC RequestRetetaFromID 1
EXEC RequestIngredienteRetetaFromID 1

CREATE TABLE bucatariRequest (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    username VARCHAR(50) UNIQUE, -- Câmpul pentru username, unic
    password VARCHAR(100), -- Câmpul pentru parolă
    
);

select * from furnizori
select * from lista_de_cumparaturi
select * from furnizori_lista_de_cumparaturi
select * from stocuri_furnizori
select * from stocuri_ingrediente

select * from retete
UPDATE retete
set poza = 'D:\\Poze\\Tiramisu.jpg'