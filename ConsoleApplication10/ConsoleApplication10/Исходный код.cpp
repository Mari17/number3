#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <boost/foreach.hpp>
#include "sha1.h"
using boost::property_tree::xml_writer_settings;
namespace fs =boost::filesystem;
using namespace fs;
using boost::property_tree::ptree;
using namespace std;
string hash_counter(string file_path){
	
	string file_text ;
	ifstream c_file;// for openning file and hash it 
	c_file.open(file_path, ifstream::in);
	while (!c_file.eof()){
		file_text += c_file.get();

	}
	const void *vp = file_text.c_str();
	unsigned char hash[20];
	char hexstring[41];
	sha1::calc(vp,10,hash); // 10 is the length of the string
	sha1::toHexString(hash, hexstring);
	return hexstring;
	
}

void all_files(const fs::path& p, std::vector<fs::path>& files)
{
    for (fs::directory_iterator pos(p); pos != fs::directory_iterator(); ++pos)
    {
        if (fs::is_directory(*pos)) all_files(*pos, files);
        else
            files.push_back(*pos);
		complete(*pos).string();
		
    }
}

void changes()
{ptree pt1;
	
	std::cout << "Enter new path" << std::endl;
	path p;
	std::string h;
	std::cin>>h;
	p=h;
	if ( !exists(p) ) std::cout<<"don't exist";
	else{
	
	std::cout << "Enter your xml File Path" << std::endl;
	std::string x;
	path p1;
	p1=x;
	std::cin>>x;
	if ( !exists(x) ) std::cout<<"don't exist";
	else{
	std::vector<fs::path> files1;
	
	read_xml(x,pt1);
    all_files(p1, files1);

	for (const auto& file1 : files1) {
		int k = 0;
		for (auto &v : pt1.get_child("file")) {
		
		std::string x = file1.string();
		x = x.erase(0, p.string().length());
		if (v.second.get<std::string>("name") != "flag")
					if (x == v.second.get<std::string>("adress"))
						if (file1.filename().string() == v.second.get<std::string>("name")) {
							if (hash_counter(file1.string())!= v.second.get<std::string>("sha1")) std::cout << "File : " << file1.filename().string() << " was changed" << std::endl;
							int k=1;
							v.second.put<std::string>("name", "flag");  break;
						}
				}
	if (k == 0) std::cout << "File : " << file1.filename().string() << " is a new file" << std::endl;
		

}
	std::cout << "\ndeleted:\n" << std::endl;
		for (auto &v : pt1.get_child("file")){
			if (v.second.get<std::string>("name") != "flag")  std::cout << "File : " << v.second.get<std::string>("name") << std::endl;
		}
	}
}
	}

int main()
{	int k;
	std::cout << "For getting files of directory in xml enter \n1\nfor watching changes in directory\n0\n"; 
	std::cin >> k;
	if (k==1){
    setlocale(LC_ALL, "Russian");
	std::string L;
	std::cout<<"Введите адрес:";
	std::cin>>L;
    fs::path directory_path(L);
	ptree pt;
	ptree way;
	if ( !exists(L) ) std::cout<<"don't exist";
	else{

    std::vector<fs::path> files;
    all_files(directory_path, files);
	
    std::cout<<"Все файлы в директории "<<directory_path<<" (включая поддиректории) находятся в:\n\n";
    for (const auto& file : files) {
	auto&a=file.filename();
	string f=file.string();
	auto&b=f.erase(0, directory_path.string().length());
	uintmax_t file_size(const path& file);
	
	
	auto settings = boost::property_tree::xml_writer_make_settings<std::string>('\t', 1);
	way.put("name",a);
	way.put("adress",b);
	way.put("size",file_size(file));
	way.put("sha1",hash_counter(file.string()));
	
	pt.push_back(make_pair("file", way));
	}
	}
	
	auto settings = boost::property_tree::xml_writer_make_settings<std::string>('\t', 1);
	std::ofstream f("files of directory.xml");
	write_xml(f, pt, settings);
	auto &v=complete("files of directory.xml").string();
	std::cout<<v;
}
	else changes();
	system("pause");
    return 0;
}

