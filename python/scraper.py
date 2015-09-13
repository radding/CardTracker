from Queue import Queue
from bs4 import BeautifulSoup
import requests
import url
import urllib

# disable warnings for debugging
import urllib3
urllib3.disable_warnings()


class Scraper(object):
    ''' Scraper Class '''

    def __init__(self, base, visited=[]):
        self.base = str(base)
        self.temp_base = str(base)
        self.visited = visited
        print "<scraper>"

    def run(self, original):
        page = self.base
        if original in page:
            pass
        elif page == "#":
            return False
        elif page[0] == "/":
            if original[len(original)-1] == "/":
                page = original + page[1:]
            else:
                page = original + page
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
                image_url = str(original) + str(uri)
                print "\n=====================[IMAGE]==>  " + image_url + "\n"
                self.temp_base = str(uri)

                # Save image locally
                urllib.urlretrieve(image_url, "images/" + image_url.rsplit("/", 1)[-1])


        print("</scraper>\n")
