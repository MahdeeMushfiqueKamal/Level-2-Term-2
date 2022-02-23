CREATE OR REPLACE PROCEDURE Resolve_Department_Choices IS
		E_ID NUMBER;
BEGIN
		DBMS_OUTPUT.PUT_LINE('Procedure Created');
		FOR each_employee in (SELECT * FROM EMPLOYEES ORDER BY HIRE_DATE)
		LOOP 
				E_ID := each_employee.EMPLOYEE_ID;
				DBMS_OUTPUT.PUT_LINE('Working on this employee - ' ||E_ID);
		END LOOP;
END;
/

DECLARE
BEGIN
		Resolve_Department_Choices;
END;



-- UPTO IS_ASSIGNED

CREATE OR REPLACE PROCEDURE Resolve_Department_Choices IS
		E_ID NUMBER;
		P_CHOICE NUMBER;
		P_DEPT NUMBER;
		IS_ASSIGNED NUMBER;
BEGIN
		DBMS_OUTPUT.PUT_LINE('Procedure Created');
		FOR each_employee in (SELECT * FROM EMPLOYEES ORDER BY HIRE_DATE)
		LOOP 
				E_ID := each_employee.EMPLOYEE_ID;
				DBMS_OUTPUT.PUT_LINE('Working on this employee - ' || E_ID);
				
				FOR each_choice in (SELECT * FROM OPTIONS WHERE EMPLOYEE_ID = E_ID ORDER BY CHOICE )
				LOOP 
						P_CHOICE := each_choice.CHOICE;
						P_DEPT := each_choice.DEPARTMENT_ID;
						SELECT COUNT(*) INTO IS_ASSIGNED FROM EMPLOYEE_DEPARTMENT WHERE EMPLOYEE_ID = E_ID;
						--DBMS_OUTPUT.PUT_LINE(IS_ASSIGNED);
						IF P_CHOICE = 1 then
								DBMS_OUTPUT.PUT_LINE(P_CHOICE || '    ' || P_DEPT);
						END IF;
				-- end each choice
				END LOOP;
		END LOOP;
END;
/

DECLARE
BEGIN
		Resolve_Department_Choices;
END;
/
