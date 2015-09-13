#import json
import crawler
import scraper

def main():
    #base = raw_input(']===>  scrape URL: ')
    base = 'http://www.cse.msu.edu/~cse232/'
    crawl = crawler.Crawler(base)
    crawl.run()
    crawl = crawl.get_visited()
    for line in crawl:
        scraper.Scraper(line).run(base)


main()
