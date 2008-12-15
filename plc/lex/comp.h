#include <stdio.h>
#include <stdlib.h>

char temploc[3] = {'#', '0', 0};

char templabel[3] = {'@', '0', 0};

struct tokenInfo {
  char *code;
  double  value;
  int lineNumber;
};

typedef struct tokenInfo tokenInfo;

/*** We create our own symbol table and functions for it here. ***/
struct varRec {
  char *name; /* the name of the variable */
  double value; /* the value the variable has - always a double */
  struct varRec *next; /* a link to the next part of the symbol table */
};

typedef struct varRec varRec;

/* The variable table: a chain of 'struct varRec'. */
varRec *varTable = NULL;
varRec *nextRec = NULL;


varRec *getVar(char *varName) {
  varRec *ptr=NULL, *returnValue=NULL;

  for (ptr = varTable; ptr != NULL;
       ptr = (varRec *) ptr->next) {
    if (!strcmp(ptr->name, varName))
      returnValue = ptr;
  }
  return returnValue;
}

varRec *putVar( char *varName, float varValue ) {
  varRec *ptr = getVar(varName);
  varRec *returnValue = NULL;

  if (getVar != NULL ) {
    ptr = (varRec *) malloc (sizeof (varRec));
    if (!varTable) {
      varTable = ptr;
      nextRec = ptr;
    } else nextRec->next = ptr;

    ptr->name = (char *) malloc( strlen(varName) + 1);
    strcpy(ptr->name, varName);
    ptr->value = varValue;
    ptr->next = (varRec *) 0;
    nextRec = ptr;
    returnValue = ptr;
  } else {
    ptr->value = varValue;
    returnValue = ptr;
  }    
  return returnValue;
}

void clearVar (void) {
  varRec *ptr, *next;
  for (ptr = varTable; ptr != (varRec *) 0;) {
    next = (varRec *) ptr->next;
    free(ptr);
    ptr = next;
  }
}

char * cat2(const char *s1, const char *s2) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(s, s1); strcat(s, s2);
  return s;
}

char * cat3(const char *s1, const char *s2, const char *s3) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3);
  return s;
}

char * cat4(const char *s1, const char *s2, const char *s3, const char *s4) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + 1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3); strcat(s, s4);
  return s;
}

char * cat5(const char *s1, const char *s2, const char *s3, const char *s4,
            const char *s5) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) +
             1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3); strcat(s, s4); strcat(s, s5);
  return s;
}

char * cat6(const char *s1, const char *s2, const char *s3, const char *s4,
            const char *s5, const char *s6) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) +
             strlen(s6) + 1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3); strcat(s, s4); strcat(s, s5);
  strcat(s, s6);
  return s;
}

char * cat7(const char *s1, const char *s2, const char *s3, const char *s4,
            const char *s5, const char *s6, const char *s7) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) +
             strlen(s6) + strlen(s7) + 1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3); strcat(s, s4); strcat(s, s5);
  strcat(s, s6); strcat(s, s7);
  return s;
}

char * cat8(const char *s1, const char *s2, const char *s3, const char *s4,
            const char *s5, const char *s6, const char *s7, const char *s8) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) +
             strlen(s6) + strlen(s7) + strlen(s8) + 1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3); strcat(s, s4); strcat(s, s5);
  strcat(s, s6); strcat(s, s7); strcat(s, s8);
  return s;
}

char * cat9(const char *s1, const char *s2, const char *s3, const char *s4,
            const char *s5, const char *s6, const char *s7, const char *s8,
            const char *s9) {
  char *s;
  s = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) +
             strlen(s6) + strlen(s7) + strlen(s8) + strlen(s9) + 1);
  strcpy(s, s1); strcat(s, s2); strcat(s, s3); strcat(s, s4); strcat(s, s5);
  strcat(s, s6); strcat(s, s7); strcat(s, s8); strcat(s, s9);
  return s;
}

char * gettemp() {
  char *temp = strdup( temploc );
  temploc[1]++;
  return temp;
}

char * getlabel() {
  char *temp = strdup( templabel );
  templabel[1]++;
  return temp;
}
