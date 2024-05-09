
--  jonctiuni pe cel putin 3 tabele

-- 1.	Joncțiune între tabela lista_de_cumparaturi, retete și users pentru a obține detalii despre lista de cumpărături împreună cu numele utilizatorului și numele retetei.

SELECT lc.id AS lista_id, u.username, r.nume AS reteta_nume
FROM lista_de_cumparaturi lc
JOIN users u ON lc.user_id = u.id
JOIN retete r ON lc.reteta_id = r.id;


-- 2.   Joncțiune între tabela stocuri_ingrediente, ingrediente și retete pentru a obține detalii despre ingredientele necesare pentru fiecare retetă.

SELECT si.reteta_id, i.nume AS ingredient_nume, si.cantitate, r.nume AS reteta_nume
FROM stocuri_ingrediente si
JOIN ingrediente i ON si.ingredient_id = i.id
JOIN retete r ON si.reteta_id = r.id;

-- 3.  Joncțiune între tabela furnizori_lista_de_cumparaturi, furnizori și ingrediente pentru a obține detalii despre furnizorii pentru fiecare ingredient din lista de cumpărături.

SELECT flc.lista_de_cumparaturi_id, f.nume AS furnizor_nume, i.nume AS ingredient_nume, flc.cantitate
FROM furnizori_lista_de_cumparaturi flc
JOIN furnizori f ON flc.furnizor_id = f.id
JOIN ingrediente i ON flc.ingredient_id = i.id;

-- 4.  Joncțiune între tabela stocuri_furnizori, furnizori și ingrediente pentru a obține detalii despre stocurile furnizorilor pentru fiecare ingredient.

SELECT sf.furnizor_id, f.nume AS furnizor_nume, i.nume AS ingredient_nume, sf.calitate, sf.pret
FROM stocuri_furnizori sf
JOIN furnizori f ON sf.furnizor_id = f.id
JOIN ingrediente i ON sf.ingredient_id = i.id;

-- 1.	Utilizatori inactivi: Această interogare va returna utilizatorii care sunt inactivi (cu activitatea setată la 0) din tabela users.

SELECT username
FROM users
WHERE activity = 1;

--2.	Ingredientele disponibile în stoc pentru toate retetele: Această interogare va returna numele ingredientelor și cantitățile disponibile în stoc pentru toate retetele din tabela stocuri_ingrediente.

SELECT i.nume AS ingredient, SUM(si.cantitate) AS cantitate_disponibila
FROM stocuri_ingrediente si
JOIN ingrediente i ON si.ingredient_id = i.id
GROUP BY i.nume;

--3.    Retetele care necesită ingrediente disponibile în stoc: Această interogare va returna numele retetelor și ingredientele necesare pentru retetele care au toate ingredientele disponibile în stoc.

SELECT r.nume AS reteta, SUM(sf.pret * si.cantitate) AS pret_total
FROM retete r
JOIN stocuri_ingrediente si ON r.id = si.reteta_id
JOIN stocuri_furnizori sf ON si.ingredient_id = sf.ingredient_id
GROUP BY r.id, r.nume; 


--4. Furnizori care oferă cel puțin un ingredient de calitate excelentă:
-- Această interogare va returna numele furnizorilor care oferă cel puțin un ingredient de calitate excelentă din tabela stocuri_furnizori.

SELECT DISTINCT f.nume AS furnizor
FROM stocuri_furnizori sf
JOIN furnizori f ON sf.furnizor_id = f.id
WHERE sf.calitate = 'excelenta';


-- Selecturi cu grupări de date
-- 1. Numărul total de retete pentru fiecare tip de utilizator:
--Această interogare va returna numărul total de retete create de fiecare tip de utilizator din tabela users și retete.

SELECT u.type, COUNT(r.id) AS numar_retete
FROM users u
JOIN retete r ON u.id = r.id
GROUP BY u.type;

-- 2. Media cantității necesare de ingrediente pentru fiecare retetă:
-- Această interogare va returna media cantității necesare de ingrediente pentru fiecare retetă din tabela stocuri_ingrediente.

SELECT r.nume AS reteta, AVG(si.cantitate) AS cantitate_medie
FROM retete r
JOIN stocuri_ingrediente si ON r.id = si.reteta_id
GROUP BY r.nume;

--3.	Prețul total al ingredientelor necesare pentru fiecare retetă: Această interogare va returna prețul total al ingredientelor necesare pentru fiecare retetă din tabela stocuri_furnizori.
SELECT r.nume AS reteta, SUM(sf.pret * si.cantitate) AS pret_total
FROM retete r
JOIN stocuri_ingrediente si ON r.id = si.reteta_id
JOIN stocuri_furnizori sf ON si.ingredient_id = sf.ingredient_id
GROUP BY r.nume;

--4.	Cantitatea totală de ingrediente disponibile în stoc pentru fiecare furnizor: Această interogare va returna cantitatea totală de ingrediente disponibile în stoc pentru fiecare furnizor din tabela stocuri_furnizori.

SELECT f.nume AS furnizor, SUM(sf.cantitate) AS cantitate_totala
FROM furnizori f
JOIN stocuri_furnizori sf ON f.id = sf.furnizor_id
GROUP BY f.nume;


--Selecturi cu filtre pe grupuri

--1.	Utilizatori activi care au creat retete: Această interogare va returna utilizatorii activi care au creat retete din tabela users și retete.
SELECT u.username, COUNT(r.id) AS numar_retete_creat
FROM users u
JOIN retete r ON u.id = r.id
WHERE u.activity = 1
GROUP BY u.username;

