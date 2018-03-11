:TOP
@CLS
@ECHO OFF

SET /P NAME=



:BEGIN
CLS
key.exe -vi%name%
PAUSE
GOTO INPUT
EXIT