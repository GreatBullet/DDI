#include "C_DDI.h"






int main(int argc, char* argv[])
{
	C_DDI object;
	std::vector<Context> test = object.pr�fe_kandidaten(object.sammle_kandidaten("C:\\"),Vergleichsmodi::Gr��e_und_Name); 
	std::cout << object.dateipfade(test,0) << std::endl;
	system("pause");
}

