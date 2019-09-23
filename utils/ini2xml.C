#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

using boost::property_tree::ptree;

using namespace std;

int main(int argc,char **argv) {
  string defname = "";

  if (argc == 2) {
    defname = argv[1];
  }

  if (defname == "") {
     printf("No name for .XML define given, program aborted.\n");
     exit(-1);
  }

  ptree pt;

  {
    ptree pt_from_ini;
    stringstream ss;
    string line;

    while(getline(cin,line)) {
      vector<string> strs;
      boost::split(strs,line,boost::is_any_of(";"));
      ss << strs[0] << endl;
    }
    read_ini(ss,pt_from_ini);

    for (const auto& section : pt_from_ini) {
      string section_name = section.first;
      for (const auto& key : section.second) {
        string item_name  = key.first;
        string item_value = key.second.get_value<string>();
	char new_section_name[1024];
        sprintf(new_section_name,"%s.%s.%s",defname.c_str(),section_name.c_str(),item_name.c_str());
        string ts = new_section_name;
        size_t pos = 0;
        for (pos = ts.find(" "); pos != string::npos; pos = ts.find(" ",pos)) {
	  ts.replace(pos,1,"_SP_");
	}
        pt.put(ts,item_value);
      }
    }
  }

  {
    stringstream ss;
    write_xml(ss,pt);
    string ts = ss.str();
    ts.erase(ts.find("\n"), 1);

    size_t pos = ts.find("\""); 
    while(pos != string::npos) {
       ts.insert(pos,"\\");
       pos = ts.find("\"",pos + 2); 
    }
    printf("#define %s \"%s\"\n",defname.c_str(),ts.c_str());

    //printf("%s\n",ts.c_str());
  }

  exit(0);
}

