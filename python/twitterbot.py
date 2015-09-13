from pymongo import MongoClient, ASCENDING, DESCENDING
from TwitterSearch import *
import datetime

mongo = MongoClient("indexr1.cloudapp.net", 27017)
db = mongo.test_database
imgs =  db.image_collection
img = db.image
#imgs.create_index([("dateadded", DESCENDING)])
try:
     tso = TwitterSearchOrder()
     tso.set_keywords(['debit', 'credit', 'card'])
     tso.set_link_filter()
     tso.set_include_entities(True)
     ts = TwitterSearch(
         consumer_key = 'qkUUSqgI3XSDziEFZr1tHBeih',
         consumer_secret = 'IPyBLRtLzhEmLd6AOM4G4Fo4mDOPCbVy9zejwMNymmbWe9bvRs',
         access_token = '2765083396-vCH2XOT88ltKgNH4BBRUk0WaQAMpfFdoaICGln3',
         access_token_secret = 'LV0kkTkakUhSMTjsoeWp4M8NWXlZbizMe6Ke6uha303ed'
     )
     for tweet in ts.search_tweets_iterable(tso):
         try:
             for content in tweet["entities"]["media"]:
                 if content["type"] == "photo":
                     img = dict(url=content["media_url"], dateadded=datetime.datetime.now())
                     imgs.insert_one(img)
                     pass
                 pass
         except KeyError:
             print "Error: ", tweet
except TwitterSearchException as e:
    print(e)
