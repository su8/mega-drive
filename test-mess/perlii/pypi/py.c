
#include <Python.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
  PyObject *pName = NULL, *pModule = NULL, *pFunc = NULL;
  PyObject *pValue = NULL;

  char pat[200];
  snprintf(pat, 199, "%s:%s", Py_GetPath(), "/home/frost/pypi");
  printf("%s\n", Py_GetPath());

  Py_Initialize();
  PySys_SetPath(pat);
  pName = PyString_FromString((char *)"multi");
  if (NULL == pName) {
    goto error;
  }

/* PyErr_Print(); */
  pModule = PyImport_Import(pName);
  Py_DECREF(pName);
  if (NULL == pModule) {
PyErr_Print();
    goto error;
    /* return -1; */
  }
PyErr_Print();
  pFunc = PyObject_GetAttrString(pModule, (char *)"uzer_func");
  if (NULL == pFunc && 0 == PyCallable_Check(pFunc)) {
PyErr_Print();
    goto error;
  }

  pValue = PyObject_CallObject(pFunc, NULL);
  if (NULL != pValue) {
    printf("Result of call: %s\n", PyString_AsString(pValue));
  }

error:
  if (NULL != pValue) {
    Py_XDECREF(pValue);
  }
  if (NULL != pFunc) {
    Py_XDECREF(pFunc);
  }
  if (NULL != pModule) {
    Py_XDECREF(pModule);
  }

  Py_Finalize();
  return -1;
}
