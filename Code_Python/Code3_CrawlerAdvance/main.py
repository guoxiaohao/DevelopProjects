#coding=utf-8

import requests
import bs4
import re

if __name__ == '__main__':
	#resp = requests.get("http://xlzd.me/query", params={"name":"xlzd", "lang": "python"})
	#print(resp.url)
	#resp = requests.post("http://xlzd.me/login", data = {"user":"xlzd", "pass": "mypassword"})
	#print(resp.url)
	
	resp = requests.get("http://xlzd.me")
	print(resp.url)
	print(resp.encoding)
	print(resp.headers)
	#print(resp.cookies)
	#print(resp.text)