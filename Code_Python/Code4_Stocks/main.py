#coding=utf-8

import requests
import bs4
import re
import os
import sys
import csv
import datetime
import time

if __name__ == '__main__':
	dirPath, fileName = os.path.split(os.path.abspath(sys.argv[0]))

	StrStock1 = 'sh601398'
	StrStock2 = 'sh601939'

	Today_ = datetime.date.today()
	str_today = Today_.strftime('%y%m%d')
	str_file1 = StrStock1 + '_' + str_today
	str_file2 = StrStock2 + '_' + str_today

	datafile1_path = dirPath + '\\' + str_file1
	datafile2_path = dirPath + '\\' + str_file2
	file1_handle = open(datafile1_path, "wb+")
	file2_handle = open(datafile2_path, "wb+")

	str_url = 'http://hq.sinajs.cn/list='
	url1 = str_url + StrStock1
	url2 = str_url + StrStock2
	while True:
		file1_handle.write(requests.get(url1).content)
		file2_handle.write(requests.get(url2).content)
		file1_handle.flush()
		file2_handle.flush()
		time.sleep(2)
	file1_handle.close()
	file2_handle.close()
