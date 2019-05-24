#include "C_DDI.h"
namespace fs = std::experimental::filesystem;
C_DDI::C_DDI()
= default;

C_DDI::~C_DDI()
= default;

// Erster Teil des Problems: Finde alle Daten und Speicher was ben�tigt wird f�r die Suche nach Duplikaten. Kriterien : Gr��e, Name 
// sammle_kandidaten() Iteriert �ber alle m�glichen Daten vom angegeben Pfad aus,
// speichert diese in einem Vector vom Typ Context.
std::vector<Context> C_DDI::sammle_kandidaten(std::string pfad) // STABLE F�r eine vorsortierung muss lediglich ein teil von pr�fe kandidaten hier implementiert werden
{
	std::cout << "sammle kandidaten" << std::endl;
	Context context;
	std::vector<Context> vec_collect;
	vec_collect.reserve(400000);
	for (auto& p : fs::recursive_directory_iterator(pfad)) 
	{
		if (p.status().type() != fs::file_type::directory && fs::is_regular_file(p)) //is_regular_file(p) macht den spa� erst exceptionsafe
		{
			context.s_fileSize = fs::file_size(p);
			context.s_filePath = fs::path(p).string();
			context.s_fileName = fs::path(p).filename().string();
			//context.s_Extention = fs::path(p).extension().string();
			vec_collect.push_back(context);
		}
	}
	return vec_collect;
}

// Zweiter Teil des Problems, denke dir einen vern�nftigen abgleichalgorythmus aus der nicht redundante Suchdatens�tze bildet.
// whiteboard attacke
// Imagin�rer Datensatz
// 1 <- Gesuchter Wert -> Save Index && pfad von duplikat wenn duplikat gefunden wurde
// 2
// 1 <- Save Index && pfad von duplikat
// 1 <- Save Index && pfad von duplikat
// 3
// 4
// 1 <- Save Index && pfad von duplikat
// -> Speicher Pfade,L�sche Indexpositionen aus Context Vektor
// Imagin�rer datensatz nach prozedur
// 2
// 3
// 4
std::vector<Context> C_DDI::pr�fe_kandidaten(std::vector<Context> Collection, Vergleichsmodi modi) // Selbst entwickelter Algorithmus, returns und parameter�bergabe k�nnen nat�rlich beliebig ge�ndert werden.
{
	std::cout << "pr�fe kandidaten" << std::endl;
	bool pushedConditionalOnce = false;
	std::vector<Context> Doppelt;
	std::vector<int> indexVec;
	switch (modi)
	{
	case Vergleichsmodi::Gr��e:
		for (std::vector<Context>::size_type i = 0; i < Collection.size(); i++)
		{
			Context Conditional = Collection[0];
			std::swap(Collection[0], Collection.back());
			Collection.pop_back();
			for (std::vector<Context>::size_type j = 0; j < Collection.size(); j++)
			{

				if (Conditional.s_fileSize == Collection[j].s_fileSize)
				{
					if (pushedConditionalOnce == false)
					{
						Doppelt.push_back(Conditional);
						pushedConditionalOnce = true;
					}
					Doppelt.push_back(Collection[j]);
					indexVec.push_back(j);
				}
			}
			for (std::vector<int>::size_type st = 0; st < indexVec.size(); st++)
			{
				std::swap(Collection[indexVec[st]], Collection.back());
				Collection.pop_back();
			}
			indexVec.clear();
			pushedConditionalOnce = false;
		}
		break;

	case Vergleichsmodi::Gr��e_und_Name:
		for (std::vector<Context>::size_type i = 0; i < Collection.size(); i++)
		{
			Context Conditional = Collection[0];
			std::swap(Collection[0], Collection.back());
			Collection.pop_back();
			for (std::vector<Context>::size_type j = 0; j < Collection.size(); j++)
			{

				if (Conditional.s_fileSize == Collection[j].s_fileSize && Conditional.s_fileName == Collection[j].s_fileName)
				{
					if (pushedConditionalOnce == false)
					{
						Doppelt.push_back(Conditional);
						pushedConditionalOnce = true;
					}
					Doppelt.push_back(Collection[j]);
					indexVec.push_back(j);
				}
			}
			for (std::vector<int>::size_type st = 0; st < indexVec.size(); st++)
			{
				std::swap(Collection[indexVec[st]], Collection.back());
				Collection.pop_back();
			}
			indexVec.clear();
			pushedConditionalOnce = false;
		}
		break;
	}

	return Doppelt;
}


std::string C_DDI::dateipfade(std::vector<Context> Collection, int i) 
{
	std::cout << "gebe kandidat" << std::endl;
	return Collection[i].s_filePath;
}