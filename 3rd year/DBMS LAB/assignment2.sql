SELECT * 
FROM Student 
NATURAL JOIN Placement;

SELECT S.*, P.PCompany
FROM Student S
JOIN Placement P ON S.S_id = P.S_id
WHERE P.PCompany IN (
    SELECT PCompany 
    FROM Placement 
    GROUP BY PCompany 
    HAVING COUNT(*) > 1
);


SELECT S.S_name, S.Branch
FROM Student S
JOIN Placement P ON S.S_id = P.S_id
WHERE P.Package = 5;

SELECT S.S_name, P.PCompany
FROM Student S
JOIN Training T ON S.T_id = T.T_id
JOIN Placement P ON S.S_id = P.S_id
WHERE T.Fees > 20000;

SELECT T.*
FROM Student S
JOIN Training T ON S.T_id = T.T_id
WHERE S.S_name = 'shantanu' 
  AND YEAR(T.Join_date) = 2011;

SELECT COUNT(DISTINCT P.PCompany) AS total_companies
FROM Placement P
JOIN Student S ON S.S_id = P.S_id
JOIN Training T ON S.T_id = T.T_id
WHERE T.Join_date < '2015-01-01';

SELECT S.S_name
FROM Student S
JOIN Placement P ON S.S_id = P.S_id
WHERE P.PCompany = 'Microsoft' AND P.Location = 'Thane';


SELECT S.S_name
FROM Student S
JOIN Training T ON S.T_id = T.T_id
WHERE T.T_id = (SELECT T_id FROM Training WHERE YEAR(Join_date) = 2015 LIMIT 1);

-- 10
CREATE VIEW StudentTrainingView AS
SELECT S.S_id, S.S_name, S.Branch, S.CGPA, T.Join_date, T.Fees
FROM Student S
JOIN Training T ON S.T_id = T.T_id;

UPDATE StudentTrainingView
SET Fees = 30000
WHERE S_name = 'Rohit';

DELETE FROM StudentTrainingView
WHERE S_name = 'Rohit';

DROP VIEW StudentTrainingView;


SELECT * FROM StudentTrainingView;

CREATE VIEW StudentView AS
SELECT S_id, S_name, Branch, CGPA, T_id
FROM Student;

UPDATE StudentView
SET Branch = 'IT'
WHERE S_name = 'Shantanu';

UPDATE Training
SET Fees = 30000
WHERE T_id = (SELECT T_id FROM Student WHERE S_name = 'Rohit');
