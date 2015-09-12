import requests
from bs4 import BeautifulSoup
from Queue import Queue

#base = 'http://iah201.tumblr.com/syllabus'


class Scraper(object):
    ''' Scraper Class '''

    def __init__(self, base):
        self.base = base
        self.temp_base = base
        self.next_urls = Queue()
        self.next_urls.put(base)
        self.prev_urls = list()

    def get_next_url(self):
        return self.next_urls.get()

    def process_page(self, bs_object):
        for link in bs_object.find_all('a'):
            print(link.get('href'))
            if link.get('href') and link.get('href') not in self.prev_urls:
                if link.get('href')[0] == '/':
                    self.next_urls.put(self.temp_base + link.get('href'))
                elif link.get('href')[0] == '#':
                    self.next_urls.put(self.temp_base)
                else:
                    self.next_urls.put(link.get('href'))

    def run(self):
        while not self.next_urls.empty():
            next_url = self.get_next_url()
            page = BeautifulSoup(requests.get(next_url).text, "html.parser")
            # USE REQUESTS YOU
            self.temp_base = next_url
            self.prev_urls.append(next_url)
            self.process_page(page)


def main():
    base = raw_input('URL to scrape: ')
    Scraper(base).run()


main()
