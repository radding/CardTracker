from multiprocessing import Lock, Pool, Process, JoinableQueue
from crawler import Crawler
#from scraper import Scraper
import json

class Manager(object):
    ''' Manager Class '''

    def __init__(self, f_links, f_pages):
        self.links = f_links
        self.pages = f_pages
        self.jobs = JoinableQueue()

    def crawler(self, link):
        Crawler(link).run(self.links)

    def scraper(self, page):
        Scraper(page).run(self.pages)

    def run(self, proc, argz):
        p = Process(target=proc, args=(argz))
        self.jobs.put(p)
        p.start()
        self.jobs.task_done(p)

    '''
    def run_multi(self, proc, argz):
        for i in argz:
            p = Process(target=proc, args=(i,))
            self.jobs.put(p)
            p.start()
    '''
