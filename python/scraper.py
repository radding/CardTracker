from bs4 import BeautifulSoup
from Queue import Queue
import requests
import url

# disable warnings for debugging
import urllib3
urllib3.disable_warnings()


class Scraper(object):
    ''' Scraper Class '''

    def __init__(self, base):
        self.base = base
        self.temp_base = base
        self.prev_urls = list()
        self.next_urls = Queue()
        self.next_urls.put(base)

    def get_next_url(self):
        return self.next_urls.get()

    def process_page(self, bs_object):
        for link in bs_object.find_all('a'):

            if link.get('href'):
                url = link.get('href')

                # fix url fragments
                if url[0] == '/':
                    url = self.temp_base + url
                elif url[0] == '#':
                    url = self.temp_base

                # Add url to next_urls
                if url not in self.prev_urls:
                    #print(url)
                    self.next_urls.put(url)

    def run(self):
        while not self.next_urls.empty():
            next_url = self.get_next_url()
            print(url.Url(next_url).to_json())

            page = BeautifulSoup(requests.get(next_url).text, "html.parser")
            self.prev_urls.append(next_url)
            #self.temp_base = next_url
            self.process_page(page)


def main():
    #base = raw_input('URL to scrape: ')
    base = 'http://iah201.tumblr.com/syllabus'
    Scraper(base).run()


main()
