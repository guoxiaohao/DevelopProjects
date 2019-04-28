#coding=utf-8

import requests
import bs4
import re
import os
import sys
import csv

if __name__ == '__main__':
	dirPath, fileName = os.path.split(os.path.abspath(sys.argv[0]))
	
	print("0--Read RawData Generate ResultData;1--Generate CSV File;2--Generate Normal File;O(Other)--Read NetWorks and Generate RawData")
	inputContent = input("input:")
	
	if inputContent=="0":
		jsonFilePath = dirPath + '\\RawData.txt'
		
		dataFiles = open(jsonFilePath, "rb")
		htmlURL = dataFiles.read()
		dataFiles.close()
		
		soupParser = bs4.BeautifulSoup(htmlURL, 'html.parser')
		div_people_list = soupParser.find('div', attrs={'class': 'people_list'})
		people_list_info = div_people_list.find_all('tr')
		numbTotal = 0
		
		datafilepath = dirPath + '\\ResultData.txt'
		datafileresults = open(datafilepath, "wb+")
		for everyone in people_list_info:
			everyoneName = everyone.find('a', attrs={'target': '_blank'})
			if everyoneName:
				numbTotal = numbTotal + 1
				print(numbTotal)
				everyonelements = everyone.find_all('td')
				url = everyoneName['href']
				datafileresults.write(url.encode("utf-8"))
				for telements in everyonelements:
					datafileresults.write(telements.get_text().encode("utf-8"))
		datafileresults.close()
		print("Program Ends")
	elif inputContent=="1":
		csvFilePath = dirPath + '\\supers_days_16.csv'
		
		listContents1 = ["0", "1", "2", "3", "4", "5", "6", "7", "8"]
		print( type(listContents1) )
		strContents1 = ','.join(listContents1)
		print( type(strContents1) )
		bContents1 = strContents1.encode(encoding = "utf-8")#bytes(strContents1, encoding = "utf8")
		print( type(bContents1) )
		
		#csvFiles = open(csvFilePath, "wb")
		#csvWrite = csv.writer(csvFiles)
		#csvWrite.writerow(bContents1)
		#csvFiles.close()
		
		#csvFiles = open(csvFilePath, "a+")
		#csvWrite.writerows([[0, 1, 0.704970959, 1, "35.4770574,-83.3205859;35.0964003,-83.7199136;35.624394,-82.9931607;35.1197519,-83.336188;35.4328955,-83.4643551;35.2190534,-82.7778579;", 0.704970959, 35.29920894, -83.60877046, "1,1,1,1,1,0"]])
		#csvFiles.close()
		print("Program Ends")
	elif inputContent=="2":
		normalFilePath = dirPath + '\\supers_days_16.txt'
		
		normalFiles = open(normalFilePath, "w")
		normalFiles.write("0, 1, 2, 3, 4, 5, 6, 7, 8")
		normalFiles.write("\n")
		normalFiles.write("0, 1, 0.704970959, 1, 35.4770574,-83.3205859;35.0964003,-83.7199136;35.624394,-82.9931607;35.1197519,-83.336188;35.4328955,-83.4643551;35.2190534,-82.7778579;, 0.704970959, 35.29920894, -83.60877046, 1,1,1,1,1,0")
		normalFiles.close()
		print("Program Ends")
	else:
		jsonFilePath = dirPath + '\\RawData.txt'
		
		strURL = "http://www.wise.xmu.edu.cn/people/faculty"
		dataURL = requests.get(strURL)
		if dataURL.status_code != 200:
			print("wrong - URL")
		else:
			print("right - URL")
			htmlURL = dataURL.content
			dataFiles = open(jsonFilePath, "wb+")
			dataFiles.write(htmlURL)
			dataFiles.close()
		print("Program Ends")
		
#的degreeList是以字节读入的，degreeList是一个字节列表。
#for d in degreeList:
#      这里d是一个字节对象，而不是字符串，因此d.split(' ') 这里提示类型错误，改为d.decode().split()即可