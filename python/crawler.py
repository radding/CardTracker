from bs4 import BeautifulSoup
import requests
import url
import scraper

### Disable warnings for debugging
# import urllib3
# urllib3.disable_warnings()


class Crawler(object):
    ''' Crawler Class '''

    def __init__(self, base, visited=[]):
        self.base = str(base)
        self.temp_base = str(base)
        self.visited = visited
        print "<crawler>"

    def get_visited(self):
        print "VISITED ==> " + " , ".join(self.visited)
        return self.visited

    def run(self):
        self.visited.append(self.base)
        print url.Url(self.base).to_json()
        self.visited.append(self.base)

        # Grab all <a> tags
        bs_object = BeautifulSoup(requests.get(self.base).text, "html.parser")
        for link in bs_object.find_all('a'):
            if str(link.get('href')) in self.visited:
                break
            elif link.get('href') and str(link.get('href')) not in self.visited:
                uri = str(link.get('href'))
                self.visited.append(uri)

                # fix url fragments
                if uri[0] == '#':
                    uri = str(self.base)
                elif uri[0] == '/':
                    uri = str(self.temp_base) + uri[1:]

                self.visited.append(uri)
                print "==> " + uri
                self.temp_base = str(uri)


        print "</crawler>\n"
