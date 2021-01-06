#include"Node_structure.h"
#include <queue>


namespace structure_graf
{

	class Graf
	{

	private:
		list<shared_ptr<Node>> NoduriGraf;//lista care v-a retine adresele fiecarui nod din graf (fiecare nod este head - capul listei inlantuite)
		list < shared_ptr<Node> > NodesSearchedInGraf{};//lista in care vom insera nodurile parcurse de PRIM.

	public:
        //------------------------------------------------------------
		bool GrafVid();

		void InsertNodeParam(int);

		void InsertArcParam(bool, int, int, size_t);

		void PrimAlgo();


		bool NodeExistsInNodesSearchedInGraf(shared_ptr<Node>&);
		bool NodeExistsInList(shared_ptr<Node>&, list < shared_ptr<Node>>&);

		void PrintStructure();
		void afisareNoduriGraf();
		void PrintNodesSearchedInGraf();
		void PrintQueue(queue <shared_ptr<Node>>&);

		size_t sizeof_NoduriGraf() { return NoduriGraf.size(); }


		
		void clearSearchedList() { NodesSearchedInGraf.clear(); }
		auto getFirstNode() { return this->NoduriGraf.begin(); }
		//------------------------------------------------------------

		
		//constructor - initializare obiect graf - InitGraf()
		Graf()
		{

			//cream lista fara noduri
			NoduriGraf.clear();
			NodesSearchedInGraf.clear();
		
		}

		~Graf() = default;

	};

	//functie de afisare a numerelor gasita de Prim
	void  structure_graf::Graf::PrintNodesSearchedInGraf()
	{

		for (auto iterator = this->NodesSearchedInGraf.begin(); iterator != this->NodesSearchedInGraf.end(); ++iterator)
		{

			cout << iterator->get()->getData() << "  ";

		}

	}

	//verificam daca un nod exista in coada clasei graf
	void structure_graf::Graf::PrintQueue(queue <shared_ptr<Node>>& actualQueue)
	{
		queue<shared_ptr<Node>> temp = actualQueue;

		while (!temp.empty())
		{
			std::cout << temp.front()->getData()<< " ";
			temp.pop();
		}
		std::cout << std::endl;

	}

	//functia de verificare graf vid
	bool Graf::GrafVid()
	{

		//daca marimea vectorului NoduriGraf care retine adresele nodurilor din graf e 0 avem graf vid.
		if (NoduriGraf.empty())
		{

			cout << "Graf Vid!" << endl;
			return true;

		}
		else
		{

			return false;

		}

	}


