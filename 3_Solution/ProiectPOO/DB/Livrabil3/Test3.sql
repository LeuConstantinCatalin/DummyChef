
--1. Creati o procedura stocata care primeste doi parametri de intrare pe baza carora se fac actualizari pe doua tabele. Procedura returneaza doi parametri de iesire reprezentand numarul de linii afectate de fiecare dintre actualizari. Exemplificati un apel al acestei proceduri 
--2. Scrieti un trigger de tip AFTER sau INSTEAD OF. (Acesta sa faca altceva decat verificarea dublurii unei anumite valori in tabela pe care este creat triggerul). Creati evenimentul necesar declansarii triggerului.
--3. In cadrul unei proceduri stocate creati o tranzitie care sa realizeze o inserare pe baza a doi parametrii de intrare, dintre care unul reprezinta valoarea cheii primare care se doreste a fi inserata. gestionati eroarea de cheie primara. exemplificati apeluri ale acestei proceduri care sa determine tratarea acesteia.
--4. Creati o tranzitie in care sa se faca 3 INSERT-uri urmate de un update si un delete. Operatiunile de update si delete sa se realizeze, fiecare din ele, pe baza a cel putin 2 join-uri. Tratati erorile in mod structurat.


--1.
--putem utiliza această procedură pentru a actualiza starea de activitate a utilizatorilor (cum ar fi bucătarii, ospătarii etc.) și cantitatea de ingrediente disponibile în stocuri. Aceasta poate fi utilă în situații precum gestionarea utilizatorilor care sunt activi sau inactivi în sistem, sau actualizarea cantităților de ingrediente din stocuri în urma unei livrări de la furnizor sau în urma unei comenzi de la clienți. Folosind această procedură, putem economisi timp și efort, asigurând în același timp consistența datelor în mai multe tabele.
CREATE PROCEDURE UpdateTables2
    @newActivity BIT,
    @newCantitate DECIMAL(10,2),
    @affectedRowsUsers INT OUTPUT,
    @affectedRowsStocuri INT OUTPUT
AS
BEGIN
    SET NOCOUNT ON;

    -- Actualizare în tabela users
    UPDATE users
    SET activity = @newActivity;

    SET @affectedRowsUsers = @@ROWCOUNT;

    -- Actualizare în tabela stocuri_ingrediente
    UPDATE stocuri_ingrediente
    SET cantitate = @newCantitate;

    SET @affectedRowsStocuri = @@ROWCOUNT;
END;

DROP PROCEDURE UpdateTables2

DECLARE @affectedUsers INT, @affectedStocuri INT;
EXEC UpdateTables2 @newActivity = 1, @newCantitate = 20.5, @affectedRowsUsers = @affectedUsers OUTPUT, @affectedRowsStocuri = @affectedStocuri OUTPUT;
SELECT 'Numărul de linii afectate în tabela users: ' + CONVERT(VARCHAR, @affectedUsers), 'Numărul de linii afectate în tabela stocuri_ingrediente: ' + CONVERT(VARCHAR, @affectedStocuri);


--2
-- Pentru a monitoriza și a înregistra activitățile de conectare în sistemul de management culinar, se dorește crearea unui trigger AFTER în SQL Server care să fie declanșat după fiecare inserare a unui nou eveniment de conectare în tabela 'logging'. Triggerul trebuie să afișeze un mesaj de confirmare atunci când este declanșat și poate fi extins pentru a include și alte acțiuni ulterioare, cum ar fi actualizarea altor tabele sau trimiterea de notificări către administratorii sistemului.

CREATE TRIGGER TriggerLoggingAfterInsert
ON logging
AFTER INSERT
AS
BEGIN
    -- Codul de acțiune al triggerului
    PRINT 'Un nou eveniment a fost înregistrat în tabela logging.';

END;

INSERT INTO logging (logged_user_id, login_time)
VALUES (1, GETDATE());

