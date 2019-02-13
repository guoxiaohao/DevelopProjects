import os
import json

if __name__ == '__main__':
    StrFile = 'ConfIni.json'
    if os.access(StrFile, os.F_OK):
        JsonFile = open(StrFile)
        StrJsonFile = json.load(JsonFile)
        StrWebSite = StrJsonFile['WebSite']
        print(StrWebSite)
    else:
        print('File Not Existed')
else:
    print('Start Wrong')