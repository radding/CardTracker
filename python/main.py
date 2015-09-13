from manager import Manager
import json

def main():
    #base = list(raw_input(']===>  scrape URL: '))
    base = ['http://iah201.tumblr.com/syllabus']
    links = open('links.json', 'r+')
    pages = open('pages.json', 'r+')
    admin = Manager(links, pages)

    admin.crawler(base)
    while True:
        for link in links:
            admin.run(admin.crawler, list(link))
#        admin.run(admin.scraper, list(pages))
        admin.jobs.join()
    '''
    admin.run(admin.crawler, ['facebook.com'])
    admin.run(admin.scraper, [])
    '''


main()
