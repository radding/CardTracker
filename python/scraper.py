from Queue import Queue
from bs4 import BeautifulSoup
import requests
import url

# disable warnings for debugging
import urllib3
urllib3.disable_warnings()


class Scraper(object):
    ''' Scraper Class '''

    def __init__(self, base, visited=[]):
        self.base = str(base)
        self.temp_base = str(base)
        self.visited = visited
        print("[Scraper Initiated]")

    def run(self, original):
        page = self.base
        if page == "#":
            return False
        if page[0] == "/":
            if original[len(original)-1] == "/":
                page = original + page[1:]
            else:
                page = original + page

        self.visited.append(url.Url(page).to_json())
        print url.Url(page).to_json()
        self.visited.append(page)

        # Grab all <img> tags
        bs_object = BeautifulSoup(requests.get(page).text, "html.parser")
        for link in bs_object.find_all('img'):
            if str(link.get('src')) in self.visited:
                break
            elif link.get('src') and str(link.get('src')) not in self.visited:
                uri = str(link.get('src'))
                self.visited.append(uri)

                # fix url fragments
                if uri[0] == '#':
                    uri = str(page)
                elif uri[0] == '/':
                    uri = str(self.temp_base) + uri[1:]

                self.visited.append(uri)
                print "==> " + uri
                self.temp_base = str(uri)


        print("[Scraper Terminated]")
