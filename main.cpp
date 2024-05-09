#include "uGraph.h"
#include "illegal_exception.h"

bool invidail(string s)
{
	return atoi(s.c_str()) > 500000 || atoi(s.c_str()) <= 0;
}

string doOper(uGraph* quad, string command, istream& fin, bool Isinsert = false, string from = "", string to = "", double d = 0.0, double s = 0.0)
{
	string str = "";
	bool oper;
	try {
		if (command == "INSERT") {
			if (!Isinsert)
				fin >> from >> to >> d >> s;
			if (invidail(from) || invidail(to) || d <= 0.0 || s <= 0.0) {
				throw illegal_exception("illegal argument");
			}
			quad->insertEdge(from, to, d, s);
			str = "success";
		}
		else if (command == "PRINT") {
			fin >> from;
			if (invidail(from)) {
				throw illegal_exception("illegal argument");
			}
			oper = quad->print(from);
			str = (oper ? "" : "failure");
		}
		else if (command == "DELETE") {
			fin >> from;
			if (invidail(from)) {
				throw illegal_exception("illegal argument");
			}
			oper = quad->delet(from);
			str = (oper ? "success" : "failure");
		}
		else if (command == "PATH") {
			fin >> from >> to;
			if (invidail(from) || invidail(to)) {
				throw illegal_exception("illegal argument");
			}
			oper = quad->path(from, to);
			str = (oper ? "" : "failure");

		}
		else if (command == "TRAFFIC") {
			if (!Isinsert)
				fin >> from >> to >> s;
			if (invidail(from) || invidail(to)) {
				throw illegal_exception("illegal argument");
			}
			oper = quad->traffic(from, to, s);
			str = (oper ? "success" : "failure");
		}
		else if (command == "LOWEST") {
			fin >> from >> to;
			if (invidail(from) || invidail(to)) {
				throw illegal_exception("illegal argument");
			}
			oper = quad->lowest(from, to);
			str = (oper ? "" : "failure");
		}
	}
	catch (const illegal_exception& e) {
		str = e.what();
	}
	return str;
}

int main()
{
	uGraph* quad = new uGraph();
	string  command, str;
	string fileName;
	while (true)
	{
		cin >> command;
		if (command == "LOAD") {				
			cin >> fileName;
			ifstream fin(fileName);
			string from = "", to = "";
			double d = 0.0, s = 0.0;
			if (fin.is_open()) {
				command = "INSERT";
				while (fin >> from >> to >> d >> s) {
					doOper(quad, command, fin, true, from, to, d, s);
				}
				fin.close();
			}
			cout << "success" << endl;		
		}		
		else if (command == "UPDATE") {
			cin >> fileName;
			ifstream fin(fileName);
			string from = "", to = "";
			double d = 0.0, s = 0.0;
			str = "failure";
			if (fin.is_open()) {				
				while (fin >> from >> to >> s) {
					d = 0.0;
					command = "TRAFFIC";
					command = doOper(quad, command, fin, true, from, to, d, s);
					if (command == "success") {
						str = command;
					}
				}
				fin.close();
			}			
			cout << str << endl;
		}						
		else if (command == "END") {
			break;
		}
		else {
			cout << doOper(quad, command, cin) << endl;
		}
	}
	if (quad != nullptr)
		delete quad;
	return 0;
}