#include "C_DDI.h"
namespace fs = std::experimental::filesystem;
C_DDI::C_DDI()
= default;

C_DDI::~C_DDI()
= default;

// Erster Teil des Problems: Finde alle Daten und Speicher was benötigt wird für die Suche nach Duplikaten. Kriterien : Größe, Name 
// sammle_kandidaten() Iteriert über alle möglichen Daten vom angegeben Pfad aus,
// speichert diese in einem Vector vom Typ Context.
std::vector<Context> C_DDI::sammle_kandidaten(std::string pfad) // STABLE Für eine vorsortierung muss lediglich ein teil von prüfe kandidaten hier implementiert werden
{
	std::cout << "sammle kandidaten" << std::endl;
	Context context;
	std::vector<Context> vec_collect;
	vec_collect.reserve(400000);
	for (auto& p : fs::recursive_directory_iterator(pfad)) 
	{
		if (p.status().type() != fs::file_type::directory && fs::is_regular_file(p)) //is_regular_file(p) macht den spaß erst exceptionsafe
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

// Zweiter Teil des Problems, denke dir einen vernünftigen abgleichalgorythmus aus der nicht redundante Suchdatensätze bildet.
// whiteboard attacke
// Imaginärer Datensatz
// 1 <- Gesuchter Wert -> Save Index && pfad von duplikat wenn duplikat gefunden wurde
// 2
// 1 <- Save Index && pfad von duplikat
// 1 <- Save Index && pfad von duplikat
// 3
// 4
// 1 <- Save Index && pfad von duplikat
// -> Speicher Pfade,Lösche Indexpositionen aus Context Vektor
// Imaginärer datensatz nach prozedur
// 2
// 3
// 4
std::vector<Context> C_DDI::prüfe_kandidaten(std::vector<Context> Collection, Vergleichsmodi modi) // Selbst entwickelter Algorithmus, returns und parameterübergabe können natürlich beliebig geändert werden.
{
	std::cout << "prüfe kandidaten" << std::endl;
	bool pushedConditionalOnce = false;
	std::vector<Context> Doppelt;
	std::vector<int> indexVec;
	switch (modi)
	{
	case Vergleichsmodi::Größe:
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

	case Vergleichsmodi::Größe_und_Name:
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