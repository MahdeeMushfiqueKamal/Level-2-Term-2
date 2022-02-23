/*
Write a function that takes two parameters employee_id and manager_id,
and returns the salary rank of the employee working under the manager
(highest salary == rank 1).
*/
CREATE OR REPLACE FUNCTION Find_Rank_Under_Manager(e_ID IN VARCHAR2, m_id IN VARCHAR2) RETURN NUMBER IS 
		RANK NUMBER;
		e_SALARY NUMBER;
BEGIN
		RANK := 1;
		SELECT SALARY INTO e_SALARY FROM EMPLOYEES WHERE EMPLOYEE_ID = e_ID;
		--DBMS_OUTPUT.PUT_LINE(e_SALARY);
		FOR r IN (SELECT SALARY,MANAGER_ID FROM EMPLOYEES)
		LOOP
				IF r.MANAGER_ID = m_id AND r.SALARY > e_SALARY THEN
						--DBMS_OUTPUT.PUT_LINE(r.MANAGER_ID || '    ' || r.SALARY);
						RANK := RANK + 1;
				END IF;
		END LOOP;
		
		RETURN RANK;
END;
/

BEGIN
		DBMS_OUTPUT.PUT_LINE(Find_Rank_Under_Manager('114','100'));
END;
