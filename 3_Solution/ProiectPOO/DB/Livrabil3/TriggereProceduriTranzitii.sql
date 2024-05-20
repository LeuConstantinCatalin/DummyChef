
--TRIGGERE

--Atunci când un utilizator se autentifică, acest trigger înregistrează într-un jurnal momentul autentificării și identitatea utilizatorului, oferind o modalitate de monitorizare a accesului la sistem și de urmărire a activității utilizatorilor.
CREATE TRIGGER trg_UserLoginLogging
ON users
AFTER INSERT
AS
BEGIN
    INSERT INTO logging (logged_user_id, login_time)
    SELECT id, GETDATE()
    FROM inserted;
END;

DROP TRIGGER trg_UserLoginLogging
--Acest trigger actualizează automat prețul total al ingredientelor pentru o rețetă în lista de cumpărături în funcție de modificările aduse stocurilor de ingrediente, asigurând o actualizare precisă și eficientă a costurilor asociate pregătirii unei rețete.
CREATE TRIGGER trg_UpdateTotalPrice
ON stocuri_ingrediente
AFTER INSERT, UPDATE
AS
BEGIN
    UPDATE l
    SET l.pret_total = (SELECT SUM(si.cantitate * sf.pret) 
                        FROM inserted i
                        INNER JOIN lista_de_cumparaturi l ON i.reteta_id = l.reteta_id
                        INNER JOIN stocuri_ingrediente si ON l.reteta_id = si.reteta_id
                        INNER JOIN stocuri_furnizori sf ON si.ingredient_id = sf.ingredient_id
                        WHERE l.id = i.reteta_id)
    FROM lista_de_cumparaturi l
    INNER JOIN inserted i ON l.reteta_id = i.reteta_id;
END;

DROP TRIGGER trg_UpdateTotalPrice

-- Prin acest trigger, orice modificare adusă stocurilor de ingrediente este înregistrată într-un jurnal, oferind o urmărire detaliată a schimbărilor și a actualizărilor efectuate asupra stocurilor, astfel încât să se poată gestiona eficient resursele disponibile.
CREATE TRIGGER trg_MonitorStockChanges
ON stocuri_furnizori
AFTER UPDATE
AS
BEGIN
    INSERT INTO logging (logged_user_id, login_time)
    VALUES (1, GETDATE()); -- Schimbați id-ul utilizatorului și data după necesități
END;

DROP TRIGGER trg_MonitorStockChanges


-- Acest trigger împiedică ștergerea accidentală a utilizatorilor activi, înlocuind operația de ștergere cu o acțiune care elimină doar utilizatorii inactivi din baza de date. Astfel, se asigură integritatea și continuitatea datelor pentru utilizatorii activi.
CREATE TRIGGER trg_PreventActiveUserDeletion
ON users
INSTEAD OF DELETE
AS
BEGIN
    DELETE FROM users
    WHERE id IN (SELECT id FROM deleted WHERE activity = 0)
END;

DROP TRIGGER  trg_PreventActiveUserDeletion

--Atunci când se înregistrează o nouă intrare în jurnalul de activitate, acest trigger actualizează automat statutul de activitate al utilizatorului asociat, marcându-l ca activ. Această funcționalitate permite menținerea și actualizarea continuă a stării de activitate a utilizatorilor în sistem.
CREATE TRIGGER trg_UpdateUserActivity
ON logging
AFTER INSERT
AS
BEGIN
    UPDATE u
    SET u.activity = 1
    FROM users u
    INNER JOIN inserted i ON u.id = i.logged_user_id;
END;



DROP TRIGGER trg_UpdateUserActivity


-- PROCEDURI STOCATE 

-- Procedura stocată pentru a obține toate retetele disponibile pentru un anumit utilizator:
CREATE PROCEDURE GetAvailableRecipesForUser
    @username VARCHAR(50)
AS
BEGIN
    SELECT r.*
    FROM retete r
    INNER JOIN lista_de_cumparaturi lc ON r.id = lc.reteta_id
    INNER JOIN users u ON lc.user_id = u.id
    WHERE u.username = @username;
END;

-- Această procedură stocată primește un nume de utilizator ca parametru și returnează toate rețetele disponibile pentru acel utilizator.

DROP PROCEDURE GetAvailableRecipesForUser

--Procedura stocată pentru a adăuga un nou furnizor:

CREATE PROCEDURE AddNewSupplier
    @supplier_name VARCHAR(100)
AS
BEGIN
    INSERT INTO furnizori (nume)
    VALUES (@supplier_name);
END;

-- Această procedură stocată primește numele unui nou furnizor și îl adaugă în tabela furnizori.
DROP PROCEDURE AddNewSupplier

-- Procedura stocată pentru a actualiza parola utilizatorului

CREATE PROCEDURE UpdateUserPassword
    @username VARCHAR(50),
    @new_password VARCHAR(100)
AS
BEGIN
    UPDATE users
    SET password = @new_password
    WHERE username = @username;
END;

-- Această procedură stocată primește numele de utilizator și noua parolă și actualizează parola utilizatorului corespunzător.

DROP PROCEDURE UpdateUserPassword

-- Procedura stocată pentru a șterge un furnizor împreună cu toate legăturile sale:

CREATE PROCEDURE DeleteSupplierAndRelatedData
    @supplier_id INT
