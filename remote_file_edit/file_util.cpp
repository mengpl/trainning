#include <errno.h>
#include "log_define.h"
#include "file_util.h"
#include "curl/curl.h"

namespace remote_file_edit
{

struct SProcess
{
    double lastruntime;
    CURL *curl;
};

class CFileTrans
{
public:
    CFileTrans(){};
    virtual ~CFileTrans(){};

    virtual int GetFile(string strUrl,CFile & cFile){};
    virtual int SendFile(string strUrl,CFile & cFile){};
    virtual int GetFileList(vector<string>,vector<CFile> & listFile){};
    virtual int SendFileList(vector<string>,vector<CFile> & listFile){};
};


class CFileTransSftp : public CFileTrans
{
public:
    CFileTransSftp()
    {
    }

    virtual ~CFileTransSftp()
    {
    }

public:

    int GetFile(const string strUrl,CFile & cFile);

    int SendFile(const string strUrl,CFile & cFile)
    {

    };

    int GetFileList(const vector<string> listUrl,vector<CFile> & listFile)
    {

    };

    int SendFileList(const vector<string> listUrl,vector<CFile> & listFile)
    {

    };

private:
    static size_t write_callback(void *buffer, size_t size, size_t nmemb,
                        void *stream)
    {
        CFile *out = (CFile *)stream;
        if(out && !out->stream) 
        {
            out->stream=fopen(out->filename.c_str(), "wb");
            if(!out->stream)
            {
                LOG_ERROR("open file %s fail,errno = %d",out->filename.c_str(),errno);
                return -1; /* failure, can't open file to write */
            }
        }
        
        int iRet = fwrite(buffer, size, nmemb, out->stream);

        if(iRet == 0)
        {
            LOG_ERROR("open file %s fail,errno = %d",out->filename.c_str(),errno);
        }

        return iRet;
    };

    static int process_callback(void *p,
                        curl_off_t dltotal, curl_off_t dlnow,
                        curl_off_t ultotal, curl_off_t ulnow)
    {
        struct SProcess * sProcess   = (SProcess *)p;
        double curtime = 0;
        CURL * curl = sProcess->curl;

        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &curtime);

        if((curtime - sProcess->lastruntime) >= 10) {
            sProcess->lastruntime = curtime;

            fprintf(stderr, "TOTAL TIME: %f \r\n", curtime);
            fprintf(stderr, "  DOWN: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T
              "\r\n", dlnow, dltotal);
        }

        if(dlnow == dltotal && dlnow > 0 and dltotal > 0)
        {
            fprintf(stderr, "TOTAL TIME: %f \r\n", curtime);
            fprintf(stderr, "  DOWN: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T
              "\r\n",dlnow, dltotal);
            return 1;
        }

        return 0;
    }

private:

    CURL * m_pCurl;
    
};

int CFileTransSftp::GetFile(const string strUrl,CFile & cFile)
{
    LOG_TRACE("**********GetFile bgein *****************");
    LOG_TRACE("strUrl = %s",strUrl.c_str());
    LOG_TRACE("local file =  %s",cFile.filename.c_str());
    struct SProcess sProcess;

    int iRet = 0;
    m_pCurl = curl_easy_init();

    if(m_pCurl)
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);

        sProcess.curl = m_pCurl;
        sProcess.lastruntime = 0;
        int iRet = 0;

        curl_easy_setopt(m_pCurl, CURLOPT_URL,strUrl.c_str());

        curl_easy_setopt(m_pCurl, CURLOPT_VERBOSE, 1L);

        curl_easy_setopt(m_pCurl, CURLOPT_NOPROGRESS, 0L);

        curl_easy_setopt(m_pCurl, CURLOPT_XFERINFOFUNCTION, process_callback);
        
        curl_easy_setopt(m_pCurl, CURLOPT_XFERINFODATA, &sProcess);

        curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, &cFile);

        CURLcode res = curl_easy_perform(m_pCurl);

        curl_easy_cleanup(m_pCurl);

        if(CURLE_OK != res && CURLE_ABORTED_BY_CALLBACK != res) 
        {
            fprintf(stderr, "get file from %s failed, please check config ,or check file exist or not !\n", strUrl.c_str());

            if(cFile.stream)
                fclose(cFile.stream);

            curl_global_cleanup();
            iRet = -1;
        }

        curl_global_cleanup();
    }

    return iRet;
};

CFileUtil::CFileUtil()
{
    m_fileTrans = new CFileTransSftp();
};

CFileUtil::~CFileUtil()
{
    if(m_fileTrans)
    {
        delete m_fileTrans;
    }   
}

int CFileUtil::GetFile(const string strUrl,CFile & cFile)
{
    m_fileTrans->GetFile(strUrl,cFile);
}

int CFileUtil::SendFile(const string strUrl,CFile & cFile)
{
    m_fileTrans->SendFile(strUrl,cFile);
}


int CFileUtil::GetFileList(const vector<string> listUrl,vector<CFile> & listFile)
{
    m_fileTrans->GetFileList(listUrl,listFile);
}

int CFileUtil::SendFileList(const vector<string> listUrl,vector<CFile> & listFile)
{
    m_fileTrans->SendFileList(listUrl,listFile);
}
}

