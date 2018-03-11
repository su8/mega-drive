
#include <Python.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
  PyObject *pName = NULL, *pModule = NULL, *pFunc = NULL;
  PyObject *pValue = NULL;

  char pat[200];
  snprintf(pat, 199, "%s:%s", (char *)Py_GetPath(), "/home/frost/pypi");

  Py_Initialize();
  Py_SetPythonHome((wchar_t *)pat);
  Py_SetPath((wchar_t *)pat);
  printf("%s\n", (char *)Py_GetPath());
  /* PySys_SetPath((const wchar_t *)pat); */
  pName = PyUnicode_DecodeFSDefault((char *)"multi");
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
    printf("Result of call: %s\n", PyUnicode_AsUTF8(pValue));
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
