import requests
import json

class Endpoint: 
  apiKey = 'b391f262d1a59e53d49c2fa94e272131'
  customerID = None
  accountType = None
  nickname = None
  rewards = None
  balance = None
  accountID = None
  firstName = None
  lastName = None
  streetNumber = None
  streetName = None
  city = None
  state = None
  zipCode = None
  def __init__(self):
    self.ID = '55e94a6af8d8770528e60c89'

class Customer(Endpoint):

  def __init(self, ID):
    Endpoint.__init__(self, ID)

  @classmethod
  def getAccs(cls):
    global listOfAccounts
    url = 'http://api.reimaginebanking.com/accounts?key={}'.format(cls.apiKey)
    r = requests.get(url)
    r = r.json()
    for item in r:
      c = Customer()
      c.accountID = item['_id']
      c.type = item['type']
      c.rewards = item['rewards']
      c.nickname = item['nickname']
      c.customerID = item['customer_id']
      c.balance = item['balance']
      yield c

  # get account by customer ID  
  def getAcc(self):
    url = 'http://api.reimaginebanking.com/customers/{}/accounts?key={}'.format(self.ID, self.apiKey)
    r = requests.get(url)

    r = r.json()
  # create an account
  def createAcc(self, cardType, nname, rewards, balance):
    url = 'http://api.reimaginebanking.com/customers/{}/accounts?key={}'.format(self.ID,self.apiKey)
    payload = {
    "type" : cardType,
    "nickname" : nname,
    "rewards" : rewards,
    "balance" : balance,
    }

    r = requests.post(url, data = json.dumps(payload), headers = {'content-type':'application/json'},)

    # print r.content

  # update an account
  def updateAcc(self, nname, accID):
    # url = 'http://api.reimaginebanking.com/customers/accounts?key={}/{}'.format(self.apiKey,self.ID)
    url = 'http://api.reimaginebanking.com/accounts/{}?key={}'.format(accID,self.apiKey)
    update = { "nickname" : nname}
    r = requests.put(url, data = json.dumps(update), headers = {'content-type':'application/json'},)

    # print r.content

  # delete an account 
  def delAcc(self, accID):
    url = 'http://api.reimaginebanking.com/accounts/{}?key={}'.format(accID,self.apiKey)
    r = requests.delete(url)

    # print r.content

  def getCustomerByID(self, accID):
    url = 'http://api.reimaginebanking.com/accounts/{}?key={}'.format(accID,self.apiKey)
    r = requests.get(url)
    r = r.json()

  @classmethod
  def getAllCustomers(cls):
    url = 'http://api.reimaginebanking.com/customers/?key={}'.format(cls.apiKey)
    r = requests.get(url)
    print r.content
    r = r.json()
    for i in r:
      c = Customer()
      c.customerID = i['_id']
      c.firstName = i['first_name']
      c.lastName = i['last_name']
      yield c
  def getAllPurchases(self, accID):
    url = 'http://api.reimaginebanking.com/accounts/{}/purchases?key={}'.format(accID,self.apiKey)
    r = requests.get(url)
    # print r.content

  def getPurchaseByID(self, purchaseID):
    url = 'http://api.reimaginebanking.com/purchases/{}/?key={}'.format(purchaseID, self.apiKey)
    r = requests.get(url)
    # print r.content

  def getAllMerchants(self):
    url = 'http://api.reimaginebanking.com/merchants/?key={}'.format(self.apiKey)
    r=requests.get(url)
    # print r.content

  def getMerchantByID(self, merchantID):
    url = 'http://api.reimaginebanking.com/merchants/{}?key={}'.format(merchantID, self.apiKey)
    r=requests.get(url)
    # print r.content