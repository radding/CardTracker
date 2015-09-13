from manager import Manager
#from pymongo import MongoClient
import json

#client = MongoClient('mongodb://localhost:27017/')
#db = client.test.database

def main():
    #base = list(raw_input(']===>  scrape URL: '))
    base = 'http://www.cse.msu.edu/~cse232/'
    links = open('links.json', 'r+')
    pages = open('pages.json', 'r+')
    admin = Manager(links, pages)

    admin.crawler(base)

    while True:
        links = open('links.json', 'r')
        for line in links:
            link = json.loads(line)['url'][0]
            print("====>" + str(link))
            admin.run(admin.crawler, str(link))

        admin.jobs.join()


main()
