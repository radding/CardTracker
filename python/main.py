#from pymongo import MongoClient
import json
import crawler
import scraper

#client = MongoClient('mongodb://localhost:27017/')
#db = client.test.database

def main():
    #base = raw_input(']===>  scrape URL: ')
    base = 'http://www.cse.msu.edu/~cse232/'
    visited = list()
    crawler.Crawler(base, visited).run()
    for line in visited:
        #scraper.Scraper(line).run()
        pass

main()
