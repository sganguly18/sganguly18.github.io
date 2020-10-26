#include<stdio.h>
#include<string.h>
#include <dirent.h>

int createFile(char *f, char *dirName);

void listing (FILE *fp,  char *dirName) {
  struct dirent *de;  // Pointer for directory entry
 
  // opendir() returns a pointer of DIR type. 
  DIR *dr = opendir(dirName);
 
  if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
      return;
    }
 
  // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
  // for readdir()
  while ((de = readdir(dr)) != NULL) {
    char *name = de->d_name;
    
    if (strcmp (".", name) == 0)
      continue;

    if (strcmp ("..", name) == 0)
      continue;

    int l = strlen(name);

    if (l>5) {
      int m = l-5;
      char* temp = name+m;

      if (strcmp (".html", temp) == 0)
	continue;
       
    }


    fprintf(fp,"<a href=\"");
    {
      char dName[100];
      sprintf  (dName, "%s/%s", dirName, name);

      char fName[100];
      sprintf  (fName, "%s.html", name);

      char s[100];
      sprintf (s,"../%s",dName);

      int ret = createFile  (fName, dName);

      if (ret != 0) 
	fprintf(fp,s);
      else
	fprintf(fp,fName);
    }

    fprintf(fp,"\">"); 
    fprintf(fp,name);
    fprintf(fp,"</a> <br>\n");
  }
 
  closedir(dr);    
}

int createFile(char *f, char *dirName) {
  //is a valid directory
  DIR *dr = opendir(dirName);
 
  if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
      return -1;
    }
  closedir(dr);

  char fName[100] = "Public/";
  strcat(fName,f);

  FILE *fp = fopen (fName,"w");

  //header
  fprintf (fp,"<html>\n");
  fprintf (fp,"<head>\n");
  fprintf (fp,"<title>RAQ User Study</title>\n");
  fprintf (fp,"</head>\n");
  fprintf (fp,"<body style=\"margin:25px;padding:20px;\">\n");
  fprintf (fp,"<h1> File Listing </h1>\n");

  //listing
  listing (fp, dirName);

  //footer
  fprintf (fp,"</body>\n");
  fprintf (fp,"</html>\n");

  fclose(fp);
  return 0;
}

void main(){
  createFile("list.html", "Public");
}
