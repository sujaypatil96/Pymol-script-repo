#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;


void error_msg(char *);

int main()
{
  ifstream cinfile, uinfile;
  bool check_error;

  char cline[100];
  char cfield1[10], cfield3[10], cfield4[10];
  int cfield2, cfield5;
  float cfield6, cfield7, cfield8, cfield9, cfield10, ctotal;

  char uline[100];
  char ufield1[10], ufield3[10], ufield4[10];
  int ufield2, ufield5;
  float ufield6, ufield7, ufield8, ufield9, ufield10, utotal;

  check_error = false;
  ctotal = 0.0;
  utotal = 0.0;

  cinfile.open("/home/tlinnet/Software/pymol/Pymol-script-repo/modules/pdb2pqr/tests/test/test-output-correct.pqr");	
  uinfile.open("/home/tlinnet/Software/pymol/Pymol-script-repo/modules/pdb2pqr/tests/test/test-output-user.pqr");	
  
  if (!cinfile)
    error_msg("test-output-correct.pqr could not be opened");

  if (!uinfile)
    error_msg("test-output-user.pqr could not be opened");

  cinfile.getline(cline, 100);
  uinfile.getline(uline, 100);

  while(!cinfile.eof() && !uinfile.eof()) {
    while(!cinfile.eof() && !uinfile.eof()) {
      cinfile.getline(cline, 100);
      uinfile.getline(uline, 100);
      sscanf(cline, "%s", cfield1);

      if (strcmp(cfield1, "REMARK") == 0) {
        if (strcmp(cline, uline) != 0)
          error_msg("Found a difference in REMARK in the PQR files");
      }
      else
        break;
    } 

    while(!cinfile.eof() && !uinfile.eof()) {
      cinfile.getline(cline, 100);
      uinfile.getline(uline, 100);

      sscanf(cline, "%s %d %s %s %d %f %f %f %f %f", cfield1, &cfield2, cfield3, cfield4, &cfield5, &cfield6, &cfield7, &cfield8, &cfield9, &cfield10);
      sscanf(uline, "%s %d %s %s %d %f %f %f %f %f", ufield1, &ufield2, ufield3, ufield4, &ufield5, &ufield6, &ufield7, &ufield8, &ufield9, &ufield10);

      if (strcmp(cfield1, "ATOM") == 0) {
        if (strcmp(cfield1, ufield1) != 0 || cfield2 != ufield2 || strcmp(cfield3, ufield3) != 0 
	    || strcmp(cfield4, ufield4) != 0 || cfield5 != ufield5 || fabs(cfield6 - ufield6) > 0.1 
          || fabs(cfield7 - ufield7) > 0.1 || fabs(cfield8 - ufield8) > 0.1 
	    || fabs(cfield9 - ufield9) > 0.1 ||fabs(cfield10 - ufield10) > 0.1) {
	  check_error = true;
        }

        ctotal += cfield6 + cfield7 + cfield8 + cfield9 + cfield10;
        utotal += ufield6 + ufield7 + ufield8 + ufield9 + ufield10;
      }
      else
        break;
    }

    while(!cinfile.eof() && !uinfile.eof()) {
      cinfile.getline(cline, 100);
      uinfile.getline(uline, 100);

      sscanf(cline, "%s %s %s %d %f %f %f %f %f", cfield1, cfield3, cfield4, &cfield5, &cfield6, &cfield7, &cfield8, &cfield9, &cfield10);
      sscanf(uline, "%s %s %s %d %f %f %f %f %f", ufield1, ufield3, ufield4, &ufield5, &ufield6, &ufield7, &ufield8, &ufield9, &ufield10);

      if (strncmp(cfield1, "HETATM", 6) == 0) {
        if (strcmp(cfield1, ufield1) != 0 || strcmp(cfield3, ufield3) != 0 
	    || strcmp(cfield4, ufield4) != 0 || cfield5 != ufield5 || fabs(cfield6 - ufield6) > 0.1 
          || fabs(cfield7 - ufield7) > 0.1 || fabs(cfield8 - ufield8) > 0.1 
	    || fabs(cfield9 - ufield9) > 0.1 ||fabs(cfield10 - ufield10) > 0.1) {
	  check_error = true;
        }

        ctotal += cfield6 + cfield7 + cfield8 + cfield9 + cfield10;
        utotal += ufield6 + ufield7 + ufield8 + ufield9 + ufield10;
      }
      else
        break;
    }
  }
  if (!cinfile.eof() || !uinfile.eof())
    error_msg("Simple test failed because the user's PQR output file contains the wrong number of data items");

  if (check_error == true && fabs(ctotal - utotal) > 20)
    error_msg("Simple test failed because the numbers in the user PQR output file and the expected values are too big");

  cout << "Simple test passed for PQR files" << endl;

  cinfile.close();
  uinfile.close();

  return 0;
}

void error_msg(char * msg)
{
  cerr << "ERORR! " << msg << endl;
  exit(EXIT_FAILURE);
}
