import json

class Url(object):
    ''' Url Class '''

    def __init__(self, url):
        # Remove trailing "/"
        if url[len(url)-1:] =='/':
            url = url[0:len(url)-1]
        self.url = url

    def get_protocol(self):
        ''' Return values:
        https => 1
        http => 0'''
        if self.url[0:5] == 'http':
            return 1
        else:
            return 0

    def to_json(self):
        ''' Returns db-ready JSON '''

        # Remove protocol
        if self.get_protocol():
            temp_url = self.url[8:]
        elif self.url[0:4] == 'http':
            temp_url = self.url[7:]
        else:
            temp_url = self.url

        # Remove hostname
        if temp_url[0:4] == 'www.':
            temp_url = temp_url[5:]

        return json.dumps({'https': self.get_protocol(),
                           'url': temp_url}, sort_keys = True)
