#pragma once
#include <experimental/filesystem>
#include <vector>
#include <iostream>

enum class Vergleichsmodi { Gr��e, Gr��e_und_Name };
struct Context
{
	uintmax_t s_fileSize = 0;
	std::string s_filePath = "";
	std::string s_fileName = "";
	//std::string s_Extention = "";
};
class C_DDI
{
public:
	C_DDI();
	~C_DDI();
	//std::vector<Context> context_collect(/*path*/,/* modi */)const; // Sammle Kandidaten �berladen
	std::vector<Context> sammle_kandidaten(std::string);	  //  Sammle Kandidaten ist noch nicht vorsortiert
	std::vector<Context> pr�fe_kandidaten(std::vector<Context>Collection, Vergleichsmodi);
	std::string dateipfade(std::vector<Context>,int);
};

