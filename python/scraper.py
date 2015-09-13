from Queue import Queue
from bs4 import BeautifulSoup
import requests
import url

# disable warnings for debugging
import urllib3
urllib3.disable_warnings()


class Scraper(object):
    ''' Scraper Class '''

    def __init__(self, page):
        self.page = page
        self.images = list()
        self.next_imgs = Queue()
        self.next_imgs.put(url)

    def get_img(self, output_file):
        output_file.write(url.Url(self.url).to_json() + "\n")

    def get_links(self, ba):
        bs_object = BeautifulSoup(requests.get(self.url).text, "html.parser")
        for link in bs_object.find_all('a'):

            if link.get('href'):
                url = link.get('href')

                # fix url fragments
                if url[0] == '/':
                    url = self.temp_base + url #[1:]
                elif url[0] == '#':
                    url = self.temp_base

                # Add url to next_urls
                if url not in self.prev_urls:
                    print("=> " + url)
                    self.next_urls.put(url)
