CREATE DATABASE DummyChef

--DROP DATABASE DummyChef

ON PRIMARY
(
Name = DummyChefData1,
FileName = 'C:\DB\DummyChef1.mdf',
size = 10MB, -- KB, Mb, GB, TB
maxsize = unlimited,
filegrowth = 1GB
),
(
Name = DummyChefData2,
FileName = 'C:\DB\DummyChef2.ndf',
size = 10MB, -- KB, Mb, GB, TB
maxsize = unlimited,
filegrowth = 1GB
),
(
Name = DummyChefData3,
FileName = 'C:\DB\DummyChef3.ndf',
size = 10MB, -- KB, Mb, GB, TB
maxsize = unlimited,
filegrowth = 1GB
)
LOG ON
(
Name = DummyChefLog1,
FileName = 'C:\DB\DummyChef4.ldf',
size = 10MB, -- KB, Mb, GB, TB
maxsize = unlimited,
filegrowth = 1024MB
),
(
Name = DummyChefLog2,
FileName = 'C:\DB\DummyChef5.ldf',
size = 10MB, -- KB, Mb, GB, TB
maxsize = unlimited,
filegrowth = 1024MB
)



-- Crează tabelul "users"
CREATE TABLE users (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    username VARCHAR(50) UNIQUE, -- Câmpul pentru username, unic
    password VARCHAR(100), -- Câmpul pentru parolă
    type VARCHAR(20), -- Câmpul pentru tip (bucătar, utilizator, admin)
    activity BIT -- Câmpul pentru activitate (1 pentru activ, 0 pentru inactiv)
);

CREATE TABLE logging (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    logged_user_id INT, -- ID-ul utilizatorului care s-a logat
    login_time DATETIME, -- Momentul de timp la care s-a realizat logarea
    FOREIGN KEY (logged_user_id) REFERENCES users(id) -- Cheie străină către tabela users
);

CREATE TABLE ingrediente (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    nume VARCHAR(100) UNIQUE -- Câmpul pentru nume, unic
);


CREATE TABLE furnizori (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    nume VARCHAR(100) UNIQUE -- Câmpul pentru nume, unic
);

CREATE TABLE stocuri_furnizori (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    furnizor_id INT, -- Cheie străină către tabelul furnizori
    ingredient_id INT, -- Cheie străină către tabelul ingrediente
    --cantitate DECIMAL(10,2), -- Cantitatea de ingredient în stoc
    calitate VARCHAR(50), -- Calitatea ingredientului
    pret DECIMAL(10,2), -- Prețul ingredientului
    zile_pana_la_livrare INT, -- Numărul de zile până la livrare
    FOREIGN KEY (furnizor_id) REFERENCES furnizori(id), -- Cheie străină către tabelul furnizori
    FOREIGN KEY (ingredient_id) REFERENCES ingrediente(id) -- Cheie străină către tabelul ingrediente
);

ALTER TABLE stocuri_furnizori
DROP COLUMN cantitate;

ALTER TABLE stocuri_furnizori
DROP COLUMN calitate;

select * from stocuri_furnizori
insert into stocuri_furnizori(furnizor_id,ingredient_id,pret,zile_pana_la_livrare,calitate) values
(1,4,12.99,1,1),
(1,5,5.99,1,2),
(1,6,6,2,1),
(1,7,1,4,3),
(1,8,20.99,3,1),
(1,9,5.99,1,1);
Update stocuri_furnizori
set calitate = 1
Where id = 3

ALTER TABLE stocuri_furnizori
ADD calitate INT;

BEGIN TRY
    ALTER TABLE stocuri_furnizori
    ADD COLUMN calitate INT;
END TRY
BEGIN CATCH
    PRINT ERROR_MESSAGE();
END CATCH


CREATE TABLE retete (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    nume VARCHAR(100) UNIQUE, -- Numele retetei, unic
    mod_de_preparare TEXT, -- Modul de preparare al retetei (text lung)
    poza VARBINARY(MAX) -- Imaginea retetei (binar)
);

ALTER TABLE retete
ALTER COLUMN poza VARCHAR(200);

