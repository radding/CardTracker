from bs4 import BeautifulSoup
import requests
import url
import scraper

### Disable warnings for debugging
# import urllib3
# urllib3.disable_warnings()


class Crawler(object):
    ''' Crawler Class '''

    def __init__(self, base):
        self.base = str(base)
        self.temp_base = str(base)
        self.visited = list()
        print("[Crawler initiated]")

    def run(self, output_file):
        output_file.write(url.Url(self.base).to_json() + "\n")
        print url.Url(self.base).to_json()

        while self.visited != []:
            # Grab all <a> tags
            bs_object = BeautifulSoup(requests.get(self.base).text, "html.parser")
            for link in bs_object.find_all('a'):

                if link.get('href'):
                    uri = str(link.get('href'))
                    print "link.href ==>" + uri

                    # fix url fragments
                    if uri[0] == '#':
                        uri = str(self.temp_base)
                    elif uri[0] == '/':
                        uri = str(self.temp_base) + uri

                    # Add url to next_urls
                    if uri not in self.visited:
                        print("not in .visited ==> " + uri)
                        self.visited.append(uri)
                        self.temp_base = str(uri)

            self.visited.append(self.base)

        print("[Crawler Terminated]")