	//functie de stergere nod parametru dintr-o lista parametru
	void DeleteNodeInList(shared_ptr<Node>& deleteNode, list < shared_ptr<Node>>& li)
	{

		//folosim un obiect de tipul std::list<>::iterator pentru iteratie in lista parametru
		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			//daca nodul pe care dorim sa il stergem este cel la care am ajuns in iteratie apelam functia de erase
			if (*iterator == deleteNode)
			{

				li.erase(iterator);
				return;
			
			}

		}

	}


	//functie de afisare a coadei
	void print_queue(queue<shared_ptr<Node>>& q)
	{
		cout << "Queue: ";

		while (!q.empty())
		{

			cout << q.front()->getData() << "\t";
			q.pop();

		}

	}


	//functie de afisare a unei liste oarecare
	void print_list(list<shared_ptr<arc>>& li)
	{


		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			cout <<iterator->get()->getNextNode()->getData() << "(w:" <<iterator->get()->getNextWeight()<<')' << "->";

		}

		cout << endl;

	}


	//functie de afisare lista cu adresele fiecarui element din lista
	void print_list_verbose(list<shared_ptr<arc>>& li)
	{


		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			cout << iterator->get()->getNextNode()->getData()
				<< " (" << iterator->get()->getNextNode() << ") "
				<< "->";

		}

		cout << endl;

	}


 
	//functia de afisare noduri graf, iteram in lista care retine adresa nodurilor aici afisam doar nodurile prezente in graf, nu si structura grafului
	void Graf::afisareNoduriGraf()
	{
		if (this->GrafVid())
		{

			return;

		}
		else
		{

			cout << "Graful contine:\n";

			shared_ptr<Node> temp{};

			for (auto i = NoduriGraf.begin(); i != NoduriGraf.end(); ++i)
			{

				cout << i->get()->getData() << endl;

			}

		}

	}

	//functie de afisare structura a grafului - afisam fiecare arc pe care il are un nod pe o linie
	void Graf::PrintStructure()
	{

		if (this->GrafVid())
		{

			return;

		}

		bool optiune{ false };

		cout << "Doriti sa afisati si adresele nodurilor? (1 - DA / 0 - NU)" << endl;
		cin >> optiune;

		cout <<"====================Structura graf===================="<< endl;
		if (optiune)
		{

			//iteram in lista nodurilor grafului 
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				auto tempList = actual->get()->getNextArc();

				cout << actual->get()->getData()
					<< " (" << *actual << ") "
					<< "  ->";
				print_list_verbose(tempList);

				cout << endl;

			}

			return;

		}
		else
		{

			//iteram in lista nodurilor grafului 
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				auto tempList = actual->get()->getNextArc();

				cout << actual->get()->getData()<< "  ->";
				print_list(tempList);

				cout << endl;

			}
			
			return;

		}

	}

	
	void Graf::InsertNodeParam(int newNumber)
	{

		try
		{

			bool numberAlreadyExists{ false };

			shared_ptr<Node> newNode = make_shared<Node>();//alocam memorie pentru un nou nod al grafului
			//daca alocarea memorie nu are loc, sarim in blocul de catch;

			cout << "\nIntroduceti un numar in noul nod: ";	//cin >> newNumber;
			newNode->setData(newNumber);



			//dorim sa ne asiguram ca cheia introdusa nu exista deja in graf
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca avem deja numarul in list, deci nu putem face insertia
				if (actual->get()->getData() == newNode->getData())
				{

					numberAlreadyExists = true;
					break;

				}

			}


			if (numberAlreadyExists)
			{

				cout << "Numarul introdus exista deja in graf." << endl;
				return;

			}
			else
			{

				NoduriGraf.push_back(newNode);//introducem noul nod in lista care va retine adresele nodurilor grafului

			}

		}

		//verificam daca alocarea memoriei a avut loc(daca functia "make_shared" nu poate aloca memorie aceasta arunca un obiect de tipul "bad_alloc" -> alocarea memoriei dinamica pentru "newNode" nu mai are loc
		catch (const bad_alloc& e)
		{

			cout << "Nu am putut aloca memorie pentru un nou nod.\n" << e.what() << '\n';
			return;

		}

	}


	//verificam daca un nod exista in lista rezultata din cautarea nodurilor 
	bool  structure_graf::Graf::NodeExistsInNodesSearchedInGraf(shared_ptr<Node>& actual)
	{
		
		for (auto iterator = this->NodesSearchedInGraf.begin(); iterator != this->NodesSearchedInGraf.end(); ++iterator)
		{

			if (iterator->get()->getData() == actual->getData())
			{
			
				return true;
		
			}
		
		}

		return false;

	}



	//verificam daca un nod exista in lista
	bool  structure_graf::Graf::NodeExistsInList(shared_ptr<Node>& actual , list<shared_ptr<Node>>& li)
	{

		for (auto iterator = li.begin(); iterator != li.end(); ++iterator)
		{

			if (*iterator == actual)
			{

				return true;

			}

		}

		return false;

	}





    //functia de inserare arc
	void structure_graf::Graf::InsertArcParam(bool ConnectionType, int source, int target, size_t weight)
	{

		if (this->GrafVid())
		{

			return;

		}

		//aceste nodri vor retine adresele nodurilor la care dorim sa inseram un arc (source - target)
		shared_ptr<Node> pointerToSourceNode;
		shared_ptr<Node> pointerToTargetNode;

		int targetWasFound{ false };
		int sourceWasFound{ false };

		cout << "Introduceti doua noduri pe care doriti sa le conectati / deconectati: " << endl;

		cout << "Primul numar: "<<source;   // cin >> number1;
		cout << "\nAl doilea numar: " << target << endl;// cin >> number2;

		try
		{

			//ne asiguram prima data ca numerele la care dorim sa introducem un arc exista in graf
			//iteram in lista pana cand gasim nodul la care dorim sa ii adaugam un arc
			for (auto actual = NoduriGraf.begin(); actual != NoduriGraf.end(); ++actual)
			{

				//daca cheia nodului urmator din iteratie este egala cu numarul pe care dorim sa il aflam setam pe true si inregistram adresa nodului in variabila pointerToNode
				if (source == actual->get()->getData())
				{

					cout << "Primul numar a fost gasit in graf" << endl;
					sourceWasFound = true;
					pointerToSourceNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

				if (target == actual->get()->getData())
				{
					cout << "Al doilea numar a fost gasit in graf" << endl;
					targetWasFound = true;
					pointerToTargetNode = *actual;//salvam adresa nodului pentru operatii viitoare

				}

			}

			//dupa ce am gasit numerele facem legaturile
			if (sourceWasFound && targetWasFound)
			{

				shared_ptr<arc> nextArcSource = make_shared<arc>();
				shared_ptr<arc> nextArcTarget = make_shared<arc>();

				nextArcSource->setNext(pointerToTargetNode, weight);
				nextArcTarget->setNext(pointerToSourceNode, weight);


				//--------------------------------------Nodul 1------------------------------------------------------------
				//daca dorim sa facem legatura apelam functia de set next a nodului source
				if (ConnectionType == true)
				{

					pointerToSourceNode->setNextArc(nextArcSource);//stabilim legaturile source
					pointerToTargetNode->setNextArc(nextArcTarget);//stabilim legaturile target
					cout << "Succes, link creat!" << endl;
					return;

				}
				else//daca dorim sa stergem legatura prima data trebuie sa cautam ca exista un link intre cele doua noduri, dupa care le vom sterge.
				{

					//iteram in lista nodurilor legate la target pentru a verifica daca source exista in aceasta lista, daca exista vom sterge adresa din lista.
					//pentru nodul target
					auto tempListTarget = pointerToTargetNode->getNextArc();
					auto tempListSource = pointerToSourceNode->getNextArc();

					cout << "Lista lui target: ";
					print_list(tempListTarget);
					cout << "Lista lui source: ";
					print_list(tempListSource);


					for (auto iterator = tempListTarget.begin(); iterator != tempListTarget.end(); ++iterator)
					{

						if (iterator->get()->getNextNode() == pointerToSourceNode)
						{

							cout << "Nodul " << iterator->get()->getNextNode()->getData() << " va fi sters!" << endl;
							tempListTarget.erase(iterator);//stergem nodul source din lista

							pointerToTargetNode->clearNextList();//stergem lista principala
							pointerToTargetNode->setNextList(tempListTarget);//trimitem ca si parametru lista temporara in lista principala(refresh list)

							break;

						}

					}


					//pentru nodul source
					for (auto iterator = tempListSource.begin(); iterator != tempListSource.end(); ++iterator)
					{

						if (iterator->get()->getNextNode() == pointerToTargetNode)
						{

							cout << "Nodul " << iterator->get()->getNextNode()->getData() << " va fi sters!" << endl;
							tempListSource.erase(iterator);//stergem nodul source din lista

							pointerToSourceNode->clearNextList();//stergem lista principala
							pointerToSourceNode->setNextList(tempListSource);//trimitem ca si parametru lista temporara in lista principala(refresh list)

							break;

						}

					}

				}

			}

		}
		catch (exception e)
		{

			cout << e.what() << endl;
			return;

		}

		if (!sourceWasFound)
		{

			cout << "Numarul " << source << " nu exista in graf" << endl;
			return;

		}

		if (!targetWasFound)
		{

			cout << "Numarul " << target << " nu exista in graf" << endl;
			return;

		}


	}



	/*
	  vom implementa algoritmul lui prim prin gasirea celui mai mic arc din graf(cu ponderea cea mai mica),
	  dupa care adaugam numerele gasite prin ponderea cea mai mica intr-un tablou pe care il vom afisa la final.
	  
	  1.Adaugam cele doua noduri cu cel mai mic arc din graf in tabloul cu numere gasite.
	  2.verificam ponderea arcelor nodurilor adaugate in tablou, dupa care adaugam nodul care area cea mai mica pondere.
	*/
	void structure_graf::Graf::PrimAlgo() 
	{

		list<shared_ptr<arc>> listOfArches;//lista care va retine nodurile legate la un nod

		size_t currentWeight=0;
		size_t currentSmallestWeight=SIZE_MAX;
		size_t counter = 0;

		queue<shared_ptr<Node>> que;//vom folosi un queue pentru a gasi nodurile care au cel mai mic arc intre ele

		for (auto actualNode = NoduriGraf.begin(); actualNode != NoduriGraf.end(); actualNode++)
		{

			cout << actualNode->get()->getData() << endl;

			listOfArches = actualNode->get()->getNextArc();//lista de noduri catre care avem arc din actualNode
			
			for (auto actualArch = listOfArches.begin(); actualArch != listOfArches.end(); actualArch++)
			{

				cout << actualArch->get()->getNextNode()->getData()<<"    ";
				cout << actualArch->get()->getNextNode()<<" w:";
				cout << actualArch->get()->getNextWeight() << endl;

				currentWeight = actualArch->get()->getNextWeight();

				if (currentWeight < currentSmallestWeight)
				{

					currentSmallestWeight = currentWeight;
					if (counter == 0)
					{

						que.push(*actualNode);
						que.push(actualArch->get()->getNextNode());
						counter = 1;
					
					}
					else
					{

						que.push(*actualNode);
						que.push(actualArch->get()->getNextNode());
						que.pop();
						que.pop();

					}
					
					
				}

				 
			}
			cout << endl;
		
		}

		//punem primul elelment din queue in lista de noduri parcursa dupa care dam pop si punem al doilea element in lista.
		NodesSearchedInGraf.push_back(que.front());
		que.pop();
		NodesSearchedInGraf.push_back(que.front());
		que.pop();
		
		
		PrintNodesSearchedInGraf();
		cout << endl;

		/// 
		/// =====pana in acest pas am gasit cele doua noduri cu weight-ul cel mai mic din graf, putem incepe implementarea algoritmului=====
		/// 
		cout << "\n===========================================" << endl;
		cout << "===============Pasul 2=====================" << endl;
		cout << "===========================================\n" << endl;


	

		shared_ptr<Node> nextNode = nullptr;
		counter = 0;
		for (auto actualNode = NodesSearchedInGraf.begin(); actualNode != NodesSearchedInGraf.end(); actualNode++)
		{

			cout << actualNode->get()->getData() << endl;

			listOfArches = actualNode->get()->getNextArc();//lista de noduri catre care avem arc din actualNode

			for (auto actualArch = listOfArches.begin(); actualArch != listOfArches.end(); actualArch++)
			{
				nextNode = actualArch->get()->getNextNode();
				if (NodeExistsInList( nextNode, NodesSearchedInGraf) )
				{
					continue;
				}

				cout << actualArch->get()->getNextNode()->getData() << "    ";
				cout << actualArch->get()->getNextNode() << " w:";
				cout << actualArch->get()->getNextWeight() << endl;

				currentWeight = actualArch->get()->getNextWeight();

				if (currentWeight < currentSmallestWeight)
				{

					currentSmallestWeight = currentWeight;
					if (counter == 0)
					{

						que.push(*actualNode);
						que.push(actualArch->get()->getNextNode());
						counter = 1;

					}
					else
					{

						que.push(*actualNode);
						que.push(actualArch->get()->getNextNode());
						que.pop();
						que.pop();

					}


				}


			}
			cout << endl;

		}















	}

}