CREATE TABLE stocuri_ingrediente (
	id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    reteta_id INT, -- Cheie străină către retete
    ingredient_id INT, -- Cheie străină către ingrediente
    cantitate DECIMAL(10,2), -- Cantitatea de ingredient necesară
    FOREIGN KEY (reteta_id) REFERENCES retete(id), -- Cheie străină către tabela retete
    FOREIGN KEY (ingredient_id) REFERENCES ingrediente(id) -- Cheie străină către tabela ingrediente
);

CREATE TABLE lista_de_cumparaturi (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    user_id INT, -- Cheie străină către tabelul users
    reteta_id INT, -- Cheie străină către tabelul retete
    pret_total DECIMAL(10,2), -- Prețul total al ingredientelor pentru reteta respectivă
    zile_pana_la_livrare INT, -- Numărul de zile până la livrare
	momentul_crearii DATETIME, -- Momentul de timp la care s-a realizat logarea
    FOREIGN KEY (user_id) REFERENCES users(id), -- Cheie străină către tabela users
    FOREIGN KEY (reteta_id) REFERENCES retete(id) -- Cheie străină către tabela retete
);



CREATE TABLE furnizori_lista_de_cumparaturi (
    id INT PRIMARY KEY IDENTITY, -- Cheie primară auto-incrementată
    lista_de_cumparaturi_id INT, -- Cheie străină către tabela lista_de_cumparaturi
    ingredient_id INT, -- Cheie străină către tabela ingrediente
	cantitate DECIMAL(10,2), -- Cantitatea de ingredient necesară
    furnizor_id INT, -- Cheie străină către tabela furnizori
    FOREIGN KEY (lista_de_cumparaturi_id) REFERENCES lista_de_cumparaturi(id), -- Cheie străină către tabela lista_de_cumparaturi
    FOREIGN KEY (ingredient_id) REFERENCES ingrediente(id), -- Cheie străină către tabela ingrediente
    FOREIGN KEY (furnizor_id) REFERENCES furnizori(id) -- Cheie străină către tabela furnizori
);





-- Inserare în tabelul "users"
INSERT INTO users (username, password, type, activity)
VALUES ('utilizator1', 'parola123', 'utilizator', 1),
       ('bucatar1', 'parola456', 'bucatar', 1),
       ('admin1', 'parola789', 'admin', 1);

-- Inserare în tabelul "logging"
INSERT INTO logging (logged_user_id, login_time)
VALUES (1, GETDATE()), -- Presupunând că utilizatorul cu ID-ul 1 s-a logat în momentul curent
       (2, '2024-03-19 10:30:00'), -- Un alt exemplu cu un timp specific
       (3, '2024-03-19 11:45:00');

-- Inserare în tabelul "ingrediente"
INSERT INTO ingrediente (nume)
VALUES ('faina'),
       ('oua'),
       ('zahar');

-- Inserare în tabelul "furnizori"
INSERT INTO furnizori (nume)
VALUES ('Furnizor1'),
       ('Furnizor2'),
       ('Furnizor3');

-- Inserare în tabelul "stocuri_furnizori"
INSERT INTO stocuri_furnizori (furnizor_id, ingredient_id,  calitate, pret, zile_pana_la_livrare)
VALUES (1, 1, 'buna', 5.99, 2),
       (2, 2, 'foarte buna', 7.50, 3),
       (3, 3, 'excelenta', 10.25, 1);

-- Inserare în tabelul "retete"
INSERT INTO retete (nume, mod_de_preparare, poza)
VALUES ('Placinta cu mere', 'Se amesteca faina cu ouale si zaharul, apoi se adauga merele taiate cubulete. Se coace la 180°C timp de 40 de minute.', NULL),
       ('Omleta', 'Se bat ouale, se adauga sare si piper, apoi se prajesc intr-o tigaie incinsa.', NULL),
       ('Tiramisu', 'Se amesteca mascarpone cu zaharul si galbenusurile, apoi se aranjeaza straturi de piscoturi insiropate cu cafea si crema de mascarpone.', NULL);

-- Inserare în tabelul "stocuri_ingrediente"
INSERT INTO stocuri_ingrediente (reteta_id, ingredient_id, cantitate)
VALUES (1, 1, 300), -- Placinta cu mere: 300 grame de faina
       (1, 2, 4),   -- Placinta cu mere: 4 oua
       (1, 3, 150), -- Placinta cu mere: 150 grame de zahar
       (2, 2, 6),   -- Omleta: 6 oua
       (3, 2, 12),  -- Tiramisu: 12 oua
       (3, 1, 200), -- Tiramisu: 200 grame de faina
       (3, 3, 250); -- Tiramisu: 250 grame de zahar