DROP TRIGGER TriggerLoggingAfterInsert
--3
-- În cadrul unui sistem de gestionare a utilizatorilor, este necesară crearea unei proceduri stocate în baza de date pentru a gestiona inserarea unui nou utilizator. Scopul este de a trata în mod adecvat cazurile în care se încearcă inserarea unei chei primare care există deja în tabelul "users". Procedura trebuie să ofere o soluție care să permită continuarea operației fără a afecta integritatea datelor. Pentru acest lucru, se propune implementarea unei logici care să identifice eroarea de cheie primară duplicată și să trateze această situație în mod corespunzător, astfel încât să se asigure adăugarea utilizatorului nou fără pierderi de date sau conflicte.
	CREATE PROCEDURE InserareCuGestionareEroare (
		@id INT,
		@username VARCHAR(50),
		@password VARCHAR(100),
		@type VARCHAR(20),
		@activity BIT
	)
	AS
	BEGIN
		SET NOCOUNT ON;

		BEGIN TRY
			INSERT INTO users (id, username, password, type, activity)
			VALUES (@id, @username, @password, @type, @activity);
		END TRY
		BEGIN CATCH
			-- Verificăm dacă eroarea este de tip cheie primară duplicată
			IF ERROR_NUMBER() = 2627
			BEGIN
				PRINT 'Eroare: Cheia primară este duplicată. Se încearcă gestionarea...';

				-- Aici poți trata eroarea cum dorești, poți genera o altă cheie unică sau poți lăsa procedura să continue fără să facă nimic.
			END
			ELSE
			BEGIN
				-- Dacă eroarea nu este de tip cheie primară duplicată, afișăm mesajul de eroare
				THROW;
			END
		END CATCH
	END;

	DROP PROCEDURE InserareCuGestionareEroare
	-- codul de testare merge doar daca pe coloana id, este anulata proprietatea de autoincrement. Dupa testare, am refacut baza de date la starea initiala
	
	-- Exemplu de apel al procedurii cu o cheie primară care nu există deja
EXEC InserareCuGestionareEroare @id = 1, @username = 'utilizator1', @password = 'parola1', @type = 'utilizator', @activity = 1;

-- Exemplu de apel al procedurii cu o cheie primară care există deja (va genera o eroare gestionată)
EXEC InserareCuGestionareEroare @id = 1, @username = 'utilizator2', @password = 'parola2', @type = 'utilizator', @activity = 1;

-- 4

-- Pentru a face testing pe baza de date, administartorul dorește implementarea unei tranzacții în cadrul unei baze de date pentru a efectua mai multe operațiuni de modificare a datelor. Aceste operațiuni includ inserarea unor noi înregistrări în tabelele "users", "furnizori" și "ingrediente", actualizarea unor înregistrări existente în tabela "furnizori" și ștergerea unor înregistrări din tabela "ingrediente". Fiecare operațiune de modificare este bazată pe cel puțin două join-uri cu alte tabele. Scopul este de a asigura consistența datelor și de a gestiona în mod structurat orice eroare care ar putea apărea în timpul tranzacției. Soluția propusă constă în implementarea unei proceduri stocate care să încadreze toate aceste operațiuni într-o singură tranzacție și să trateze în mod adecvat orice eroare care ar putea interveni, asigurând astfel integritatea și fiabilitatea datelor din baza de date.

CREATE PROCEDURE TranzitieCuTratareErori
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        BEGIN TRANSACTION; -- Începe tranzacția
        
        -- Inserare 1
        INSERT INTO users (username, password, type, activity)
        VALUES ('utilizator1', 'parola123', 'utilizator', 1);

        -- Inserare 2
        INSERT INTO furnizori (nume) VALUES ('Furnizor1');

        -- Inserare 3
        INSERT INTO ingrediente (nume) VALUES ('Ingrediente1');

        -- Update
        UPDATE furnizori
        SET nume = 'NoulNume'
        FROM furnizori AS f
        INNER JOIN stocuri_furnizori AS sf ON f.id = sf.furnizor_id
        WHERE sf.calitate = 'Buna';

        -- Delete
        DELETE FROM ingrediente
        WHERE id IN (
            SELECT i.id
            FROM ingrediente AS i
            INNER JOIN stocuri_ingrediente AS si ON i.id = si.ingredient_id
            INNER JOIN retete AS r ON si.reteta_id = r.id
            WHERE r.nume = 'Reteta1'
        );

        COMMIT TRANSACTION; -- Confirmă tranzacția dacă toate instrucțiunile sunt executate cu succes
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION; -- Anulează tranzacția în caz de eroare
        -- Afisează mesajul de eroare
        PRINT 'Eroare: ' + ERROR_MESSAGE();
    END CATCH;
END;

DROP PROCEDURE TranzitieCuTratareErori