#coding=utf-8

import os
import sys
import json
import re

if __name__ == '__main__':
	dirPath, fileName = os.path.split(os.path.abspath(sys.argv[0]))
	jsonFilePath = dirPath + '\\ConfIni.json'
	print(jsonFilePath)
	
	if os.access(jsonFilePath, os.F_OK)==False:
		print('wrong - File Path')
	
	print('right - File Path')
	jsonFile = open(jsonFilePath, encoding='utf-8')
	jsonFileContent = json.load(jsonFile)
	
	StringContent = jsonFileContent['StringContent']
	
	pattern = re.compile(r'\d+')
	result = pattern.findall(StringContent)
	print(result)
	
	pattern = re.compile(r'python')
	result = pattern.findall(StringContent)
	print(result)
	
	pattern = re.compile(r'[Pp]ython')
	result = pattern.findall(StringContent)
	print(result)
	
	pattern = re.compile(r'[0-9]')
	result = pattern.findall(StringContent)
	print(result)
	
	pattern = re.compile(r'[a-z]')
	result = pattern.findall(StringContent)
	print(result)
	
	pattern = re.compile(r'[^Ppy]')
	result = pattern.findall(StringContent)
	print(result)
	
	Test1 = jsonFileContent['BaseSettings']['Test1']
	pattern = re.compile(r'colou?r')
	result = pattern.findall(Test1)
	print(result)
	
	Test2 = jsonFileContent['BaseSettings']['Test2']
	pattern = re.compile(r'ru*b')
	result = pattern.findall(Test2)
	print(result)
	pattern = re.compile(r'ru+b')
	result = pattern.findall(Test2)
	print(result)