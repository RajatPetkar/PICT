
-- CREATE TABLES
CREATE TABLE Training (
    T_id INT PRIMARY KEY,
    Join_date DATE,
    Fees DECIMAL(10,2)
);

CREATE TABLE Student (
    S_id INT PRIMARY KEY,
    S_name VARCHAR(50),
    Branch VARCHAR(50),
    CGPA DECIMAL(3,2),
    T_id INT,
    FOREIGN KEY (T_id) REFERENCES Training(T_id)
        ON DELETE SET NULL ON UPDATE CASCADE
);

CREATE TABLE Placement (
    P_id INT PRIMARY KEY,
    S_id INT,
    PCompany VARCHAR(50),
    Package INT,
    Location VARCHAR(50),
    FOREIGN KEY (S_id) REFERENCES Student(S_id)
        ON DELETE CASCADE ON UPDATE CASCADE
);


-- INSERT DATA

INSERT INTO Training VALUES
(101, '2019-01-01', 20000),
(102, '2020-06-01', 18000),
(103, '2018-09-01', 22000),
(104, '2019-01-01', 25000),
(105, '2021-01-01', 19000),
(106, '2021-01-01', 21000),
(107, '2017-07-01', 17000),
(108, '2021-01-01', 24000),
(109, '2020-08-01', 23000),
(110, '2021-01-01', 26000);

INSERT INTO Student VALUES
(1, 'Amit', 'Computer', 8.5, 101),
(2, 'Deepa', 'IT', 7.8, 102),
(3, 'Ravi', 'Mechanical', 6.9, 103),
(4, 'Anjali', 'Computer', 9.1, 104),
(5, 'Dinesh', 'IT', 7.2, 105),
(6, 'Riya', 'EXTC', 8.0, 106),
(7, 'Akshay', 'Computer', 6.5, 107),
(8, 'David', 'IT', 8.8, 108),
(9, 'Pooja', 'Civil', 9.5, 109),
(10, 'Ankita', 'Computer', 7.0, 110);

INSERT INTO Placement VALUES
(1, 1, 'Infosys', 30000, 'Pune'),
(2, 2, 'TCS', 40000, 'Mumbai'),
(3, 3, 'Wipro', 28000, 'Bangalore'),
(4, 4, 'Capgemini', 50000, 'Pune'),
(5, 5, 'Tech Mahindra', 35000, 'Hyderabad'),
(6, 6, 'IBM', 40000, 'Mumbai'),
(7, 7, 'Google', 70000, 'Hyderabad'),
(8, 8, 'Cognizant', 45000, 'Pune'),
(9, 9, 'Amazon', 80000, 'Delhi'),
(10, 10, 'Microsoft', 90000, 'Mumbai');

-- QUERIES

-- Q2
SELECT * FROM Student
WHERE Branch IN ('Computer', 'IT')
AND (S_name LIKE 'a%' OR S_name LIKE 'd%' OR S_name LIKE 'A%' OR S_name LIKE 'D%');

-- Q3
SELECT COUNT(DISTINCT PCompany) AS num_companies FROM Placement;

-- Q4
UPDATE Training
SET Fees = Fees * 1.15
WHERE YEAR(Join_date) = 2019;

-- Q5
DELETE FROM Student
WHERE CGPA < 7;

SELECT * FROM Student;


-- Q6
SELECT DISTINCT PCompany FROM Placement
WHERE Location IN ('Pune', 'Mumbai');

-- Q7
SELECT S_name FROM Student
WHERE T_id IN (
    SELECT T_id FROM Training WHERE Join_date = '2019-01-01'
)
AND T_id IN (
    SELECT T_id FROM Training WHERE Join_date = '2021-01-01'
);

-- Q8a
SELECT S_name FROM Student
WHERE CGPA = (SELECT MAX(CGPA) FROM Student);

-- Q8b
SELECT S_name FROM Student
WHERE CGPA BETWEEN 7 AND 9;

-- Q9
SELECT S.S_name, S.T_id, T.Fees
FROM Student S
JOIN Training T ON S.T_id = T.T_id
ORDER BY T.Fees DESC;

-- Q10
SELECT P.PCompany, S.S_name, P.Location, P.Package
FROM Placement P
JOIN Student S ON P.S_id = S.S_id
WHERE P.Package IN (30000, 40000, 50000);