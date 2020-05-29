//
// Generated on 2020/05/29 by inimoni 
//

/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Documentation
  Struct = Section name, Field = Key name.
  The function used is only a declaration, load(), and save().
  The constructor automatically reads initialization file [initFileName].
  Please rewrite [initFileName] in the source freely.
  It becomes Windows folder when there is not path. The relative path can be used.

Example
#include "SampleIni.h"
void CTestDlg::OnButton1()
{
    //initFileName = "./sample.ini";
    SampleIni data1;                   // Open ./sample.ini
    int v = data1.Sample.value;        // [Sample]-value Get
    data1.Sample.value = v+1;          // [Sample]-value Modify
    data1.save();                      // Save ./Sample.ini (Opened file)

    SampleIni data2("sample.ini");     // Open C:/WINDOWS/Sample.ini
    data2.load("./sample.ini");        // Open Specified file.
    data2.save();                      // Save Opened file (Making at not being)
}

Supplementation
  Reading and writing becomes the unit of the file.
  [initFileName] is the same as the argument of GetPrivateProfileString() of SDK.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/

#ifndef DGO_ACINI_H
#define DGO_ACINI_H

#include <string>
using namespace std;

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#ifdef _UNICODE
typedef std::wstring string_t;
#else
typedef std::string string_t;
#endif

namespace inimoni {
    template<class T>
    static bool inirw(int is_read, string_t& fname, string_t sec, string_t key, T& val_t);
};

/**
    dgo_ac.ini input output class.
*/
class Dgo_acIni
{
public:

    Dgo_acIni(string_t fname = _T(""))
    {
        initFileName = _T("./dgo_ac.ini"); //Default file.    
        init();
        load(fname);
    }

    /**
        INI file is read.
        @param fname Filename
        When there is not a file, It becomes initFileName.
        When there is not a pass, It becomes Windows folder.
    */
    bool load(string_t fname = _T(""))
    {
        if (fname.empty()) {
            fname = initFileName;
        }
        loadFileName = fname;
        WIN32_FIND_DATA fd;
        HANDLE h = ::FindFirstFile(fname.c_str(), &fd);
        if (h != INVALID_HANDLE_VALUE) {
            iniRW(fname, 1);
        }
        return (h != INVALID_HANDLE_VALUE);
    }

    /**
        It writes it in the INI file.
        @param fname Filename
        When there is not a file, It becomes open file.
        When there is not a pass, It becomes Windows folder.
    */
    bool save(string_t fname = _T(""))
    {
        if (fname.empty()) {
            fname = loadFileName;
        }
        iniRW(fname, 0);
        return true;
    }

public:

    // GSENSOR
    struct _GSENSOR
    {
        int      enable;
        int      limit;
    } GSENSOR;

    // SOUND
    struct _SOUND
    {
        int      index0;
        int      index1;
        int      index2;
        int      index3;
        int      index4;
        int      index5;
        int      index6;
        int      index7;
        int      index8;
        int      index9;
    } SOUND;

    // KEY
    struct _KEY
    {
        int      index;
    } KEY;

protected:

    string_t initFileName;
    string_t loadFileName;

    bool iniRW(string_t f, int r)
    {
        string_t s;

        s = _T("GSENSOR");
        inimoni::inirw(r, f, s, _T("enable           "), GSENSOR.enable);
        inimoni::inirw(r, f, s, _T("limit            "), GSENSOR.limit);

        s = _T("SOUND");
        inimoni::inirw(r, f, s, _T("index0           "), SOUND.index0);
        inimoni::inirw(r, f, s, _T("index1           "), SOUND.index1);
        inimoni::inirw(r, f, s, _T("index2           "), SOUND.index2);
        inimoni::inirw(r, f, s, _T("index3           "), SOUND.index3);
        inimoni::inirw(r, f, s, _T("index4           "), SOUND.index4);
        inimoni::inirw(r, f, s, _T("index5           "), SOUND.index5);
        inimoni::inirw(r, f, s, _T("index6           "), SOUND.index6);
        inimoni::inirw(r, f, s, _T("index7           "), SOUND.index7);
        inimoni::inirw(r, f, s, _T("index8           "), SOUND.index8);
        inimoni::inirw(r, f, s, _T("index9           "), SOUND.index9);

        s = _T("KEY");
        inimoni::inirw(r, f, s, _T("index            "), KEY.index);
        return true;
    }

    void init()
    {
        GSENSOR.enable = 1;
        GSENSOR.limit = 50;
        SOUND.index0 = 0;
        SOUND.index1 = 1;
        SOUND.index2 = 2;
        SOUND.index3 = 3;
        SOUND.index4 = 4;
        SOUND.index5 = 5;
        SOUND.index6 = 6;
        SOUND.index7 = 7;
        SOUND.index8 = 8;
        SOUND.index9 = 9;
        KEY.index = 0;
    }
};
typedef Dgo_acIni Dgo_acFile; //êVãåå›ä∑

//---------------------------------------------------------------------------
// Common method                                                             
//---------------------------------------------------------------------------
#ifndef INIMONI_INIRW                                                        
#define INIMONI_INIRW                                                        
namespace inimoni
{
    /*
    Read and Write INI file
      int     is_read  1=Read mode, 0=Write mode
      string  fname    Filename (The Windows folder when there is not path)
      string  sec      Section name
      string  key      Key name
      T       val_t    [Read]Init+Output, [Write]Input
    */
    template<class T>
    bool inirw(int is_read, string_t& fname, string_t sec, string_t key, T& val_t)
    {
        if (is_read) {
            inimoni::read(fname.c_str(), sec.c_str(), key.c_str(), val_t);
        }
        else {
            inimoni::write(fname.c_str(), sec.c_str(), key.c_str(), val_t);
        }
        return true;
    }

    bool read(string_t ifn, string_t sec, string_t key, int& dst)
    {
        dst = GetPrivateProfileInt(sec.c_str(), key.c_str(), dst, ifn.c_str());
        return true;
    }

    bool read(string_t ifn, string_t sec, string_t key, basic_string<TCHAR>& dst)
    {
        TCHAR buf[256];
        GetPrivateProfileString(
            sec.c_str(),
            key.c_str(),
            dst.c_str(),
            buf,
            sizeof(buf),
            ifn.c_str());
        dst = buf;
        return true;
    }

    bool read(string_t ifn, string_t sec, string_t key, double& dst)
    {
        string_t s;
        inimoni::read(ifn, sec, key, s);

        TCHAR* e;
        double x = _tcstod(s.c_str(), &e);

        dst = 0.0;
        if (!*e) {
            dst = x;
        }
        return true;
    }

    template<class T>
    bool write(string_t ifn, string_t sec, string_t key, T val_t)
    {
        TCHAR val[1024];
        inimoni::to_string(val, val_t);
        WritePrivateProfileString(sec.c_str(), key.c_str(), val, ifn.c_str());
        return true;
    }

    void to_string(TCHAR* str, int val)
    {
        _stprintf(str, _T("%d"), val);
    }

    void to_string(TCHAR* str, double val)
    {
        _stprintf(str, _T("%f"), val);
    }

    void to_string(TCHAR* str, basic_string<TCHAR> val)
    {
        _stprintf(str, _T("%s"), val.c_str());
    }
};

#endif                                                                  
#endif                                                                  

