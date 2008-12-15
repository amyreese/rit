#include <stdio.h>
#include <stdlib.h>
struct tokenInfo
{
  char *name;
  double  value;
  int lineNumber;
};
typedef struct tokenInfo tokenInfo;

/*** We create our own symbol table and functions for it here. ***/
struct varRec
{
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

varRec *putVar( char *varName, float varValue )
{
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
};

void clearVar (void) {
  varRec *ptr, *next;
  for (ptr = varTable; ptr != (varRec *) 0;) {
    next = (varRec *) ptr->next;
    free(ptr);
    ptr = next;
  }
};
