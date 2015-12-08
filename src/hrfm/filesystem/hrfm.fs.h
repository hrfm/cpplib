#pragma once

#include <map>
#include <string>
#include <iostream>
#include <regex>

using namespace std;
using namespace boost;

namespace hrfm { namespace fs{
    
    static filesystem::path getHomeDirectory(){
        filesystem::path path = getenv("HOME");
        return path;
    }
    
    static filesystem::path resolvePath( filesystem::path path ){
        filesystem::path resolvedPath;
        string pathStr = path.string();
        if( pathStr.find("~/") == 0 ){
            pathStr.erase(0,2);
            resolvedPath = getHomeDirectory() / pathStr;
        }else{
            resolvedPath = pathStr;
        }
        return resolvedPath;
    }
    
    // --------------------------------------------------------------------------------------------------------------
    
    const static string FILE_TYPE_PIC = "pic";
    const static string FILE_TYPE_MOV = "mov";
    
    static string getFileType( filesystem::path filepath ){
        filesystem::path extension = filepath.extension();
        if( extension == ".jpg" || extension == ".jpeg" || extension == ".png" || extension == ".gif" ){
            return FILE_TYPE_PIC;
        }else if( extension == ".mov" || extension == ".mp4" || extension == ".avi" ){
            return FILE_TYPE_MOV;
        }else{
            return "";
        }
    }
    
    // --------------------------------------------------------------------------------------------------------------
    
    static vector<filesystem::path> getFileList( filesystem::path dir, bool ignoreDotFiles = true, bool sortByNumeric = true, filesystem::path createCopyInto = "" ){
        
        try{
            
            if( filesystem::exists(dir) && filesystem::is_directory(dir) && !filesystem::is_empty(dir) ){
                
                typedef vector<filesystem::path> vec;
                vec v;
                
                filesystem::directory_iterator endItr;
                
                copy( filesystem::directory_iterator(dir), filesystem::directory_iterator(), back_inserter(v) );
                
                // ------------------------------------------------------------
                // If ignoreDotFiles is true.
                // Erase file path that filename begin with "."
                
                if( ignoreDotFiles ){
                    for ( vector<filesystem::path>::iterator it=v.begin(); it != v.end(); ){
                        string fname = (*it).filename().string();
                        if( fname.find(".") == 0 ){
                            it = v.erase(it);
                        }else{
                            ++it;
                        }
                    }
                }
                
                // ------------------------------------------------------------
                // If set createCopyInto.
                // Create file copy into that path.
                // And return new path.
                
                if( createCopyInto != "" ){
                    for ( vector<filesystem::path>::iterator it=v.begin(); it != v.end(); ++it ){
                        string fname   = (*it).filename().string();
                        string newPath = createCopyInto.string() + "/" + fname;
                        try{
                            filesystem::copy_file( (*it), filesystem::path( newPath ) );
                        }catch(...){}
                        (*it) = newPath;
                    }
                }
                
                
                // ------------------------------------------------------------
                // If sortByNumeric is true.
                // Sort vector by numercal part of filename.
                
                if( sortByNumeric ){
                    
                    sort( v.begin(), v.end(), []( const filesystem::path & a, const filesystem::path & b ){
                        
                        string aStr = a.filename().string();
                        string bStr = b.filename().string();
                        int aInt, bInt;
                        
                        regex reg("^[0-9]+");
                        std::smatch mA, mB;
                        
                        regex_search( aStr, mA, reg );
                        regex_search( bStr, mB, reg );
                        
                        if( mA.size() == 0 && mB.size() == 0 ){
                            return aStr < bStr;
                        }
                        
                        try{
                            if( 0 < mA.size() ){
                                aInt = std::stoi(mA.str());
                            }else{
                                aInt = 999999;
                            }
                        }catch(...){
                            aInt = 999999;
                        }
                        
                        try{
                            if( 0 < mB.size() ){
                                bInt = std::stoi(mB.str());
                            }else{
                                bInt = 999999;
                            }
                        }catch(...){
                            bInt = 999999;
                        }
                        
                        return aInt < bInt;
                        
                    });
                    
                    
                }
                
                return v;
                
            }else{
                cout << "Path is empty." << endl;
            }
            
        }catch(...){}
        
        return vector<filesystem::path>();
        
    }
    
}}
