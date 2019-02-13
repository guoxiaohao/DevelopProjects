import os
import json
import urllib

if __name__ == '__main__':
    StrFile = 'ConfIni.json'
    bErrors = True
    if os.access(StrFile, os.F_OK):
        JsonFile = open(StrFile)
        StrJsonFile = json.load(JsonFile)
        if('WebSite' in StrJsonFile):
            StrWebSite = StrJsonFile['WebSite']
            try:
                ResponWeb = urllib.request.urlopen(StrWebSite, data=None, timeout=5)
            except:
                bErrors = False
            
            if bErrors:
                print(ResponWeb.read().decode('utf-8'))
            else:
                print('Timeout')
        else:
            print('Key Wrong')  
    else:
        print('File Not Existed')
else:
    print('Start Wrong')