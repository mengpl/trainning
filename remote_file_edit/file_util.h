#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
namespace remote_file_edit
{
    class CFile
    {
    public:
        CFile(){ stream = NULL; filename="";};
        virtual ~CFile(){};
    public:
        string filename;
        FILE * stream;
    };

    class CFileTrans;
    class CFileUtil
    {
    public:
        CFileUtil();
        virtual ~CFileUtil();
    
    public:
        int GetFile(const string strUrl,CFile & cFile);
        int SendFile(const string strUrl,CFile & cFile);

        int GetFileList(const vector<string> listUrl,vector<CFile> & listFile);
        int SendFileList(const vector<string> listUrl,vector<CFile> & listFile);

    private:
        CFileTrans * m_fileTrans;

    };
}

#endif /*__FILE_UTIL_H__*/