#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//printf("hello");
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
//	else {
//    	printf("Connected to database! \n");
//	}
    
    char *sql1 = "UPDATE alarm SET finished_by_pult = 1 WHERE finished_by_pult = 0;";
    
    rc = sqlite3_exec(db, sql1, 0, 0, &err_msg);
    
    char *sql2 = "INSERT INTO user_action (dict_action_type, action_data, action_data2, user_id, user_ip, time) " \
                "SELECT 12, action_data, NULL, 0, '127.0.0.1', CAST((julianday('now') - 2440587.5) * 86400000.0 AS int) " \
                "FROM (SELECT action_data, max(time) as time, dict_action_type, action_data2, user_id, user_ip, time " \
                "FROM user_action WHERE dict_action_type IN (10, 11, 12 , 13, 20, 21, 22) GROUP BY action_data) WHERE dict_action_type <> 12";

    rc = sqlite3_exec(db, sql2, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
    
    sqlite3_close(db);  
    
    printf("All alarms in database were completed! \n");
    
    system("pause");   
       
	return 0;
}
