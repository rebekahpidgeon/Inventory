#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

static int callback( void* data, int argc, char** argv, char** azColName){ // EXAMPLE CALLBACK
    // data* is any extra information about the connection
    // argc is number of columns in the current row of the result set
    // argv contains the values of each column in the current row of the result set
    // azColName contains the column names of the result set
    int i; // initialise index for loop variable
    //stderr is used to print error messages or diagnostic information, rather than stdout
    fprintf(stderr, "%s: ", (const char*)data); // print out any extra information

    for(i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); // if argv[i] is false, print null. If true (has info) print the info
    }
    return 0;
}

char** admin_callback( void* data, int argc, char** argv, char** azColName){
    int i;
    char* username;
    char* password;
    for(i = 0; i < argc; i++){
        
    }
}

string start_program(){
    string answer;
    cout << "Welcome to inventory!" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1: Admin Login" << endl;
    cout << "2: Login to inventory" << endl;
    cout << "3: Sign up" << endl;
    cin >> answer;
    return answer;
}
void check_program(){
    string choice = start_program();
    if(choice == "1") {
        admin_login();
    }
    else if(choice == "2") {
        login();
    }
    else if(choice == "3") {
        signup();
    }
    else{
        cout << "Invalid choice: " << choice << endl;
        check_program();
    }
}
void admin_login(){
    string username;
    string password;
    cout << "Please enter your username: ";
    getline(cin, username);
    cout << "Please enter your password: ";
    getline(cin, password);

    stringstream sql_stream; // create a stream to create the sql statement required
    sql_stream << "SELECT * FROM OWNER WHERE USERNAME == " << username << " AND PASSWORD = " << password;

    string sql = sql_stream.str(); // convert sql stream to string
    string data("CALLBACK");
    
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("inventory.db", &db);
    if(rc != SQLITE_OK){
        cout << "Error accessing database" << endl;
        return -1;
    }

    else if(rc == SQLITE_OK){
        cout << "Database access" << endl;
    }

    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);

    if(rc != SQLITE_OK){
        cerr << "Error SELECT" << endl;
    }
    else{
        cout << "Operation successful" << endl;
    }

    sqlite3_close(db);

}
int main() {
    check_program();
}