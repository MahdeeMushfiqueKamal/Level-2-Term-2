/* 1. Write a PL/SQL procedure that takes four parameters: employee count n, average salary m, manager id m_id as inputs, and rank r as output.
The procedure finds each manager who manages more than n employees and the employees under his/her supervision has average salary less than m, and
then ranks the managers according to the employees’ average salary under him and prints those managers’ full names along with their ranks and the
average salaries of the employees. The highest ranked manager (1) manages the employees with the least average salary. */


CREATE OR REPLACE PROCEDURE Manager_Ranking_Based_On_Avr_Salary (n IN NUMBER, m IN NUMBER) IS
		rank NUMBER;
BEGIN
		rank := 1;
		DBMS_OUTPUT.PUT_LINE('Procedure Created');
		FOR each_row in (SELECT e1.FIRST_NAME || ' ' || e1.LAST_NAME as "Manager",COUNT(*) as "Manages", AVG(e2.SALARY) as "Avr salary" FROM EMPLOYEES e1 JOIN EMPLOYEES e2 ON (e1.EMPLOYEE_ID = e2.MANAGER_ID) GROUP BY e1.FIRST_NAME || ' ' || e1.LAST_NAME ORDER BY "Avr salary")
		LOOP 
				IF each_row."Manages" > n AND each_row."Avr salary" < m THEN
					DBMS_OUTPUT.PUT_LINE(rank || '    ' || each_row."Manager" || '     ' || each_row."Manages" || '     ' || each_row."Avr salary");
					rank := rank +1;
				END IF;
		END LOOP; 
END;
/
BEGIN 
Manager_Ranking_Based_On_Avr_Salary(5,8700);
END;
/