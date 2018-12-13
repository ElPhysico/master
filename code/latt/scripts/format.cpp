a<y/* g++ -o format format.cpp */
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

ifstream infile;
FILE *outfile;
string file;
double val;

void ReadCommandLine(int argc, char const *argv[], string &file, double &val)
{
	for (int i = 1; i < argc; i++) {
		if (strstr(argv[i], "-path="))
			file = argv[i] + 6;
		if (strstr(argv[i], "-val="))
			val = atof(argv[i] + 5);
	}
}

// skips k lines from current position
void skip_lines(int k, ifstream &datei) {
    int l = 0;
    string skippedline;
    while (datei && l < k) {
        getline(datei, skippedline);
        l++;
    }
}

int main(int argc, char const *argv[])
{
	val = 0;
	string h1, h2, h3, h4, h5, h6, h7, h8;
	double fpt_zero, fpt_d_zero;
	vector<double> p, fpt, fpt_d;
	vector<double> sorted_p, sorted_fpt, sorted_fpt_d;
	ReadCommandLine(argc, argv, file, val);

	infile.open(file.c_str());
	if (!infile) {
		cerr << "Error: can't read file\n";
	} else {
		getline(infile, h1);
		getline(infile, h2);
		getline(infile, h3);
		getline(infile, h4);
		getline(infile, h5);
		getline(infile, h6);
		getline(infile, h7);
		getline(infile, h8);
		getline(infile, h8);
		string sp, sfpt, sfpt_d, sscfpt, sscfpt_d;
		while (infile >> sp >> sfpt >> sfpt_d >> sscfpt >> sscfpt_d) {
			if (atof(sp.c_str()) == val) {
				fpt_zero = atof(sfpt.c_str());
				fpt_d_zero = atof(sfpt_d.c_str());
			}
			p.push_back(atof(sp.c_str()));
			fpt.push_back(atof(sfpt.c_str()));
			fpt_d.push_back(atof(sfpt_d.c_str()));

		}
		printf("FPT-Zero is: %.6f and delta is: %.6f\n", fpt_zero, fpt_d_zero);
	}
	infile.close();

	int min_index;
	double min;
	while ((int) p.size() >= 1) {
		min_index = -1;
		min = 2.0;
		for (int i = 0; i < (int) p.size(); i++) {
			if (p[i] < min) {
				min = p[i];
				min_index = i;
			}
		}
		sorted_p.push_back(p[min_index]);
		sorted_fpt.push_back(fpt[min_index]);
		sorted_fpt_d.push_back(fpt_d[min_index]);
		p.erase(p.begin() + min_index);
		fpt.erase(fpt.begin() + min_index);
		fpt_d.erase(fpt_d.begin() + min_index);
	}

	outfile = fopen(file.c_str(), "w");
	fprintf(outfile, h1.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, h2.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, h3.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, h4.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, h5.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, "\n");
	fprintf(outfile, h6.c_str());
	fprintf(outfile, "\n");

	for (int i = 0; i < (int) sorted_p.size(); i++) {
		fprintf(outfile, "\n");
		fprintf(outfile, "%.3f", sorted_p[i]);
		fprintf(outfile, "\t%f\t%f", sorted_fpt[i], sorted_fpt_d[i]);
		fprintf(outfile, "\t%f", sorted_fpt[i] / fpt_zero);
		fprintf(outfile, "\t%f", sorted_fpt_d[i] / fpt_zero);
	}

	fclose(outfile);


	return 0;
}
