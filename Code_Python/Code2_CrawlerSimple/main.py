#coding=utf-8

import requests
import bs4

if __name__ == '__main__':
	print("主程序运行")
	
	strURL = "http://www.wise.xmu.edu.cn/people/faculty"
	dataURL = requests.get(strURL)
	
	if dataURL.status_code != 200:
		print("错误 - 获取 URL")
		
	print("正确 - 获取 URL")
	htmlURL = dataURL.content
	soupParser = bs4.BeautifulSoup(htmlURL, 'html.parser')
	
	#找到第一个带有‘div’标签,包含"class = 'people_list'"的HTML
	div_people_list =  soupParser.find('div', attrs={'class': 'people_list'})
	print(div_people_list)
	#find_all取出所有，返回列表
	#a_s = div_people_list.find_all('a', attrs={'target': '_blank'})
	
	#for a in a_s:
	#	url = a['href']
	#	name = a.get_text()
	#	print(name,url)