--2.	Retetele cu mai multe de 5 ingrediente: Această interogare va returna retetele care au mai mult de 5 ingrediente din tabela retete și stocuri_ingrediente.

SELECT r.nume AS reteta, COUNT(si.ingredient_id) AS numar_ingrediente
FROM retete r
JOIN stocuri_ingrediente si ON r.id = si.reteta_id
GROUP BY r.nume
HAVING COUNT(si.ingredient_id) > 5;

--3.	Retetele cu mai multe de 5 ingrediente: Această interogare va returna retetele care au mai mult de 5 ingrediente din tabela retete și stocuri_ingrediente.

SELECT u.username, SUM(lc.pret_total) AS total_platit
FROM users u
JOIN lista_de_cumparaturi lc ON u.id = lc.user_id
WHERE lc.pret_total > 50
GROUP BY u.username;

--4.	Retetele cu mai multe de 5 ingrediente: Această interogare va returna retetele care au mai mult de 5 ingrediente din tabela retete și stocuri_ingrediente.

SELECT r.nume AS reteta
FROM retete r
JOIN stocuri_ingrediente si ON r.id = si.reteta_id
JOIN stocuri_furnizori sf ON si.ingredient_id = sf.ingredient_id
WHERE sf.calitate = 'excelenta'
GROUP BY r.nume;

--Selecturi cu CTE

--1.	Utilizatori și retetele create de ei: Această interogare utilizează o CTE pentru a defini temporar o listă de utilizatori și retetele create de ei din tabelele users și retete
WITH UtilizatoriCuRetete AS (
    SELECT u.username, r.nume AS reteta
    FROM users u
    JOIN retete r ON u.id = r.id
)
SELECT * FROM UtilizatoriCuRetete;

--2.	Ingredientele și preturile disponibile în stoc: Această interogare utilizează o CTE pentru a defini temporar o listă de ingrediente și preturi disponibile în stoc din tabelele ingrediente și stocuri_furnizori.
WITH PretStoc AS (
    SELECT i.nume AS ingredient, sf.pret
    FROM ingrediente i
    JOIN stocuri_furnizori sf ON i.id = sf.ingredient_id
)
SELECT * FROM PretStoc;

--3.	Lista de cumpărături cu prețul total pentru fiecare utilizator: Această interogare utilizează o CTE pentru a defini temporar lista de cumpărături și prețul total pentru fiecare utilizator din tabelele lista_de_cumparaturi și users.
WITH PretTotalLista AS (
    SELECT user_id, SUM(pret_total) AS pret_total
    FROM lista_de_cumparaturi
    GROUP BY user_id
)
SELECT u.username, pt.pret_total
FROM users u
JOIN PretTotalLista pt ON u.id = pt.user_id;

--4.	Numarare furnizori
WITH NumarFurnizori AS (
    SELECT COUNT(*) AS numar_furnizori
    FROM furnizori
)
SELECT * FROM NumarFurnizori;

--View-

--1.	Lista de cumpărături cu prețul total pentru fiecare utilizator: Această interogare utilizează o CTE pentru a defini temporar lista de cumpărături și prețul total pentru fiecare utilizator din tabelele lista_de_cumparaturi și users.
CREATE VIEW ListaCumparaturiUtilizatoriActivi AS
SELECT lc.id, u.username, r.nume AS reteta, lc.pret_total
FROM lista_de_cumparaturi lc
JOIN users u ON lc.user_id = u.id
JOIN retete r ON lc.reteta_id = r.id
WHERE u.activity = 1;

--2.	View pentru stocurile disponibile în stocurile furnizorilor: Acest view va afișa stocurile disponibile în stocurile furnizorilor din tabela stocuri_furnizori.
CREATE VIEW StocuriDisponibileFurnizori AS
SELECT sf.furnizor_id, f.nume AS furnizor, i.nume AS ingredient, sf.cantitate
FROM stocuri_furnizori sf
JOIN furnizori f ON sf.furnizor_id = f.id
JOIN ingrediente i ON sf.ingredient_id = i.id;

--3.	View pentru stocurile disponibile în stocurile furnizorilor: Acest view va afișa stocurile disponibile în stocurile furnizorilor din tabela stocuri_furnizori.
CREATE VIEW ReteteCuOua AS
SELECT r.nume AS reteta, si.cantitate AS cantitate_oua
FROM retete r
JOIN stocuri_ingrediente si ON r.id = si.reteta_id
JOIN ingrediente i ON si.ingredient_id = i.id
WHERE i.nume = 'oua';

--4.	View pentru stocurile disponibile în stocurile furnizorilor: Acest view va afișa stocurile disponibile în stocurile furnizorilor din tabela stocuri_furnizori.
CREATE VIEW FurnizoriIngredienteExcelente AS
SELECT DISTINCT f.nume AS furnizor, sf.calitate
FROM furnizori f
JOIN stocuri_furnizori sf ON f.id = sf.furnizor_id
WHERE sf.calitate = 'excelenta';

--5.	View pentru stocurile disponibile în stocurile furnizorilor: Acest view va afișa stocurile disponibile în stocurile furnizorilor din tabela stocuri_furnizori.
CREATE VIEW ListaCumparaturiDetaliiIngrediente AS
SELECT lc.id, u.username, r.nume AS reteta, flc.cantitate, i.nume AS ingredient, f.nume AS furnizor
FROM lista_de_cumparaturi lc
JOIN users u ON lc.user_id = u.id
JOIN retete r ON lc.reteta_id = r.id
JOIN furnizori_lista_de_cumparaturi flc ON lc.id = flc.lista_de_cumparaturi_id
JOIN ingrediente i ON flc.ingredient_id = i.id
JOIN furnizori f ON flc.furnizor_id = f.id;
