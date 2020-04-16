#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    istream *in = &cin;
    ifstream file;
    bool file_opened = false;
    int n;
    int LL = 40;
    int IN = 8;

    //Error checking
    for(int i = 1; i < argc; i++)
    {
        std::string argi(argv[i]);
        if(argi.at(0) == '-')
        {
            string str2 = argi.substr(1,2);
            if( str2 == "LL" || str2 == "IN" )
            {
                if(argi.at(3) != '=')
                {
                    cerr << "MISSING = SIGN " << argi << endl;
                    return -1;
                }
            }
            else
            {
                cerr << "UNRECOGNIZED FLAG " << argi << endl;
                return -1;
            }
            for(int j = 4; j < argi.length(); j++)
            {
                if( !isdigit( argi.at(j) ) )
                {
                    cerr << "VALUE NOT INTEGER > 0 " << argi << endl;
                    return -1;
                }
            }
            string str3 = argi.substr(4);
            n = std::stoi( str3 );
            if(str2 == "LL")
            {
                LL = n;
            }
            else if(str2 == "IN")
            {
                IN = n;
            }
        }
        else
        {
            if(file_opened)
            {
                cerr << "TOO MANY FILENAMES" << endl;
                return -1;
            }
            file.open(argv[i]);
            if(file.is_open())
            {
                in = &file;
                file_opened = true;
            }
            else
            {
                cerr << "UNABLE TO OPEN FILE " << argi << endl;
                return -1;
            }
        }
    }

    //File Processing
    string indent = "";
    for(int i = 0; i < IN; i++)
    {
        indent += " ";
    }

    string line;
    string output = "";
    bool newParagraph = true;
    int wordCount = 0;
    int emptyLineCount = 0;

    while( getline(*in,line) )
    {
        string tmp = "";
        string tmp2;
        istringstream myString(line);

        bool whiteSpacesOnly = line.find_first_not_of(' ') != std::string::npos;

        if( whiteSpacesOnly || line.empty() )
        {
            emptyLineCount += 1;
            if( emptyLineCount > 1 )
            {
                newParagraph = true;
            }
        }

        while( myString >> tmp2 )
        {
            
            if( newParagraph )
            {
                
                tmp = "";
                output += "\n\n";
                tmp += indent;
                newParagraph = false;
                wordCount = 0;
            }
            else
            {
                emptyLineCount = 0;
            }

            if( tmp2.length() + tmp.length() - 1 > LL && wordCount >= 1)
            {
                output += tmp;
               
                tmp = "";
                tmp += "\n";
                wordCount = 0;
            }            

            wordCount += 1;
            tmp += tmp2 + " ";
        }

        output += tmp;
        

    }
    
    cout << output << endl;

    return 0;
}