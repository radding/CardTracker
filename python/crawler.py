from Queue import Queue
import requests
import url
import scraper

### Disable warnings for debugging
# import urllib3
# urllib3.disable_warnings()


class Crawler(object):
    ''' Crawler Class '''

    def __init__(self, base):
        self.base = base
        self.temp_base = base
        self.prev_urls = list()
        self.next_urls = Queue()
        self.next_urls.put(base)
        print("[Crawler initiated]")

    def get_next_url(self):
        return self.next_urls.get()

    def run(self, output_file):
        while not self.next_urls.empty():
            next_url = self.get_next_url()
            output_file.write(url.Url(next_url).to_json() + "\n")
            print(url.Url(next_url).to_json())

            self.prev_urls.append(str(next_url))
            self.temp_base = next_url

            # eventually must call Scraper().get_images()
            # scraper.Scraper(page).get_links(next_url)
            #print("\n PREV URLS: \n" + str(self.prev_urls))
            #print("\n NEXT URLS: \n" + str(self.next_urls.get()))
            #print
        print("[Crawler Terminated]")
