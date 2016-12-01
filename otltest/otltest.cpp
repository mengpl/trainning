#include <iostream>

#define OTL_ORA11G
#define DB_TYPE_ORA 
#include "otl.4.0.254.h"


using namespace std;

int main(void)
{
    cout << "case 1 " << endl;
    otl_connect::otl_initialize(); // initialize OCI environment  
    otl_connect db; 
    try 
    { 
        db.rlogon("scott/tiger@dev"); // connect to Oracle  
        cout<<"Connect to Database"<<endl; 
    } 
    catch(otl_exception& p) 
    {  
        // intercept OTL exceptions  
        cerr<<p.msg<<endl; // print out error message  
        cerr<<p.stm_text<<endl; // print out SQL that caused the error  
        cerr<<p.sqlstate<<endl; // print out SQLSTATE message  
        cerr<<p.var_info<<endl; // print out the variable that caused the error  
    } 

    int iEmpNo,iMgr,count = 0;
    otl_stream tOtlStream(1,"select empno,mgr from emp ",db);

    while(!tOtlStream.eof())
    {

      tOtlStream>>iEmpNo;
      tOtlStream>>iMgr;
      count++;

      cout<<iEmpNo<<"  "<< iMgr <<"  "<<endl;

    }

    db.logoff(); // disconnect from Oracle 
}