AS
BEGIN
    DELETE FROM furnizori WHERE id = @supplier_id;
    DELETE FROM stocuri_furnizori WHERE furnizor_id = @supplier_id;
    DELETE FROM furnizori_lista_de_cumparaturi WHERE furnizor_id = @supplier_id;
END;

--Această procedură stocată primește ID-ul unui furnizor și șterge furnizorul împreună cu toate înregistrările legate de el din tabelele relevante.

DROP PROCEDURE DeleteSupplierAndRelatedData


-- Procedura stocată pentru a adăuga un nou ingredient în stocul furnizorului:

CREATE PROCEDURE AddIngredientToSupplierStock
    @supplier_id INT,
    @ingredient_id INT,
    @quality VARCHAR(50),
    @price DECIMAL(10,2),
    @delivery_days INT
AS
BEGIN
    INSERT INTO stocuri_furnizori (furnizor_id, ingredient_id, calitate, pret, zile_pana_la_livrare)
    VALUES (@supplier_id, @ingredient_id, @quality, @price, @delivery_days);
END;

DROP PROCEDURE AddIngredientToSupplierStock


-- Această procedură stocată primește ID-ul furnizorului, ID-ul ingredientului, calitatea, prețul și numărul de zile până la livrare și adaugă un nou ingredient în stocul furnizorului corespunzător.


-- tranzacții cu prelucrarea erorilor

-- Tranzacție pentru adăugarea unui nou utilizator și înregistrarea în jurnal (logging):

BEGIN TRY
    BEGIN TRANSACTION;

    INSERT INTO users (username, password, type, activity)
    VALUES ('new_user', 'password123', 'utilizator', 1);

    INSERT INTO logging (logged_user_id, login_time)
    VALUES (SCOPE_IDENTITY(), GETDATE());

    COMMIT TRANSACTION;
END TRY
BEGIN CATCH
    IF @@TRANCOUNT > 0
        ROLLBACK TRANSACTION;
    
    -- Putem înregistra sau gestiona eroarea aici
    SELECT ERROR_MESSAGE() AS ErrorMessage;
END CATCH;


--Tranzacție pentru actualizarea prețului unui ingredient în stocul furnizorului:

BEGIN TRY
    BEGIN TRANSACTION;

    UPDATE stocuri_furnizori
    SET pret = 15.99
    WHERE furnizor_id = 1 AND ingredient_id = 2;

    COMMIT TRANSACTION;
END TRY
BEGIN CATCH
    IF @@TRANCOUNT > 0
        ROLLBACK TRANSACTION;
    
    -- Puteți înregistra sau gestiona eroarea aici
    SELECT ERROR_MESSAGE() AS ErrorMessage;
END CATCH;


--Tranzacție pentru adăugarea unui nou furnizor împreună cu legăturile sale:

BEGIN TRY
    BEGIN TRANSACTION;

    INSERT INTO furnizori (nume)
    VALUES ('NumeFurnizor');

    DECLARE @supplier_id INT = SCOPE_IDENTITY();

    INSERT INTO stocuri_furnizori (furnizor_id, ingredient_id, calitate, pret, zile_pana_la_livrare)
    VALUES (@supplier_id, 1, 'Bună', 10.99, 3);

    -- Se pot adăuga și alte legături aici

    COMMIT TRANSACTION;
END TRY
BEGIN CATCH
    IF @@TRANCOUNT > 0
        ROLLBACK TRANSACTION;
    
    -- Puteți înregistra sau gestiona eroarea aici
    SELECT ERROR_MESSAGE() AS ErrorMessage;
END CATCH;

-- Tranzacție pentru ștergerea unui utilizator și a tuturor datelor asociate:

BEGIN TRY
    BEGIN TRANSACTION;

    DECLARE @deleted_user_id INT;
    SELECT @deleted_user_id = id FROM users WHERE username = 'user_to_delete';

    DELETE FROM lista_de_cumparaturi WHERE user_id = @deleted_user_id;
    DELETE FROM logging WHERE logged_user_id = @deleted_user_id;
    DELETE FROM users WHERE id = @deleted_user_id;

    COMMIT TRANSACTION;
END TRY
BEGIN CATCH
    IF @@TRANCOUNT > 0
        ROLLBACK TRANSACTION;
    
    -- Puteți înregistra sau gestiona eroarea aici
    SELECT ERROR_MESSAGE() AS ErrorMessage;
END CATCH;



-- Tranzacție pentru adăugarea unui nou ingredient în stocul furnizorului cu verificare de existență a furnizorului:

BEGIN TRY
    BEGIN TRANSACTION;

    DECLARE @supplier_id INT;
    SELECT @supplier_id = id FROM furnizori WHERE nume = 'FurnizorExist';

    IF @supplier_id IS NULL
    BEGIN
        RAISERROR('Furnizorul nu există.', 16, 1);
    END

    INSERT INTO stocuri_furnizori (furnizor_id, ingredient_id, calitate, pret, zile_pana_la_livrare)
    VALUES (@supplier_id, 1, 'Bună', 10.99, 3);

    COMMIT TRANSACTION;
END TRY
BEGIN CATCH
    IF @@TRANCOUNT > 0
        ROLLBACK TRANSACTION;
    
    -- Puteți înregistra sau gestiona eroarea aici
    SELECT ERROR_MESSAGE() AS ErrorMessage;
END CATCH;


-- Aceste tranzacții gestionează erorile care pot apărea în timpul executării și revin la starea anterioară a datelor în caz de eroare.

