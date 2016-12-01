
#include "file_util.h"
#include "log_define.h"
#include "config.h"
#include "util.h"

using namespace std;
using namespace remote_file_edit;

CLog g_log;

int main(int argc, char** argv )
{
    // sleep(100);
    int iRet = 0;
    CReadConfig cReadConfig("remote_file_edit.cfg");

    string strIp = cReadConfig.read_config("ip");
    string strUserName = cReadConfig.read_config("username");
    string strRemotePath = cReadConfig.read_config("remote_path");
    string strLocalPath = cReadConfig.read_config("local_path");
    string strFileName = cReadConfig.read_config("filename");
    
    if(strIp.empty() || strUserName.empty() || strRemotePath.empty() || strLocalPath.empty() || strFileName.empty())
    {
        LOG_ERROR(" please check config some of config is not config,strIp = %s,strUserName = %s,strRemotePath = %s,strLocalPath = %s,strFileName = %s",
                    strIp.c_str(),strUserName.c_str(),strRemotePath.c_str(),strLocalPath.c_str(),strFileName.c_str());
        return -1;
    }

    strIp = TrimSpace(strIp.c_str());
    strLocalPath = TrimSpace(strLocalPath);
    strRemotePath = TrimSpace(strRemotePath);
    strUserName = TrimSpace(strUserName);
    strFileName = TrimSpace(strFileName);

    if(!IsEndWith(strRemotePath,'/'))
    {
        strRemotePath.append("/");
    }

    if(!IsEndWith(strLocalPath,'/'))
    {
        strLocalPath.append("/");
    }

    vector<string> listIp;
    SpiltString(strIp," ",&listIp);

    vector<string> listLocalFile;
    CFileUtil cFileUtil;
    for(vector<string>::iterator it = listIp.begin();
            it != listIp.end(); ++it)
    {
        string strUrl;
        strUrl.append("sftp://");
        strUrl.append(strUserName);
        strUrl.append("@");
        strUrl.append(*it);
        strUrl.append(strRemotePath);
        strUrl.append(strFileName);

        LOG_TRACE("strUrl = %s",strUrl.c_str());

        CFile cFile;
        cFile.filename.append(strLocalPath);
        cFile.filename.append(*it);
        cFile.filename.append("_");
        cFile.filename.append(strFileName);

        LOG_TRACE("local filename = %s",cFile.filename.c_str());

        iRet = cFileUtil.GetFile(strUrl,cFile);

        listLocalFile.push_back(cFile.filename);

    }

    

    return 0;

    // //2 show file 
    // SendFileToDb();

    // //3 edit file
    // GetFileFromDb();
    // //4 send remote
    // SendModifiedFile();

}