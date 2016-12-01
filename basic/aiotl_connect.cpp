#include <iostream> 
using namespace std;

#define OTL_ORA10G  //不可缺少
#include "otl.h" //注意OTL头文件位置

otl_connect db;

int main() 
{ 
    int i = 0;
    otl_connect::otl_initialize();  
    do
    {
        i++;
        try 
        { 
            cout << "try to connect oracle" << endl;

            db.rlogon("ad/ad@192.168.80.13:1521/dev"); 
            
        } 
        catch(otl_exception& p) 
        {  
            cerr<<p.msg<<endl;  
            cerr<<p.stm_text<<endl;  
            cerr<<p.sqlstate<<endl;  
            cerr<<p.var_info<<endl;  
            cout<<"Connected to Database fail "<<endl;
        }
    }
    while(!db.connected && i != 10000);
    
    cout<<"Connected to Database success"<<endl;

    db.logoff(); 
  return 0; 
}