-- Inserare în tabelul "lista_de_cumparaturi"
INSERT INTO lista_de_cumparaturi (user_id, reteta_id, pret_total, zile_pana_la_livrare,momentul_crearii)
VALUES (1, 2, NULL, NULL,GETDATE()), -- Utilizatorul 1 are în lista de cumpărături reteta 1, prețul total și zilele până la livrare vor fi actualizate automat
       (2, 2, NULL, NULL,'2024-03-19 10:30:00'), -- Utilizatorul 2 are în lista de cumpărături reteta 2, prețul total și zilele până la livrare vor fi actualizate automat
       (3, 3, NULL, NULL,'2024-03-19 10:35:00'); -- Utilizatorul 3 are în lista de cumpărături reteta 3, prețul total și zilele până la livrare vor fi actualizate automat

-- Inserare în tabelul "furnizori_lista_de_cumparaturi"
-- Presupunând că fiecare retetă necesită un ingredient de la un furnizor
INSERT INTO furnizori_lista_de_cumparaturi (lista_de_cumparaturi_id, ingredient_id, cantitate, furnizor_id)
VALUES (1, 1, 500, 1), -- Lista de cumpărături 1 necesită 500 grame de făină de la furnizorul 1
       (2, 2, 8, 2),   -- Lista de cumpărături 2 necesită 8 ouă de la furnizorul 2
       (3, 3, 300, 3); -- Lista de cumpărături 3 necesită 300 grame de zahăr de la furnizorul 3


	   UPDATE lista_de_cumparaturi
SET pret_total = (
    SELECT SUM(ROUND(sf.pret * flc.cantitate, 0))
    FROM furnizori_lista_de_cumparaturi flc
    INNER JOIN stocuri_furnizori sf ON flc.furnizor_id = sf.furnizor_id AND flc.ingredient_id = sf.ingredient_id
    WHERE flc.lista_de_cumparaturi_id = lista_de_cumparaturi.id
)
WHERE id IN (
    SELECT lista_de_cumparaturi_id
    FROM furnizori_lista_de_cumparaturi
    WHERE reteta_id = lista_de_cumparaturi.reteta_id
);

UPDATE lista_de_cumparaturi
SET zile_pana_la_livrare = (
    SELECT MAX(sf.zile_pana_la_livrare)
    FROM furnizori_lista_de_cumparaturi flc
    INNER JOIN stocuri_furnizori sf ON flc.furnizor_id = sf.furnizor_id AND flc.ingredient_id = sf.ingredient_id
    WHERE flc.lista_de_cumparaturi_id = lista_de_cumparaturi.id
)

select * from lista_de_cumparaturi
select * from retete R JOIN ingrediente_reteta IR ON R.id = IR.ID
SELECT * FROM ingrediente

ALTER procedure Cumparaturi
@nume varchar(100)
AS
BEGIN

SELECT SF.pret, SF.zile_pana_la_livrare, SF.calitate, F.nume FROM stocuri_furnizori SF 
JOIN ingrediente I ON SF.ingredient_id = I.id
JOIN furnizori F ON F.id = SF.furnizor_id
where I.nume = @nume

END

EXEC Cumparaturi cafea
EXEC Cumparaturi lapte

select * from users

insert into users(username,password, type, activity) values (2,2,'bucatar',4);

CREATE PROCEDURE ActivityUtilizator AS
BEGIN
SELECT username, activity from users
WHERE type = 'utilizator'
ORDER BY activity
END

EXEC ActivityUtilizator
EXEC ActivityBucatar

CREATE PROCEDURE ActivityBucatar AS
BEGIN
SELECT username, activity from users
WHERE type = 'bucatar'
ORDER BY activity
END

SELECT username, activity from users
WHERE type = 'admin'
ORDER BY activity

EXEC RequestToateRetetele

select * from retete

Update retete
Set poza = 'D:\\Poze\\Omleta.jpg'
Where ID = 2
