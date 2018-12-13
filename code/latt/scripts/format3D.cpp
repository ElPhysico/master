/* g++ -o format3D format3D.cpp */
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

ifstream infile;
FILE *outfile;
string file;

void ReadCommandLine(int argc, char const *argv[], string &file)
{
	for (int i = 1; i < argc; i++) {
		if (strstr(argv[i], "-path="))
			file = argv[i] + 6;
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
	string h1, h2, h3, h4, h5, h6, h7, h8;
	double minmfpt=1e10;
	vector<double> p_min, p_max, mfpt, delta;
	vector<double> sorted_p_min, sorted_p_max, sorted_mfpt, sorted_delta;
	ReadCommandLine(argc, argv, file);

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
		string sp_min, sp_max, smfpt, sdelta;
		while (infile >> sp_min >> sp_max >> smfpt >> sdelta) {
			if (atof(smfpt.c_str()) <= minmfpt)
				minmfpt = atof(smfpt.c_str());
			p_min.push_back(atof(sp_min.c_str()));
			p_max.push_back(atof(sp_max.c_str()));
			mfpt.push_back(atof(smfpt.c_str()));
			delta.push_back(atof(sdelta.c_str()));

		}
		printf("Min. MFPT is: %.1f\n", minmfpt);
	}
	infile.close();

	int min_index;
	double pmin, pmax;
	while ((int) p_min.size() >= 1) {
		min_index = -1;
		pmin = 2.0;
		pmax = 2.0;
		for (int i = 0; i < (int) p_min.size(); i++) {
			if (p_min[i] < pmin) {
				pmin = p_min[i];
				pmax = p_max[i];
				min_index = i;
			} else if (p_min[i] == pmin && p_max[i] < pmax) {
				pmax = p_max[i];
				min_index = i;
			}
		}
		sorted_p_min.push_back(p_min[min_index]);
		sorted_p_max.push_back(p_max[min_index]);
		sorted_mfpt.push_back(mfpt[min_index]);
		sorted_delta.push_back(delta[min_index]);
		p_min.erase(p_min.begin() + min_index);
		p_max.erase(p_max.begin() + min_index);
		mfpt.erase(mfpt.begin() + min_index);
		delta.erase(delta.begin() + min_index);
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
	fprintf(outfile, h6.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, h7.c_str());
	fprintf(outfile, "\n");
	fprintf(outfile, "\n");
	fprintf(outfile, h8.c_str());

	double pnow = sorted_p_min[0];
	for (int i = 0; i < (int) sorted_p_min.size(); i++) {
		if (sorted_p_min[i] > pnow) {
			fprintf(outfile, "\n");
			pnow = sorted_p_min[i];
		}
		fprintf(outfile, "\n");
		fprintf(outfile, "%.3f", sorted_p_min[i]);
		fprintf(outfile, "\t%.3f", sorted_p_max[i]);
		fprintf(outfile, "\t%f\t%f", sorted_mfpt[i], sorted_delta[i]);
	}

	fclose(outfile);


	return 0;
}
