#include <iostream> 
using namespace std;

#define OTL_ORA10G  //不可缺少
#include "otlv4.h" //注意OTL头文件位置

otl_connect db;
string strMonitorSql = "select 1 from dual";

int main() 
{ 
    otl_connect::otl_initialize();  

    cout << "try to connect oracle" << endl;

    while(!db.connected)
    {

        try 
        {
            db.rlogon("ad/ad@192.168.80.13:1521/dev"); 
        }
        catch(otl_exception& p) 
        {  
            cerr<<p.msg<<endl;  
            cerr<<p.stm_text<<endl;  
            cerr<<p.sqlstate<<endl;  
            cerr<<p.var_info<<endl;  
            cout<<"Connected to Database fail "<<endl;
            continue;
        }
    }

    while(true)
    {
        try
        {
            cout << "try to select to oracle" << endl;
            otl_nocommit_stream os(1, strMonitorSql.c_str(), db);
            os.close();
        } 
        catch(otl_exception& p) 
        {  
            cerr<<p.msg<<endl;  
            cerr<<p.stm_text<<endl;  
            cerr<<p.sqlstate<<endl;  
            cerr<<p.var_info<<endl;  
            cout<<"select fail "<<endl;
            continue;
        }

        sleep(3);
    }
    
    cout<<"Connected to Database success"<<endl;
    db.logoff(); 
    
  return 0; 
}