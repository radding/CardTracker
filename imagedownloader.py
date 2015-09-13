from pymongo import MongoClient
import tempfile
import requests

mongo = MongoClient("indexr1.cloudapp.net", 27017)
db = mongo.test_database
imgs =  db.image_collection
img = db.image

def download_image(url):
    _, file_name = tempfile.mkstemp()
    f = open(file_name, "w+")
    r = requests.get(settings.STATICMAP_URL.format(**data), stream=True)
    if r.status_code == 200:
        for chunk in r:
            f.write(chunk)
            pass
        pass
    f.close()
    return file_name
    
