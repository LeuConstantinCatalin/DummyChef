--•	Select cu filtrare de date calendaristice:

SELECT *
FROM logging
WHERE login_time >= '2024-03-19' AND login_time < '2024-03-20';

--•	Select cu prelucrare de date de tip caracter:

SELECT id, nume, UPPER(nume) AS nume_mare
FROM ingrediente;

--•	Select folosind clauza Order By:

SELECT *
FROM retete
ORDER BY nume;

--•	Select cu filtrarea datelor folosind TOP:

SELECT TOP 2 *
FROM users;

--•	Select cu filtrarea și ordonarea datelor:

SELECT *
FROM furnizori_lista_de_cumparaturi
WHERE cantitate > 100
ORDER BY cantitate DESC;

--• Select cu filtrare de date în care se combină cel puțin 2 predicate:

SELECT *
FROM lista_de_cumparaturi
WHERE user_id = 1 AND pret_total IS NOT NULL;

--• Select cu ordonare pe mai multe coloane:

SELECT *
FROM stocuri_furnizori
ORDER BY furnizor_id, ingredient_id;

--•	Select cu concatenare de coloane în care este permis NULL, cu obținerea unui rezultat relevant:

SELECT 
    CONCAT_WS(' - ', i.nume, ISNULL(calitate, 'Necunoscută')) AS detalii_ingredient
FROM stocuri_furnizori sf
INNER JOIN ingrediente i ON sf.ingredient_id = i.id;

--•	Select cu eliminarea duplicatelor rămase după aplicarea a două filtre. Afișați datele în mod convenabil:

SELECT DISTINCT username, password, activity, type
FROM users
WHERE activity = 1
   AND type = 'utilizator' -- Se aplică al doilea filtru
ORDER BY username; -- Poate fi orice coloană pe care doriți să o ordonați



