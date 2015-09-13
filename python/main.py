import crawler
import scraper

def main():
    base = raw_input('===>  scrape URL: ')
    crawl = crawler.Crawler(base)
    crawl.run()
    crawl = crawl.get_visited()
    for line in crawl:
        scraper.Scraper(line).run(base)


main()
